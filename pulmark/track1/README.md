# Entry for Chia Network VDF Competition, 2nd round, Track1

## Introduction
The program implements VDF based on reference implementation and Track1 competition rules. More information about the competition and reference sample code is available at Github: [Chia Network VDF Competition](https://github.com/Chia-Network/vdf-competition).

To build the program, run install.sh script that installs all dependencies and then compiles the code. 

The run.sh script executes the CLI program and it takes following mandatory arguments to calculate VDF:
* discriminent (hex format)
* number of iterations (decimal)

The script should output the result of the VDF, encoded as a, b of the final classgroup element.

## Dependencies
The program depends on [GNU Multi Precision library](https://gmplib.org) and uses it for big integer arithmetic. GMP is distributed under the dual licenses, GNU LGPL v3 and GNU GPL v2. These licenses make the library free to use, share, and improve, and allows user to pass on the result.

A custom binary for GMP static library was created by using [Mercurial GMP repository](https://gmplib.org/repo/) and [build options](https://gmplib.org/manual/Build-Options.html#Build-Options). This library is optimized for competition by supporting the CPU instruction set of Chia Network's test computer [CPU Xeon W-2123](https://en.wikichip.org/wiki/intel/xeon_w/w-2123). When compiling library streaming SIMD and advanced vector extensions were enabled.

***WARNING***: Because of these CPU specific optimizations running this entry might crash on computers having different CPU than test computer.

## Description

The source code for Track1 is exactly the same as for my Track2 competition entry.

Currently the entry time is 161s for the test run in Chia Network's reference machine.

## Future Enhancements
Due to time constraints and no test environment for similar GPU as in Chia Network's test computer for Track1, I was not able to implement as originally planned a big integer library for GPU that would perhaps provide better performance. So this is left for possible future work.

## License
Copyright &copy; [Markku Pulkkinen](https://keybase.io/pulmark). Released under the [Apache Version 2.0 License](https://www.apache.org/licenses/LICENSE-2.0).
