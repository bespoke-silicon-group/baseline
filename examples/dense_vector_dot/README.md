# Dense Vector Vector Dot Product Kernel

This example runt the dense vector vector dot product kernel.
Each input vector is represented by two arrays, the array of index 
of non-zero valeus, and the array with the corresponding values.
The output is a single number replresenting the dot product.

The kernel code is located in the subdirectories of [kernel](kernel). The actual
sum of absolute differences code is in the header file
[kernel/include/sum_abs_diff.hpp](kernel/include/sum_abs_diff.hpp). 

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

This is sequential version, a single tile handles the entire dot product.



