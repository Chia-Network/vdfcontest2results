# Congratulations to Sundersoft for winning both tracks of the second Chia VDF competition and earning $100,000!  
  
We had four entries that all made large improvements in the speed of the VDF algorithm in both contest tracks compared to our in house reference implementation. Note that these timings are for 4x the iterations and on slightly slower hardware (no turboboost) than the first VDF contest.

Two of the entries had problems with certain discriminants. Since the final judging discriminants are unknown (aside from a hash) to the contest entrants, we recommend testing your entry against as many random discriminants as possible.  
  
The passphrase for the final judging discriminant generation (as given by the precommitment at contest start) is below:  
  
python3 create_competition_discriminants.py “armor drive digital shaft dash wide resemble guilt bubble push sniff grass asset vital version reward grid popular ketchup diary pen hurdle doctor lumber”  
  
Sundersoft's entry took advantage of a number of optimizations and you can read about his improvements [here](sundersoft/entry/README.md). One of his ideas was to parallelize parts of the algorithm in order to take advantage of two cores, and that helped to push him to a 2x speedup over the reference implementation.  
  
Techniques from ALL contestants will likely be incorporated to further improve the VDF algorithm. Thus, additionally, Chia has decided to award $2000 each to the three teams that submitted an optimized entry but did not place first. Thank you for your hard work! 

The source code for all entries for both tracks is included in this [repository](https://github.com/Chia-Network/vdfcontest2results).  
  
Please consider entering our [current competition](https://www.chia.net/2019/07/07/chia-network-announces-pos-competition.en.html) for improving the [Proof of Space](https://github.com/Chia-Network/proofofspace) algorithm. Proof of Space is heavily dependent on sorting and disk I/O and there should be many possibilities for improvement over the reference implementation. There is also a Hellman attack (time/memory tradeoff) example for those who would like to see how much space they can save by maxing out the computational power of the reference hardware.  
  
## Track 1 Results (SIMD/GPU) in avg sec per run  
  
Sundersoft: 91.3    
nemo1369: 133 crash #4 hang #5    
PulledPork: 145.7 (late entry)    
pulmark: 161 hang #4    
Chia reference: 178    
  
## Track 2 Results (No SIMD/GPU) in avg sec per run  
  
Sundersoft: 97.4    
nemo1369: 142 crash #4 hang #5    
PulledPork: 153 (late entry)    
pulmark: 164 hang #4    
Chia reference: 182.6    
  
### Track 1 Runs (SIMD/GPU)  
  
#### Successfully cloned the repository keybase://team/chia_network.nemo1369/track1  
Starting install.sh  
Install output: x86_64-unknown-linux-gnu  
-- The C compiler identification is GNU 8.3.0  
-- The CXX compiler identification is GNU 8.3.0  
-- Check for working C compiler: /usr/bin/cc  
-- Check for working C compiler: /usr/bin/cc -- works  
-- Detecting C compiler ABI info  
-- Detecting C compiler ABI info - done  
-- Detecting C compile features  
-- Detecting C compile features - done  
-- Check for working CXX compiler: /usr/bin/c++  
-- Check for working CXX compiler: /usr/bin/c++ -- works  
-- Detecting CXX compiler ABI info  
-- Detecting CXX compiler ABI info - done  
-- Detecting CXX compile features  
-- Detecting CXX compile features - done  
-- The ASM compiler identification is GNU  
-- Found assembler: /usr/bin/cc  
-- Performing Test HAVE_AVX_EXTENSIONS  
-- Performing Test HAVE_AVX_EXTENSIONS - Failed  
-- Performing Test HAVE_AVX2_EXTENSIONS  
-- Performing Test HAVE_AVX2_EXTENSIONS - Failed  
-- Found MPIRXX: /usr/local/lib/libmpirxx.a    
-- Found MPFR: /usr/include (Required is at least version "1.0.0")   
-- Configuring done  
-- Generating done  
-- Build files have been written to: /home/chia/host_entry/submissions/entry/build/release  
Scanning dependencies of target chia_vdf_test  
[ 50%] Building CXX object CMakeFiles/chia_vdf_test.dir/src/main.cpp.o  
[100%] Linking CXX executable chia_vdf_test  
[100%] Built target chia_vdf_test  
  
Install errors:   
Total time for installation: 112.38236498832703  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.1618411540985  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.4143304824829  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.10787725448608  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.15771675109863  
4: Starting run.sh  
Iterations: 8388608  
Run Errors: Floating point exception (core dumped)  
  
Incorrect output  
Run Output:   
Total time for entry: 58.05953121185303  
5: Starting run.sh  
Iterations: 8388608  
Timeout of 10 minutes for running expired! Halting the execution  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.41919565200806  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.24476051330566  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.18854069709778  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 133.44797039031982  
Total time for 10 runs: 1724.309164762497  
  
#### Successfully cloned the repository keybase://team/chia_network.pulmark/track1  
Starting install.sh  
Install output:   
Install errors:   
Total time for installation: 0.9050869941711426  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 161.14946961402893  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 161.04424571990967  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 161.01133561134338  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 160.93533849716187  
4: Starting run.sh  
Iterations: 8388608  
Timeout of 10 minutes for running expired! Halting the execution  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 160.97457265853882  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 161.11020946502686  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 160.95081663131714  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 161.04002475738525  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 160.9651539325714  
Total time for 10 runs: 2049.2939624786377  
  
#### Successfully cloned the repository keybase://team/chia_network.sundersoft/entry  
Starting install.sh  
Install output:   
cat /proc/cpuinfo | grep -e MHz -e GHz  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1200.034  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1327.733  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1259.417  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1376.102  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1200.062  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1291.428  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1263.274  
model name    : Intel(R) Xeon(R) W-2123 CPU @ 3.60GHz  
cpu MHz        : 1436.681  
cat /proc/cpuinfo | grep flags | head -n 1  
flags        : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb cat_l3 cdp_l3 invpcid_single pti intel_ppin ssbd mba ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm cqm mpx rdt_a avx512f avx512dq rdseed adx smap clflushopt clwb intel_pt avx512cd avx512bw avx512vl xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local dtherm arat pln pts md_clear flush_l1d  
enable_all_instructions=0  
if cat /proc/cpuinfo | grep -w avx2 | grep -w fma | grep -w -q adx; then  
    enable_all_instructions=1  
fi  
echo "enable_all_instructions: $enable_all_instructions"  
enable_all_instructions: 1  
  
sudo apt-get install libgmp3-dev -y  
Reading package lists...  
Building dependency tree...  
Reading state information...  
libgmp3-dev is already the newest version (2:6.1.2+dfsg-3).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
sudo apt-get install libflint-dev -y  
Reading package lists...  
Building dependency tree...  
Reading state information...  
libflint-dev is already the newest version (2.5.2-18).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
  
compile_flags="-std=c++1z -D VDF_MODE=0 -D ENABLE_ALL_INSTRUCTIONS=$enable_all_instructions -no-pie -march=native"  
link_flags="-no-pie -lgmpxx -lgmp -lflint -lpthread"  
  
g++ -o compile_asm.o -c compile_asm.cpp $compile_flags -O0  
g++ -o compile_asm compile_asm.o $link_flags  
./compile_asm  
as -o asm_compiled.o asm_compiled.s  
g++ -o vdf.o -c vdf.cpp $compile_flags -O3  
g++ -o vdf vdf.o asm_compiled.o $link_flags  
  
Install errors:   
Total time for installation: 9.441139459609985  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.85422348976135  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.3599112033844  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.52150201797485  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 92.13793563842773  
4: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.78142023086548  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.93001890182495  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.88069820404053  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.74474239349365  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.40027356147766  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 91.42858910560608  
Total time for 10 runs: 917.0397233963013  
  
#### Successfully cloned the repository keybase://team/chia_network.pulledpork/track1  
Entry logs are too big... Showing only last 9000 characters  
/fq_zech_poly/fq_zech_poly_sub.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_brent_kung.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_normalise.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_xgcd_euclidean_f.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_evaluate_fq.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_set.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_powmod_ui_binexp_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_derivative.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_sqr.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mulhigh_classical.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_deflation.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_div_series.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_powmod_fmpz_sliding_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_randtest_irreducible.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_inflate.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_hgcd.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_add.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_gcd_euclidean.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mul.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_evaluate_fq_vec_fast.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mullow_classical.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_evaluate_fq_vec_iter.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_sqr_KS.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_inlines.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_get_str.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_divrem_f.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_randtest_monic.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_swap.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_pow.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_scalar_submul_fq.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_divrem_divconquer_recursive.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_init.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_shift_right.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_brent_kung_precomp_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mullow_KS.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_horner.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_shift_left.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_fprint.o  
make[2]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2/fq_zech_poly'  
make[2]: Entering directory '/home/chia/host_entry/submissions/entry/flint-2.5.2/fq_zech_poly_factor'  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_squarefree.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_cantor_zassenhaus.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_squarefree.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_kaltofen_shoup.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_print.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_pow.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_irreducible.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_init.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_insert.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_realloc.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_fit_length.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_inlines.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_equal_deg.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_iterated_frobenius_preinv.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_berlekamp.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_clear.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_irreducible_ben_or.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_concat.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_irreducible_ddf.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_equal_deg_prob.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_print_pretty.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_distinct_deg.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_set.o  
make[2]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2/fq_zech_poly_factor'  
    AR   libflint.a  
make[1]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2'  
+ make install  
make[1]: Entering directory '/home/chia/host_entry/submissions/entry/flint-2.5.2'  
make[1]: Nothing to be done for 'static'.  
make[1]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2'  
ls: cannot access 'libflint.so*': No such file or directory  
mkdir -p "/home/chia/host_entry/submissions/entry/vdfroot/lib"  
mkdir -p "/home/chia/host_entry/submissions/entry/vdfroot/include/flint"  
cp  ulong_extras.h  long_extras.h  perm.h  fmpz.h  fmpz_vec.h  fmpz_poly.h  fmpq_poly.h  fmpz_mat.h  fmpz_lll.h  mpfr_vec.h  mpfr_mat.h  mpf_vec.h  mpf_mat.h  nmod_vec.h  nmod_poly.h  nmod_poly_factor.h  arith.h  mpn_extras.h  nmod_mat.h  fmpq.h  fmpq_vec.h  fmpq_mat.h  padic.h  fmpz_poly_q.h  fmpz_poly_mat.h  nmod_poly_mat.h  fmpz_mod_poly.h  fmpz_mod_poly_factor.h  fmpz_factor.h  fmpz_poly_factor.h  fft.h  qsieve.h  double_extras.h  d_vec.h  d_mat.h  padic_poly.h  padic_mat.h  qadic.h  fq.h  fq_vec.h  fq_mat.h  fq_poly.h  fq_poly_factor.h  fq_nmod.h  fq_nmod_vec.h  fq_nmod_mat.h  fq_nmod_poly.h  fq_nmod_poly_factor.h  fq_zech.h  fq_zech_vec.h  fq_zech_mat.h  fq_zech_poly.h  fq_zech_poly_factor.h NTL-interface.h flint.h longlong.h config.h gmpcompat.h fft_tuning.h fmpz-conversions.h profiler.h templates.h  fq_vec_templates.h  fq_mat_templates.h  fq_poly_templates.h  fq_poly_factor_templates.h  fq_templates.h "/home/chia/host_entry/submissions/entry/vdfroot/include/flint"  
mkdir -p "/home/chia/host_entry/submissions/entry/vdfroot/include/flint/flintxx"  
cp flintxx/*.h "/home/chia/host_entry/submissions/entry/vdfroot/include/flint/flintxx"  
cp *xx.h "/home/chia/host_entry/submissions/entry/vdfroot/include/flint"  
+ cd ..  
+ export 'CFLAGS=-O3 -march=skylake -mtune=skylake -I/home/chia/host_entry/submissions/entry/vdfroot/include'  
+ CFLAGS='-O3 -march=skylake -mtune=skylake -I/home/chia/host_entry/submissions/entry/vdfroot/include'  
+ export LDFLAGS=-L/home/chia/host_entry/submissions/entry/vdfroot/lib  
+ LDFLAGS=-L/home/chia/host_entry/submissions/entry/vdfroot/lib  
+ g++ -o vdf -O3 -march=skylake -mtune=skylake -I/home/chia/host_entry/submissions/entry/vdfroot/include -L/home/chia/host_entry/submissions/entry/vdfroot/lib vdf.cpp -lflint -lmpfr -lgmp -lgmpxx  
+ sudo cgcreate -g cpuset:/everythingelse  
+ sudo cgset -r cpuset.cpus=0-5 everythingelse  
+ sudo cgset -r cpuset.mems=0 everythingelse  
+ CPUSET=/sys/fs/cgroup/cpuset  
+ set +x  
moving tasks to cpuset:/everythingelse  
done moving tasks to cpuset:/everythingelse  
+ wc -l /sys/fs/cgroup/cpuset/tasks  
103 /sys/fs/cgroup/cpuset/tasks  
+ wc -l /sys/fs/cgroup/cpuset/everythingelse/tasks  
302 /sys/fs/cgroup/cpuset/everythingelse/tasks  
+ sudo cgcreate -a : -t : -g cpuset:/vdfonly  
+ cgset -r cpuset.cpus=6-7 vdfonly  
+ cgset -r cpuset.mems=0 vdfonly  
+ cgset -r cpuset.cpu_exclusive=1 vdfonly  
+ echo performance  
+ sudo tee /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor /sys/devices/system/cpu/cpu5/cpufreq/scaling_governor /sys/devices/system/cpu/cpu6/cpufreq/scaling_governor /sys/devices/system/cpu/cpu7/cpufreq/scaling_governor  
++ hostname  
+ echo 'install done on beast'  
install done on beast  
+ exit 0  
  
Install errors:   
Total time for installation: 87.47422742843628  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 146.93210363388062  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.32032871246338  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.28240156173706  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.42277097702026  
4: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 147.22733616828918  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.56169080734253  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.2247200012207  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.75197649002075  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.30732035636902  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 145.4335377216339  
Total time for 10 runs: 1457.4648282527924  
  
#### Successfully cloned the repository keybase://team/chatbotvdftest/vdf2  
Starting install.sh  
Install output: Reading package lists...  
Building dependency tree...  
Reading state information...  
libgmp3-dev is already the newest version (2:6.1.2+dfsg-3).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
Reading package lists...  
Building dependency tree...  
Reading state information...  
libflint-dev is already the newest version (2.5.2-18).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
  
Install errors:   
Total time for installation: 2.1522510051727295  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 177.35045957565308  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 177.5227553844452  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 180.0469093322754  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 177.6243498325348  
4: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 178.05836820602417  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 177.6966621875763  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 177.42461252212524  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 177.47170400619507  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 178.19566297531128  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 178.11474299430847  
Total time for 10 runs: 1779.5067927837372  
  
### Track 2 Runs (No SIMD/GPU)  
  
#### Successfully cloned the repository keybase://team/chia_network.sundersoft/entry  
Starting install.sh  
Install output:   
cat /proc/cpuinfo | grep -e MHz -e GHz  
model name    : Intel(R) Pentium(R) CPU G4500 @ 3.50GHz  
cpu MHz        : 2424.402  
model name    : Intel(R) Pentium(R) CPU G4500 @ 3.50GHz  
cpu MHz        : 1368.524  
cat /proc/cpuinfo | grep flags | head -n 1  
flags        : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust erms invpcid rdseed smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm arat pln pts hwp hwp_notify hwp_act_window hwp_epp md_clear flush_l1d  
enable_all_instructions=0  
if cat /proc/cpuinfo | grep -w avx2 | grep -w fma | grep -w -q adx; then  
    enable_all_instructions=1  
fi  
echo "enable_all_instructions: $enable_all_instructions"  
enable_all_instructions: 0  
  
sudo apt-get install libgmp3-dev -y  
Reading package lists...  
Building dependency tree...  
Reading state information...  
libgmp3-dev is already the newest version (2:6.1.2+dfsg-3).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
sudo apt-get install libflint-dev -y  
Reading package lists...  
Building dependency tree...  
Reading state information...  
libflint-dev is already the newest version (2.5.2-18).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
  
compile_flags="-std=c++1z -D VDF_MODE=0 -D ENABLE_ALL_INSTRUCTIONS=$enable_all_instructions -no-pie -march=native"  
link_flags="-no-pie -lgmpxx -lgmp -lflint -lpthread"  
  
g++ -o compile_asm.o -c compile_asm.cpp $compile_flags -O0  
g++ -o compile_asm compile_asm.o $link_flags  
./compile_asm  
as -o asm_compiled.o asm_compiled.s  
g++ -o vdf.o -c vdf.cpp $compile_flags -O3  
g++ -o vdf vdf.o asm_compiled.o $link_flags  
  
Install errors:   
Total time for installation: 9.596147775650024  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.45304107666016  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.48760509490967  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.4010922908783  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.47472286224365  
4: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.34111976623535  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.3874523639679  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.56164622306824  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.33419799804688  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.77236986160278  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 97.38989806175232  
Total time for 10 runs: 974.6033797264099  
  
#### Successfully cloned the repository keybase://team/chia_network.pulmark/track2  
Starting install.sh  
Install output:   
Install errors:   
Total time for installation: 0.519963264465332  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.36102747917175  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.33928632736206  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.4577133655548  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 165.2287402153015  
4: Starting run.sh  
Iterations: 8388608  
Timeout of 10 minutes for running expired! Halting the execution  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.23687934875488  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.4793803691864  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.53272581100464  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.33844780921936  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 164.44704580307007  
Total time for 10 runs: 2080.5236349105835  
  
#### Successfully cloned the repository keybase://team/chia_network.pulledpork/track2  
Entry logs are too big... Showing only last 9000 characters  
build/fq_zech_poly/fq_zech_poly_compose_mod_brent_kung.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_shift_left.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_hamming_weight.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_div_basecase.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_set_fq.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mullow_classical.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_div_newton_n_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_normalise.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_sub.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_remove.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_evaluate_fq.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_set.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_derivative.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mul.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_deflation.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_sqr.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mulhigh_classical.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_get_str.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_powmod_fmpz_sliding_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_randtest_irreducible.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_gcd.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_xgcd_euclidean_f.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mulhigh.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_one.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_evaluate_fq_vec_fast.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_evaluate_fq_vec_iter.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_shift_right.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_make_monic.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_brent_kung_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_get_str_pretty.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_deflate.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_divrem_divconquer.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_scalar_submul_fq.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_divrem_f.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_init.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_sqr_KS.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_xgcd_euclidean.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_brent_kung_precomp_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mullow_KS.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_divrem_divconquer_recursive.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_compose_mod_horner_preinv.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_fprint.o  
    CC   ../build/fq_zech_poly/fq_zech_poly_mul_classical.o  
make[2]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2/fq_zech_poly'  
make[2]: Entering directory '/home/chia/host_entry/submissions/entry/flint-2.5.2/fq_zech_poly_factor'  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_squarefree.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_cantor_zassenhaus.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_squarefree.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_kaltofen_shoup.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_print.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_init.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_print_pretty.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_insert.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_realloc.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_pow.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_irreducible_ddf.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_inlines.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_equal_deg.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_iterated_frobenius_preinv.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_irreducible.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_berlekamp.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_clear.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_is_irreducible_ben_or.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_concat.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_fit_length.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_equal_deg_prob.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_factor_distinct_deg.o  
    CC   ../build/fq_zech_poly_factor/fq_zech_poly_factor_set.o  
make[2]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2/fq_zech_poly_factor'  
    AR   libflint.a  
make[1]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2'  
+ make install  
make[1]: Entering directory '/home/chia/host_entry/submissions/entry/flint-2.5.2'  
make[1]: Nothing to be done for 'static'.  
make[1]: Leaving directory '/home/chia/host_entry/submissions/entry/flint-2.5.2'  
ls: cannot access 'libflint.so*': No such file or directory  
mkdir -p "/home/chia/host_entry/submissions/entry/vdfroot/lib"  
mkdir -p "/home/chia/host_entry/submissions/entry/vdfroot/include/flint"  
cp  ulong_extras.h  long_extras.h  perm.h  fmpz.h  fmpz_vec.h  fmpz_poly.h  fmpq_poly.h  fmpz_mat.h  fmpz_lll.h  mpfr_vec.h  mpfr_mat.h  mpf_vec.h  mpf_mat.h  nmod_vec.h  nmod_poly.h  nmod_poly_factor.h  arith.h  mpn_extras.h  nmod_mat.h  fmpq.h  fmpq_vec.h  fmpq_mat.h  padic.h  fmpz_poly_q.h  fmpz_poly_mat.h  nmod_poly_mat.h  fmpz_mod_poly.h  fmpz_mod_poly_factor.h  fmpz_factor.h  fmpz_poly_factor.h  fft.h  qsieve.h  double_extras.h  d_vec.h  d_mat.h  padic_poly.h  padic_mat.h  qadic.h  fq.h  fq_vec.h  fq_mat.h  fq_poly.h  fq_poly_factor.h  fq_nmod.h  fq_nmod_vec.h  fq_nmod_mat.h  fq_nmod_poly.h  fq_nmod_poly_factor.h  fq_zech.h  fq_zech_vec.h  fq_zech_mat.h  fq_zech_poly.h  fq_zech_poly_factor.h NTL-interface.h flint.h longlong.h config.h gmpcompat.h fft_tuning.h fmpz-conversions.h profiler.h templates.h  fq_vec_templates.h  fq_mat_templates.h  fq_poly_templates.h  fq_poly_factor_templates.h  fq_templates.h "/home/chia/host_entry/submissions/entry/vdfroot/include/flint"  
mkdir -p "/home/chia/host_entry/submissions/entry/vdfroot/include/flint/flintxx"  
cp flintxx/*.h "/home/chia/host_entry/submissions/entry/vdfroot/include/flint/flintxx"  
cp *xx.h "/home/chia/host_entry/submissions/entry/vdfroot/include/flint"  
+ cd ..  
+ export 'CFLAGS=-O2 -march=corei7 -mtune=corei7 -I/home/chia/host_entry/submissions/entry/vdfroot/include'  
+ CFLAGS='-O2 -march=corei7 -mtune=corei7 -I/home/chia/host_entry/submissions/entry/vdfroot/include'  
+ export LDFLAGS=-L/home/chia/host_entry/submissions/entry/vdfroot/lib  
+ LDFLAGS=-L/home/chia/host_entry/submissions/entry/vdfroot/lib  
+ g++ -o vdf -O2 -march=corei7 -mtune=corei7 -I/home/chia/host_entry/submissions/entry/vdfroot/include -L/home/chia/host_entry/submissions/entry/vdfroot/lib vdf.cpp -lflint -lmpfr -lgmp -lgmpxx  
+ sudo cgcreate -g cpuset:/everythingelse  
+ sudo cgset -r cpuset.cpus=0 everythingelse  
+ sudo cgset -r cpuset.mems=0 everythingelse  
+ CPUSET=/sys/fs/cgroup/cpuset  
+ set +x  
moving tasks to cpuset:/everythingelse  
done moving tasks to cpuset:/everythingelse  
+ wc -l /sys/fs/cgroup/cpuset/tasks  
50 /sys/fs/cgroup/cpuset/tasks  
+ wc -l /sys/fs/cgroup/cpuset/everythingelse/tasks  
244 /sys/fs/cgroup/cpuset/everythingelse/tasks  
+ sudo cgcreate -a : -t : -g cpuset:/vdfonly  
+ cgset -r cpuset.cpus=1 vdfonly  
+ cgset -r cpuset.mems=0 vdfonly  
+ cgset -r cpuset.cpu_exclusive=1 vdfonly  
+ sudo tee /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor  
+ echo performance  
++ hostname  
+ echo 'install done on nano'  
install done on nano  
+ exit 0  
  
Install errors:   
Total time for installation: 114.83840537071228  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.91711592674255  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.96696782112122  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.7537226676941  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.98101925849915  
4: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 153.0834174156189  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 153.14163756370544  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.84042596817017  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.92313170433044  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 152.8175859451294  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 153.11787915229797  
Total time for 10 runs: 1529.5435078144073  
I've started takeover  
  
#### Successfully cloned the repository keybase://team/chia_network.nemo1369/track2  
Starting install.sh  
Install output: skylake-unknown-linux-gnu  
Scanning dependencies of target chia_vdf_test  
[ 50%] Building CXX object CMakeFiles/chia_vdf_test.dir/src/main.cpp.o  
[100%] Linking CXX executable chia_vdf_test  
[100%] Built target chia_vdf_test  
  
Install errors:   
Total time for installation: 146.77958393096924  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 141.8264615535736  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 141.73725414276123  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 141.78592228889465  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 141.7925488948822  
4: Starting run.sh  
Iterations: 8388608  
Run Errors: Floating point exception (core dumped)  
  
Incorrect output  
Run Output:   
Total time for entry: 61.73984885215759  
5: Starting run.sh  
Iterations: 8388608  
Timeout of 10 minutes for running expired! Halting the execution  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 141.6470422744751  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 141.80639123916626  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 142.27552556991577  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 142.00012516975403  
Total time for 10 runs: 1796.7131698131561  
  
#### Successfully cloned the repository keybase://team/chatbotvdftest/vdf2  
Starting install.sh  
Install output: Reading package lists...  
Building dependency tree...  
Reading state information...  
libgmp3-dev is already the newest version (2:6.1.2+dfsg-3).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
Reading package lists...  
Building dependency tree...  
Reading state information...  
libflint-dev is already the newest version (2.5.2-18).  
0 upgraded, 0 newly installed, 0 to remove and 189 not upgraded.  
  
Install errors:   
Total time for installation: 2.1767776012420654  
0: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.3897397518158  
1: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.5297417640686  
2: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.7059063911438  
3: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.6523585319519  
4: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.74383997917175  
5: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.35491847991943  
6: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.58416175842285  
7: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.8670516014099  
8: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.63310027122498  
9: Starting run.sh  
Iterations: 8388608  
Run Errors:   
Correct output  
Total time for entry: 182.82131266593933  
Total time for 10 runs: 1826.2823462486267  
  

