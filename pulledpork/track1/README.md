
```
This entry is intended to be a kind of "off the shelf baseline":  
No new asm code, no new math, just see what is possible with libraries already
out there and with minor tweaks to the vdf.cpp reference code.

- use mpir instead of gmp
- select mpir options for max speed
  - minor, turn off any checking for use of FFT, the numbers we are
    using are too small for that
  - try the different build configure options
    - I was initially very confused when in testing I noticed that prebuilt
      libraries for haswell beat the host config, so I tried a whole bunch of
      options just to be thorough (but turned out the main issue is that
      Xeon just confuses the mpir default config)
    - best arch config was, unsurprisingly: skylakeavx
- link to mpir and flint statically
  - this lets the linker determine what is actually used, putting all the
    actually needed pieces closer in memory and with no run-time fixup or 
    resolving needed
- minor tweaks to vdf.cpp
  - remove some NUDPL stuff that is not needed in our case because of prime
    discriminant (which means we always have gcd(A,B)=1)
  - skip stdlib termination of program
- adjust cpu freq scaling
  - default was set to powersave, change to performance
  - even with changes, cpufreq doesn't appear locked at max like the docs
    suggest. quite possible that I misunderstood and was not optimal
- set aside core for vdf program to run without contention
  - have no way to set isolcpus on bootline, so do best to approximate this
  - create a cpuset of all but the last core, try to move every task to it
  - create a cpuset of just the last core for the vdf program
  - launch the vdf program into this cpuset
  - I have not done extensive testing on this and am new to cgroups, so am
    unsure if I even did this correctly

The mpir change had the largest effect, and the cpu freq scaling had a small
but noticeable effect. One nice side effect of the cpu freq scaling change and
cpuset change was that the runs were much more consistent, allowing for lower
noise in testing changes. Basically, each run was now much closer to the "best"
run. I don't expect the cpusets helped much beyond that, since it can only
help by removing distractions.

Regarding the other changes, I've previously seen a small but noticeable
effect of choosing to static link (but I did not check this time), and my
guess is the other changes probably are in the noise.

Note: libflint does its own memory management. I did not look into this, but I
think everything can fit into the data cache, if not, or libflint makes choices
that happend to be poor for our use case, then removing cache misses would be
a fruitful place to look. I guessed the data cache was big enough, but did not
test to verify this assumption.
```

