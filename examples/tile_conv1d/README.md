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

### Version 4

Almost identical to Version 3, but requires the host to compute
the output vector size. Further, removes the assembly optimization
due to it generating poor code.

### Version 5

Switches to a manually-unrolled, untemplated version of the kernel,
making it easier for the compiler.

### Version 6

Removes the `sum` and `a` arrays, which were confusing the compiler
into forcing a writeback into memory rather than keeping them in
registers. Instead, we keep them in four explicit variables marked
`register`. Also converts the "leftover" phase of the unrolling algorithm
to a series of switch statements, which actually performs very well.

### Version 7
Takes the idea from Version 6 and runs with it: converts the whole
loop into a series of switch statements. This seems to be peak
performance: there are no stalls, executes in about 30 cycles per
output element, and has 0.9808 IPC. The only bubbles are due to
branch mispredicts, which are unavoidable. 
