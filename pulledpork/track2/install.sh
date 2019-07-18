#!/bin/bash

# --- issues with vdf_bot
# Instead of using the exitcode to determine an error,
# vdf_bot considers any output on stderr to be an error.
# So warnings during compiling the libraries,
# spurious stderr output from make scripts,
# or using set -x, will kill the install.
# This is my work around:
exec 3>&2 # fd3 = original stderr
exec 2>&1 # redirect stderr to stdout
trap 'echo "ERR" 1>&3; exit 1' ERR # on error: write to org stderr and exit

# --- pull down mpir and flint, then configure and build them
set -x
sudo apt-get -q update
sudo apt-get -q -y install gcc g++ yasm m4 make libmpfr-dev cgroup-tools

wget -q http://mpir.org/mpir-3.0.0.tar.bz2
wget -q http://www.flintlib.org/flint-2.5.2.tar.gz

tar -xaf mpir-3.0.0.tar.bz2
tar -xaf flint-2.5.2.tar.gz

# there are issue with mpir on skylake non-avx
# see: https://github.com/wbhart/mpir/issues/274
# after trying several work around options, the best appears to be
# fall back to haswell
rm mpir-3.0.0/mpn/x86_64/skylake/{add,sub}_n.as
export MPN_PATH=" x86_64/skylake x86_64/haswell x86_64/sandybridge x86_64 generic"

# adjust cflags for mpir
export CFLAGS="-O3 -march=corei7 -mtune=corei7"

export VDF_BASE=$(pwd)
export VDF_PREFIX=$(pwd)/vdfroot

cd mpir-3.0.0
./configure --prefix=$VDF_PREFIX --disable-shared --enable-cxx --enable-gmpcompat --disable-fft --build=skylake-pc-linux-gnu
make -j3
make install
cd ..

# lower opt level for higher level code
export CFLAGS="-O2 -march=corei7 -mtune=corei7"

cd flint-2.5.2
./configure --prefix=$VDF_PREFIX --disable-shared --with-mpir=$VDF_PREFIX
make -j3
make install
cd ..

# --- finally build our binary
export CFLAGS="$CFLAGS -I$VDF_PREFIX/include"
export LDFLAGS="-L$VDF_PREFIX/lib"
g++ -o vdf $CFLAGS $LDFLAGS vdf.cpp -lflint -lmpfr -lgmp -lgmpxx

# ======== performance tweaks ========

# ---- reserve a core for our program
# do after building so that all the cpus can be used when compiling/linking

# create a cpuset for "normal" processes, and move all tasks there
# ideally we'd use isolcpus on bootline, but that is out of our control
sudo cgcreate -g cpuset:/everythingelse
sudo cgset -r cpuset.cpus=0 everythingelse
sudo cgset -r cpuset.mems=0 everythingelse # otherwise empty

CPUSET=/sys/fs/cgroup/cpuset
(set +x # too noisy
echo "moving tasks to cpuset:/everythingelse"
# kernel tasks may refuse to move, for example:
#   UID        PID  PPID  C STIME TTY      STAT   TIME CMD
#   root         2     0  0 02:33 ?        S      0:00 [kthreadd]
# this is indicated by the write failing with the error "Invalid argument"
# so just try moving each task, allowing it to fail
for pid in $(cat $CPUSET/tasks); do
    echo "$pid" | sudo tee $CPUSET/everythingelse/tasks &> /dev/null || true
done
echo "done moving tasks to cpuset:/everythingelse"
)

# note how many were/were-not moved
wc -l /sys/fs/cgroup/cpuset/tasks
wc -l /sys/fs/cgroup/cpuset/everythingelse/tasks

# create a cpuset for our vdf program
sudo cgcreate -a $USER:$USER -t $USER:$USER -g cpuset:/vdfonly
cgset -r cpuset.cpus=1 vdfonly
cgset -r cpuset.mems=0 vdfonly # otherwise empty
cgset -r cpuset.cpu_exclusive=1 vdfonly
#cgset -r cpuset.sched_load_balance=0 vdfonly # probably overkill, and unwise without isolcpus, since many of our task moves failed

# ---- adjust cpufreq scaling (apparently it was defaulting to powersave)
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor > /dev/null

echo "install done on $(hostname)"
exit 0

