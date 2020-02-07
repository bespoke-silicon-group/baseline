# Single-Tile Matrix Matrix Multiply

This example runs tile group shared memory reduction on a 1x1 grid 
of tile groups. All elements in shared memory are added together in 
a parallel manner and stored in the first element of the array. 
A[0] <-- Sum (A[i] for i from 0 to N)

The tiles first load the array from DRAM into tile group shared memory,
then perform reduction by cutting the array in half at each iteration,
thus performing the sum of N elements in O(logN).

An example reduction on an array of 8 is shown below:
![alt text](https://github.com/drichmond/baseline/blob/reduction_shared_mem/examples/reduction_shared_mem/images/reduction.PNG "Reduction Example")

Reduction is performed in a loop, starting from an offset of 1 and a multiplicand of 2:
- For every element with index multiplicand of 2: A[i] <-- A[i] + A[i+1]
- Perform barrier 
- For every element with index multiplicand of 4: A[i] <-- A[i] + A[i+2]
- Perform barrier 
- For every element with index multiplicand of 8: A[i] <-- A[i] + A[i+4]
- Perform barrier 
- .... Continue until offset is larger that array size ....
- Perform barrier 
- Sum of the entire array is stored in the first element

Remember, reduction is only allowed inside a single tile group, as tiles in 
different tile groups cannot communicated through tile group shared memory. 
Thus, the grid dimensions in this test is always pre-fixed at 1x1, and the 
entire operation must happen inside a single tile group.

This test is intended to demonstrate the use and benefit of tile group shared 
memory.

For an example on how reduction works, see the comments in the kernel code.

The kernel code is located in the subdirectories of [kernel](kernel). The actual
shared memory recution code is in the header file
[kernel/include/reduction_shared_mem.hpp](kernel/include/reduction_shared_mem.hpp). 


# Makefile Targets

- `analysis`: Runs all kernel versions produces profiler results. Results are
  placed in each kernel's version directory

- `default`: Run the default kernel version and produce profiling results
  (defined in [Makefile](Makefile)

- `all`: Run both of the rules listed above.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

In this version, number of tiles launched (i.e. the number of tiles in a tile group) 
is equal to the size of the array. Therefore, each tile is responsible for a single 
element in the array. Each tile's element is deduced from its flat ID inside tile 
group, i.e. bsg_id, which is calculated from tile's X/Y coordinates insdie tile group.

Once the reduction is complete, only a single tile stores the result back into the DRAM. 

As each tile is only responsible for one element, the size of the array is bound to 
the maximum number of tiles in a single tile group. Version 2 solves this problem.

### Version 1

In this version, each tile can be responsible for multiple elements. The entire work 
(i.e. the size of the array to be reduced) is divided evenly among tiles based on the 
number of tiles in a tile group.

Each tile is responsible for N / (bsg_tiles_X * bsg_tiles_Y) elements.

At each synchronous section, a thread loop is wraped around the code, with each 
iteration representing a virtual thread, or a single element of the vector. 
The thread loop bounds is calculated based on the tile's ID inside tile group 
bsg_id, and each tile then accesses elements based on the loop iteration, instead 
of its ID.

Once the reduction is complete, only a single tile stores the result back into 
the DRAM. 

In this version, there are no limits on the size of the array to be reduced, as 
long as it fits inside tile group shared memory.

