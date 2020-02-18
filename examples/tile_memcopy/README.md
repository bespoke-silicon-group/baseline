# Single-Tile Memcopy

This example memcpy on a single tile. This test is intended to demonstrate
the effect of non-blocking loads on program performance.

The kernel code is located in the subdirectories of [kernel](kernel). 

Each kernel copies a list of integers from INPUT into a temporary array on the
tile (temp), adds one to each element, and then copies the result to
OUTPUT. 

Only INPUT->temp and temp->OUTPUT data transfer is profiled to understand the
limitations of memory copy. INPUT/OUTPUT copy is run twice: First, to initialize
the icache and victim cache, and again to understand remote-load
performance. Therefore, Tags 0 (into tile) and 1 (out of tile) can be ignored,
and tags 2 (into tile) and 3 (out of tile) profile data transfer performance.

## Makefile Targets

For a list of all Makefile targets, run `make help`.

## Versions

There are several different versions of this kernel. Each is a subdirectory in
the [kernel](kernel) directory.

In general, tile-to-DRAM data transfer is not a limiting factor on
performance. None of the kernels below stall on this data transfer path.

### Version 0

This version is the baseline. It uses memcpy from RISC-V
[newlib](https://sourceware.org/git/gitweb.cgi?p=newlib-cygwin.git;a=blob;f=newlib/libc/machine/riscv/memcpy.c). It
issues 8 non-blocking remote loads `lw` before issuing `sw` instructions to
store data in the destination buffer. (8 is probably a limitation of RV32E,
which only has 15 GP registers).

This version gets good performance. For an array of 256 4-byte elements and
running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile transfer an IPC of
.56, 562 stall cycles, and 1225 total cycles. The average element load-stall
is 2.19 cycles.

### Version 1

This version demonstrates the pitfall of copying data using a rolled for-loop
for data transfer. Each iteration of the loop loads data from DRAM/VCache and
stores it to DMEM: 1 `lw`, followed by 1 `sw`. Because the `sw` instruction has
a dependency on `lw`, each `sw` stalls for the entire request/response
round-trip.

This version gets poor performance. For an array of 256 4-byte elements and
running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile transfer an IPC of
.26, 3584 stall cycles, and 4887 total cycles. The average element load-stall
is 14 cycles

### Version 2

In theory, this version demonstrates the benefits of unrolling data copying by a
factor of 2 using the `GCC unroll 2` pragma. In theory, each iteration of the
loop loads two elements of data from DRAM/VCache and stores it to DMEM: 2 `lw`
instructions, followed by 2 `sw` instructions. Because the `lw` instructions do
not stall, some pipeline parallelism is present while the first `sw` instruction
is stalled.

However, this is not the case. The following is a snippet of the assembly: 

```
 51c:	0007a683          	lw	x13,0(x15)
 520:	00878793          	addi	x15,x15,8
 524:	00870713          	addi	x14,x14,8
 528:	fed72c23          	sw	x13,-8(x14)
 52c:	ffc7a683          	lw	x13,-4(x15)
 530:	fed72e23          	sw	x13,-4(x14)
```

In this case, the `lw`/`sw` instructions are still interleaved. 

However, this version gets better, but still poor, performance. For an array of 256
4-byte elements and running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile
transfer an IPC of .19, 3840 stall cycles, and 4766 total cycles. The average
element load-stall is 11 cycles

### Version 3

This version demonstrates the benefits of unrolling data copying by a factor of
2 (manually). Each iteration of the loop loads two elements of data from
DRAM/VCache and stores it to DMEM: 2 `lw` instructions, followed by 2 `sw`
instructions. Because the `lw` instructions do not stall, some pipeline
parallelism is present while the first `sw` instruction is stalled.

This version gets better, but still poor, performance. For an array of 256
4-byte elements and running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile
transfer an IPC of .34, 1792 stall cycles, and 2711 total cycles. The average
element load-stall is 7 cycles (half of v1).

### Version 4

This version is a failure. In this version, data is loaded into a temporary
buffer before being stored in local DMEM. The data copy loop is unrolled by a
factor of 4. In theory, this should allow 4 `lw` instructions to be issued
concurrently before the first `sw` causes a stall. However, this is not the case
because gcc reorders instructions and `lw`/`sw` instructions are interleaved.

This version gets poor performance. For an array of 256 4-byte elements and
running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile transfer an IPC of
.17, 3904 stall cycles, and 4696 total cycles. The average element load-stall
is 15 cycles (Worse than v1!).

### Version 5

This version uses the same approach as v4 (above) with substantially
different results. Data is loaded into a temporary buffer before being stored in
local DMEM. The data copy loop is unrolled by a factor of 8. However, in this
version 8 `lw` instructions are issued concurrently before the first `sw` causes
a stall. For some reason, GCC does not reorder instructions (who knows why) and
performance is great.

This version gets good performance, on par with v0. For an array of 256 4-byte
elements and running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile
transfer an IPC of .47, 736 stall cycles, and 1400 total cycles. The average
element load-stall is 2.9 cycles (Worse than v0, but not by much!).

### Version 6

This version uses the same approach as v4 and v5 (above), again, with
substantially different results than either of the previous versions. Data is
loaded into a temporary buffer before being stored in local DMEM. The data copy
loop is unrolled by a factor of 16. In this version 16 `lw` instructions are
issued concurrently before the first `sw` causes a stall, however the `sw`
instructions are not issued in the same order that the dependencies are produced
(for instance the second `sw` instruction depends on the last `lw`
instruction). For some reason, GCC does something different than v4 and v5 and
performance is middling.

This version gets poor performance, on par with v4. For an array of 256 4-byte
elements and running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile
transfer an IPC of .20, 2320 stall cycles, and 2920 total cycles. The average
element load-stall is 9 cycles.

### Version 7

This version uses the same approach as v4-v6, except that data is loaded into a
temporary buffer that is defined as a `float` array before being stored in local
DMEM. This forces the compiler to use `flw` instructions and floating point `f`
registers. The benefit of this is that there is no/little register pressure on
fp registers since they are not used in the RISC-V ABI. 

The data copy loop is unrolled by a factor of 16. In this version 16 `flw`
instructions are issued concurrently before the first `sw` causes a
stall. Unlike v6 and v4 (above) the `fsw` instructions appear in the correct
order relative to their dependencies.

This version gets fantastic performance, better than v0. For an array of 256
4-byte elements and running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile
transfer an IPC of .80, 144 stall cycles, and 744 total cycles. The average
element load-stall is .56 cycles.

### Version 8

This version uses the same approach as v7, with substantially different
results. 

The data copy loop is unrolled by a factor of 32. In this version 32 `flw`
instructions are issued concurrently before the first `sw` causes a stall. Like
v4 and v6 above, the first `fsw` instruction depends on the last `flw`
instruction. It is not clear why GCC is doing this.

This version gets mediocre performance, on par with v3. For an array of 256
4-byte elements and running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile
transfer an IPC of .28, 1440 stall cycles, and 2008 total cycles. The average
element load-stall is 5.6 cycles.

### Version 9

This version uses the same approach as v7 and v8, but uses assembly to specify
the ordering of `flw` and `fsw` instructions. This proves optimal.

The data copy loop is unrolled by a factor of 32. In this version 32 `flw`
instructions are issued concurrently before the first `sw` causes a stall. As
expected, the `fsw` instructions are ordered relative to their dependent `flw`
instructions.

This version gets the best performance. For an array of 256 4-byte elements and
running on tile (0,0) of a 4x4 manycore DRAM/VCache -> Tile transfer an IPC of
.9967, 0 stall cycles, and 600 total cycles. The average element load-stall is
0 cycles.

### Version 10

This is identical to v9, except that it wraps standard memcopy for
non-word-aligned transfers. This is the current, best definition of bsg_memcpy.
