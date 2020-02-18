# Single-Tile Conv1D

This example runs Conv1D (A (*) F = O) on a single tile. This test is
intended to demonstrate different optimizations on a Manycore program.

The kernel code is located in the subdirectories of [kernel](kernel). The actual
matrix-multiplication code is in the header file
[kernel/include/matrix_multiply.hpp](kernel/include/matrix_multiply.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

This is a naive implementation on DMEM resident data.

Optimizations: 
  - None

### Version 1

This implementation uses a slightly cleverer method for indexing the
input array that is amenable to unrolling. Instead of tracking an
input index for data, it uses the filter index and the output
index. (Though it has no effect)

This may not work well with stepping.

### Version 2

This is implementation unrolls the outer loop to compute multiple
output pixels concurrently. 

### Version 3

This version unrolls the outer loop, but also uses assembly to
initialize the sum array.