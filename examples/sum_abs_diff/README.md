# Single-Tile Matrix Matrix Multiply

This example runs Parallel Matrix-Matrix Multiplication (A * B = C).
This test is intended to demonstrate different HW/SW optimizations on
a Manycore program.

# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0
Naive Matrix Multiplication using DRAM-Resident data.
To test the effect of unrolling the inner multiplication 
loop, the kernel is executed 6 times with different 
loop unrolling factors 1, 2, 4, 8, 16, 32. Each iteration
is tagged with it's unrolling factor in the stats.

### Version 1
Blocked Matrix Multiplication using SW tile group shared memory.
The Deprecated C version of tile group shared memory is used in this code.

To test the effect of unrolling the inner multiplication 
loop, the kernel is executed 6 times with different 
loop unrolling factors 1, 2, 4, 8, 16, 32. Each iteration
is tagged with it's unrolling factor in the stats.

### Version 2
Blocked Matrix Multiplication using SW tile group shared memory.
The modern C++ version of tile group shared memory, bsg\_striped\_array.hpp 
is used in this code.

To test the effect of unrolling the inner multiplication 
loop, the kernel is executed 6 times with different 
loop unrolling factors 1, 2, 4, 8, 16, 32. Each iteration
is tagged with it's unrolling factor in the stats.

### Version 3
Blocked Matrix Multiplication using HW tile group shared Memory.
The hardware tile group shared memory, along with it's driver
bsg\_shared\_mem.hpp is used in this code.
 
To test the effect of unrolling the inner multiplication 
loop, the kernel is executed 6 times with different 
loop unrolling factors 1, 2, 4, 8, 16, 32. Each iteration
is tagged with it's unrolling factor in the stats.


