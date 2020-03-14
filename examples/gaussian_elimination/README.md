# Gaussian Elimination

This example runs the gaussian elimination on an input MxN matrix. 
Input matrix represents a set of coefficients for an N-dimension linear 
equation. The purpose of this kernel is to transform the input matrix into 
a matrix where the triangle portion of the matrix below the diameter is zero.
Result is an MxN matrix.                                                   

Because of the nature of the application and the need for synchronization 
among threads, the entire operation has to be done within one tile group. 
Therefore, a single tile group has to handle the entire matrix, and the block 
size (a tile group's workload) is set to the matrix height. 

The kernel code is located in the subdirectories of [kernel](kernel). The actual
sum of absolute differences code is in the header file
[kernel/include/sum_abs_diff.hpp](kernel/include/sum_abs_diff.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

In this version, each thread is responsible for calculating a row in 
each step of the computation. Each tile in the tile group can be 
responsible for multple threads (i.e. calculating multiple rows).
The second loop of the sequential compuation, which loops over all
rows to calculate the new values in each step, is broken and divided 
among tiles. Each step of the outter loop needs a barrier to sync 
the new values of all rows.



