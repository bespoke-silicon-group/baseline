# Single-Tile Matrix Matrix Multiply

This example runs Vector-Vector Addition (A + B = C) on:
- `v0`: a single 1D tille group (1x1 grid of 8x4 tile group) compiled with gcc 
- `v1`: a single 1D tille group (1x1 grid of 8x4 tile group) compiled with llvm 
- `v2`: a single 1D tille group (1x1 grid of 8x4 tile group) compiled with llvm, uses remote keyword

Makefile.llvm does llvm compilation on versions v1 and v2
Makefile.gcc does gcc compilation on version v0
