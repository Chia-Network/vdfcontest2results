# Entry for Chia Network VDF Competition, 2nd round, Track2

## Introduction
The program implements VDF based on reference implementation. The program doesn't use SIMD instructions as specified in competition rules for Track2. More information about the competition and reference sample code is available at Github: [Chia Network VDF Competition](https://github.com/Chia-Network/vdf-competition).

To build the program, run install.sh script that installs all dependencies and then compiles the code. 

The run.sh script executes the CLI program and it takes following mandatory arguments to calculate VDF:
* discriminent (hex format)
* number of iterations (decimal)

The script should output the result of the VDF, encoded as a, b of the final classgroup element.

## Dependencies
The program depends on [GNU Multi Precision library](https://gmplib.org) and uses it for big integer arithmetic. GMP is distributed under the dual licenses, GNU LGPL v3 and GNU GPL v2. These licenses make the library free to use, share, and improve, and allows user to pass on the result.

A custom binary for GMP static library was created by using [Mercurial GMP repository](https://gmplib.org/repo/) and [build options](https://gmplib.org/manual/Build-Options.html#Build-Options). This library is optimized for competition by supporting the CPU instruction set and of Chia Network's test computer [CPU Pentium G4500](https://en.wikichip.org/wiki/intel/pentium_(2009)/g4500). When compiling library streaming SIMD and advanced vector extensions were disabled.

***WARNING***: Because of these CPU specific optimizations running this entry might crash on computers having different CPU than test computer.

## Description
The implementation of VDF is written in C/C++. 

The classgroup element is implemented as header-only in header file form. Header files defines C++ structures and classes for VDF functionality.

The run script executes the main program that parses input arguments from console terminal, inits the initial element and then uses methods implemented in header file for VDF calculation. After VDF calculation, results are displayed in console terminal.

### Approach

The best implementations for round-1 were studied. Also a study of Antic library that contains NUDUPL algoritm was carried out.

Then following solutions were implemented and tested for performance:

* Bulaiden's NUDUPL and optimized Akasnil reduce algorithm using GMP lib for big integers
* Antic NUDUPL with Antic reducer using original Flint, Antic libs for big integers
* Antic NUDUPL with Antic reducer ported to use GMP lib for big integers
* Antic NUDUPL and different reducers (my own Track1 reducer, antic reducer, optimized akasnil reducer) ported to use GMP lib for big integers.

The Antic NUDUPL + optimized Akasnil reduce algorithm provided best performance. Currently the entry time is 164-165s for the test run in Chia Network's reference machine.

## License
Copyright &copy; [Markku Pulkkinen](https://keybase.io/pulmark). Released under the [Apache Version 2.0 License](https://www.apache.org/licenses/LICENSE-2.0).
