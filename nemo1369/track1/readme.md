# Chia Network VDF

## Implementation Description

This particular implementation contains both optimizations, algorithmic and hardware-driven.

### Algorithmic Optimizations

This particular implementation advances the 'NUDPL'-enabled implementation with removing redundant copying and type-conversions.

Reduction steps are replaced with approximation algorithm proposed in the round 1 with the only difference - 
termination condition threshold is increased to 64 bit. That is done so because 
of NUDPL-generated coefficients are far more smaller, than 2048 bit, the reduction itself is required to "smooth" 
them to fully reduced ones. Such an approximation algorithm usage in combination with NUDPL makes the performance better.

NUDPL itself optimized for particular GCD values := 1, so no redundant divisions are required.

Normalization steps are optimized for handling particular values of already normalized form with no redundant copying.

### Hardware Optimizations

This particular implementation uses the custom-crafted libmpir fork (https://github.com/nemo1369/mpir.git) with 
advanced Skylake architecture support and extensive vector-processing instructions usage.

### Further Improvements

Possible GCD parallel computations showed no significant performance improvements (because of numbers size is 
relatively small and processors amount requirement is relatively huge), but this still can be considered for 
some implementation for GPU with "A 
parallel extended GCD algorithm" by Sidi Mohamed Sedjelmaci usage.

The best implementation of this competition is going to be embedded into a more generic VDF C++ library (with bindings in various languages) by Nil
 Foundation (https://github.com/nilfoundation/vdf). For now it contains this implementation.