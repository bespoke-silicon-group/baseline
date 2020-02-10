# Single-Tile Matrix Matrix Multiply

This example runs Matrix-Matrix Multiplication (A * B = C) on a single
tile. This test is intended to demonstrate different optimizations on
a Manycore program.

The kernel code is located in the subdirectories of [kernel](kernel). The actual
matrix-multiplication code is in the header file
[kernel/include/matrix_multiply.hpp](kernel/include/matrix_multiply.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

This is a vanilla matrix multiply implementation using DRAM-Resident data. A set
of nested loops compute the resulting matrix. Calls to bsg_print_stat_start/end
are used to measure performance

Optimizations: 
  - None

The profiling results from this kernel should show instruction cache misses
caused by the first call to bsg_print_stat_start/end.

### Version 1

This is a vanilla matrix multiply implementation using DRAM-Resident data. A set
of nested loops compute the resulting matrix. Calls to bsg_print_stat_start/end
are used to measure performance

Optimizations: 
  - The first call to bsg_print_stat_start/end is discarded to tag
0. The non-zero tags should have no instruction cache misses.

### Version 2

This is a vanilla matrix multiply implementation using DMEM-Resident data. 

Optimizations: 
  - The first call to bsg_print_stat_start/end is discarded to tag
0. The non-zero tags should have no instruction cache misses.
  - Matrix data is resident in DMEM

### Version 3

This is a matrix multiply implementation using DMEM-Resident data. In
this implementation, Matrix B has been transposed 

Optimizations: 
  - The first call to bsg_print_stat_start/end is discarded to tag
0. The non-zero tags should have no instruction cache misses.
  - Matrix data is resident in DMEM
  - B is Transposed

### Version 4

This is a matrix multiply implementation using DMEM-Resident data. In this
implementation, additions are used instead of multiplies to create access
indices for A and B.

Optimizations: 
  - The first call to bsg_print_stat_start/end is discarded to tag
0. The non-zero tags should have no instruction cache misses.
  - Matrix data is resident in DMEM
  - B is Transposed
  - Integer multiplies have been removed from the code

### Version 5, 6, 7

This is a matrix multiply implementation using DMEM-Resident data. In these
implementations, the row-column dot product has been unrolled and 2, 4, and 8
results are computed simultaneously.

Optimizations: 
  - The first call to bsg_print_stat_start/end is discarded to tag
0. The non-zero tags should have no instruction cache misses.
  - Matrix data is resident in DMEM
  - B is Transposed
  - Integer multiplies have been removed from the code
  - The second loop is unrolled


### Version 8

This is a matrix multiply implementation using DMEM-Resident data. In these
implementations, the result variables of the unrolled dot products are
initialized using inline assembly to overcome an issue in GCC.

Optimizations: 
  - The first call to bsg_print_stat_start/end is discarded to tag
0. The non-zero tags should have no instruction cache misses.
  - Matrix data is resident in DMEM
  - B is Transposed
  - Integer multiplies have been removed from the code
  - The second loop is unrolled
  - Results are optimized using inline assembly