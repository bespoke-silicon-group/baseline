# Single-Tile Matrix Matrix Multiply

This example runs Vector-Vector Addition (A + B = C) on:
- `v0`: a single tile (1x1 grid of 1x1 tile group)
- `v1`: a single 1D tile group (1x1 grid of 2x1 tile group)
- `v2`: a single 2D tile group (1x1 grid of 2x2 tile group)
- `v3`: a 1D grid of 2D tile groups (4x1 grid of 2x2 tile groups)

This test is intended to demonstrate how to use multiple tile groups each 
consisting of multiple tiles, how to distribute the work among tiles, and
how to use the CUDA-Lite symbols to identify a tile.

The kernel code is located in the subdirectories of [kernel](kernel). The actual
vector-vector additioncode is in the header file
[kernel/include/vector_add.hpp](kernel/include/vector_add.hpp). 


# Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

### Version 0

This is a vanilla vector addition implementation on a 1x1 grid of 1x1 tile group.
The entire addition is perfomed by a single tile, no work distribution is done.
Calls to bsg_print_stat_start/end are used to measure performance.

### Version 1

This is a vanilla vector addition implementation on a 1x1 grid of 2x1 tile group.
The entire work is done by one 1D tile group, and is distributed among tiles based
on bsg_x (tile's X cooridnate inside tile group).
Calls to bsg_print_stat_start/end are used to measure performance.

### Version 2

This is a vanilla vector addition implementation on a 1x1 grid of 4x4 tile group.
The entire work is done by one 2D tile group, and is distributed among tiles based
on bsg_id (tile's flat ID inside tile group, deduced from tile's X/Y coordinates).
Calls to bsg_print_stat_start/end are used to measure performance.

### Version 3

This is a vanilla vector addition implementation on a 4x1 grid of 2x2 tile group.
Work is distributed among tile groups. Programmer defines the share of each 
tile group by specifying block_size_x, and grid dimensions or the number of tile 
groups needed is calculated by evenly dividing the entire work (or the WIDTH of 
vector) by each tile group's share (block_size_x). Work in a tile group is 
divided among tiles based on bsg_id (tile's flat id inside tile group, deduced 
from tile's X/Y coordinates inside tile group). Calls to bsg_print_stat_start/end 
are used to measure performance.

As the nature of the compuation is one dimensional vector addition, there is no 
need to launch a 2D grid of tile groups, as dividing the work is an unnessary 
overhead. For examples of launching a 2D grid of tile groups, see matrix multiplication.
