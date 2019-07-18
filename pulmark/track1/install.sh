#!/bin/sh
###############################################################################
# Installation script using GNU g++ compiler
#
# Dependencies: libgmp
#
# g++ --version
# g++ -march=native -Q --help=target | egrep -- '-march=|-mtune' | cut -f3
###############################################################################

## install dynamic libgmp library
## sudo apt-get install libgmp3-dev

# Build-dynamic: dynamic linking, O2 optimizations
###############################################################################
#g++ -o a.out -no-pie -pthread -pipe -Wall -O2 -march=native -mtune=native \
#-fprefetch-loop-arrays --param max-inline-insns-single=2000 -std=c++1y \
#main.cpp -lgmp
###############################################################################
# Build-static: static linking, skylake server (avx512) march for libgmp, 
# O2 optimizations
###############################################################################
g++ -o a.out -no-pie -pthread -pipe -Wall -O2 -march=native -mtune=native \
-fprefetch-loop-arrays --param max-inline-insns-single=2000 -std=c++1y \
main.cpp -Wl,-Bstatic -L./lib -l:libgmp-O2-skylake-avx512.a -Wl,-Bdynamic
