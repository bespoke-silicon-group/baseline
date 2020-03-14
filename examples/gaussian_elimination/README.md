# Gaussian Elimination

This example runs the gaussian elimination on an input MxN matrix. 
Input matrix represents a set of coefficients for an N-dimension linear 
equation. The purpose of this kernel is to transform the input matrix into 
a matrix where the triangle portion of the matrix below the diameter is zero.
Result is an MxN matrix.                                                   

The kernel code is located in the subdirectories of [kernel](kernel). The actual
sum of absolute differences code is in the header file
[kernel/include/sum_abs_diff.hpp](kernel/include/sum_abs_diff.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

Initial Version



