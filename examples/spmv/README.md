# Sparse Matrix Dense Vector Multiplication Kernel

This example runs the sparse matrix dense vector multiplication kernel.
The kernel performs a multiplication between a sparse matrix and a 
dense vector. Dense vector is represented by two vectors, a list of 
non-zero indices, and a list of non-zero values cooresponding to 
those indicis. Result is a sparse vector.

The kernel code is located in the subdirectories of [kernel](kernel). The actual
sum of absolute differences code is in the header file
[kernel/include/sum_abs_diff.hpp](kernel/include/sum_abs_diff.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

Initial version. Matrix is divided by it's Y dimensions among tile groups and 
tiles in the tile group, and each tile group performs block_size number of 
row column multiplications and stores block_size results into the sparse result
vector.


### Version 1

Sparse matrix and dense vector dimensions are templatized in the kernel to allow
for better compiler optimization.


### Version 2

This version loads the dense vector into tile group shared memory, 
to reduce the redundant access latency to the dense vector. 
This version also uses the new template barrier library.

