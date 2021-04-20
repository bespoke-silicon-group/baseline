	.text
	.file	"kernel.cpp"
	.file	1 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h"
	.file	2 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h"
	.file	3 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/debug/debug.h"
	.file	4 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/stdlib.h"
	.file	5 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/bits/std_abs.h"
	.file	6 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/cstdlib"
	.file	7 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/llvm/llvm-install/lib/clang/10.0.0/include/stddef.h"
	.file	8 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/bits/exception_ptr.h"
	.file	9 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/riscv32-unknown-elf-dramfs/bits/c++config.h"
	.file	10 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/math.h"
	.file	11 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/bsg_manycore/software/riscv-tools/riscv-install/bin/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/cmath"
	.globl	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_ # -- Begin function _Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
	.p2align	2
	.type	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_,@function
_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_: # @_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
.Lfunc_begin0:
	.loc	2 174 0                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:174:0
	.cfi_sections .debug_frame
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x10
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x11
	addi	sp, sp, -32
	.cfi_def_cfa_offset 32
	sw	ra, 28(sp)
	sw	s0, 24(sp)
	sw	s1, 20(sp)
	sw	s2, 16(sp)
	sw	s3, 12(sp)
	sw	s4, 8(sp)
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	.cfi_offset s1, -12
	.cfi_offset s2, -16
	.cfi_offset s3, -20
	.cfi_offset s4, -24
	mv	s0, a0
.Ltmp0:
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 175 39 prologue_end   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:39
	lbu	a2, 0(a0)
	.loc	2 175 64 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:64
	lbu	a0, 1(a0)
	mv	s1, a1
.Ltmp1:
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	.loc	2 175 53                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:53
	add	a0, a0, a2
	.loc	2 175 76                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:76
	srli	s2, a0, 1
.Ltmp2:
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	.loc	2 94 66 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:94:66
	lui	a7, %hi(__bsg_y)
	lw	a1, %lo(__bsg_y)(a7)
.Ltmp3:
	.loc	2 177 39                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:177:39
	lbu	a5, 0(s1)
.Ltmp4:
	.loc	2 94 66                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:94:66
	slli	a1, a1, 24
	slli	a3, s2, 18
	or	a4, a3, s0
	or	a1, a4, a1
	.loc	2 98 39                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:98:39
	lui	a6, %hi(__bsg_x)
	lw	a4, %lo(__bsg_x)(a6)
.Ltmp5:
	.loc	2 177 64                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:177:64
	lbu	a0, 1(s1)
.Ltmp6:
	.loc	2 98 45                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:98:45
	sub	a2, a4, a2
	lui	a4, 131072
	.loc	2 94 66                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:94:66
	or	a1, a1, a4
.Ltmp7:
	#DEBUG_VALUE: bsg_row_barrier_sync:p_remote_barrier <- $x11
	.loc	2 98 9                  # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:98:9
	add	a1, a1, a2
.Ltmp8:
	.loc	2 0 9 is_stmt 0         # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:9
	addi	a2, zero, 1
	.loc	2 98 72                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:98:72
	sb	a2, 2(a1)
.Ltmp9:
	.loc	2 188 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:188:13
	lw	a6, %lo(__bsg_x)(a6)
.Ltmp10:
	.loc	2 177 53                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:177:53
	add	a0, a0, a5
	.loc	2 177 76 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:177:76
	srli	a1, a0, 1
.Ltmp11:
	#DEBUG_VALUE: bsg_row_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_row_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	.loc	2 188 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:188:13
	bne	a6, s2, .LBB0_6
.Ltmp12:
# %bb.1:                                # %if.then
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x9
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x11
	.loc	2 105 66                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:105:66
	slli	a0, a1, 24
	.loc	2 108 33                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:108:33
	lbu	a2, 1(s0)
	.loc	2 108 56 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:108:56
	lbu	a5, 0(s0)
	.loc	2 105 66 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:105:66
	or	a3, a3, s1
	or	a0, a3, a0
	.loc	2 108 45                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:108:45
	sub	a3, a2, a5
.Ltmp13:
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x13
	.loc	2 105 66                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:105:66
	or	a2, a0, a4
.Ltmp14:
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x12
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: poll_range:range <- $x13
	.loc	2 210 17                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:210:17
	bltz	a3, .LBB0_5
.Ltmp15:
# %bb.2:                                # %for.body.i.i.preheader
	#DEBUG_VALUE: poll_range:range <- $x13
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x9
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 17 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:17
	mv	a5, zero
.Ltmp16:
.LBB0_3:                                # %for.body.i.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: poll_range:range <- $x13
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x9
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	mv	a4, a5
.Ltmp17:
	#DEBUG_VALUE: poll_range:i <- $x14
	.loc	2 211 30 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:211:30
	add	a0, s0, a5
	lbu	a0, 2(a0)
.Ltmp18:
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x14
	.loc	2 0 30 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:30
	mv	a5, zero
.Ltmp19:
	.loc	2 211 30                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:211:30
	beqz	a0, .LBB0_3
.Ltmp20:
# %bb.4:                                # %for.cond.i.i
                                        #   in Loop: Header=BB0_3 Depth=1
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x14
	#DEBUG_VALUE: poll_range:range <- $x13
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x9
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 210 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:210:41
	addi	a5, a4, 1
.Ltmp21:
	#DEBUG_VALUE: poll_range:i <- $x15
	.loc	2 210 17 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:210:17
	bne	a4, a3, .LBB0_3
.Ltmp22:
.LBB0_5:                                # %_Z20bsg_col_barrier_syncP17_bsg_row_barrier_P17_bsg_col_barrier_ii.exit
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x9
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 111 39 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:111:39
	lui	a0, %hi(__bsg_y)
	.loc	2 111 57 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:111:57
	lbu	a3, 0(s1)
.Ltmp23:
	.loc	2 111 39                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:111:39
	lw	a0, %lo(__bsg_y)(a0)
	.loc	2 111 45                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:111:45
	sub	a0, a0, a3
	.loc	2 111 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:111:9
	add	a0, a2, a0
	addi	a2, zero, 1
.Ltmp24:
	.loc	2 111 72                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:111:72
	sb	a2, 2(a0)
.Ltmp25:
	.loc	2 191 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:191:13
	lui	a0, %hi(__bsg_x)
	lw	a6, %lo(__bsg_x)(a0)
.Ltmp26:
.LBB0_6:                                # %if.end
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 191 36 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:191:36
	bne	a6, s2, .LBB0_16
.Ltmp27:
# %bb.7:                                # %if.end
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 0                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	lw	a0, %lo(__bsg_y)(a7)
	.loc	2 191 36                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:191:36
	bne	a0, a1, .LBB0_16
.Ltmp28:
# %bb.8:                                # %if.then8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	.loc	2 124 33 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:124:33
	lbu	s3, 1(s1)
	.loc	2 124 56 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:124:56
	lbu	s4, 0(s1)
	.loc	2 124 45                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:124:45
	sub	a0, s3, s4
.Ltmp29:
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x9
	#DEBUG_VALUE: poll_range:range <- $x10
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x10
	.loc	2 210 17 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:210:17
	bltz	a0, .LBB0_13
.Ltmp30:
# %bb.9:                                # %for.body.i.i49.preheader
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x10
	#DEBUG_VALUE: poll_range:range <- $x10
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x9
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 17 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:17
	mv	a2, zero
.Ltmp31:
.LBB0_10:                               # %for.body.i.i49
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x10
	#DEBUG_VALUE: poll_range:range <- $x10
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x9
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	mv	a1, a2
.Ltmp32:
	#DEBUG_VALUE: poll_range:i <- $x11
	.loc	2 211 30 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:211:30
	add	a2, s1, a2
	lbu	a3, 2(a2)
.Ltmp33:
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x11
	.loc	2 0 30 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:30
	mv	a2, zero
.Ltmp34:
	.loc	2 211 30                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:211:30
	beqz	a3, .LBB0_10
.Ltmp35:
# %bb.11:                               # %for.cond.i.i45
                                        #   in Loop: Header=BB0_10 Depth=1
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x10
	#DEBUG_VALUE: poll_range:range <- $x10
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x9
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 210 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:210:41
	addi	a2, a1, 1
.Ltmp36:
	#DEBUG_VALUE: poll_range:i <- $x12
	.loc	2 210 17 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:210:17
	bne	a1, a0, .LBB0_10
.Ltmp37:
# %bb.12:                               # %for.body.preheader.i
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x10
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_alert:i <- 0
	.loc	2 131 9 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:131:9
	addi	a2, a0, 1
	addi	a0, s1, 2
.Ltmp38:
	.loc	2 132 40                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:132:40
	mv	a1, zero
	call	memset
.Ltmp39:
	#DEBUG_VALUE: bsg_col_barrier_alert:i <- undef
.LBB0_13:                               # %for.end.i
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 0 is_stmt 0         # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	lui	a0, %hi(__bsg_x)
	lw	a6, %lo(__bsg_x)(a0)
.Ltmp40:
	#DEBUG_VALUE: alert_col:i <- $x20
	#DEBUG_VALUE: alert_col:p_col_b <- $x9
	.loc	2 219 9 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:219:9
	bltu	s3, s4, .LBB0_16
.Ltmp41:
# %bb.14:                               # %for.body.lr.ph.i11.i
	#DEBUG_VALUE: alert_col:p_col_b <- $x9
	#DEBUG_VALUE: alert_col:i <- $x20
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_col:i <- $x20
	.loc	2 0 0 is_stmt 0         # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	slli	a0, a6, 18
	or	a0, a0, s1
.Ltmp42:
	.loc	2 219 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:219:9
	addi	a1, s4, -1
	slli	a3, s4, 24
	lui	a7, 131072
	addi	a5, zero, 1
	lui	a2, 4096
.Ltmp43:
.LBB0_15:                               # %for.body.i13.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: alert_col:p_col_b <- $x9
	#DEBUG_VALUE: alert_col:i <- $x20
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_col:i <- undef
	.loc	2 220 55 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:220:55
	or	a4, a0, a3
	or	a4, a4, a7
.Ltmp44:
	#DEBUG_VALUE: alert_col:p_remote_barrier <- $x14
	.loc	2 223 47                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:223:47
	sw	a5, 4(a4)
.Ltmp45:
	#DEBUG_VALUE: alert_col:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	2 219 44                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:219:44
	addi	a1, a1, 1
	add	a3, a3, a2
.Ltmp46:
	.loc	2 219 9 is_stmt 0       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:219:9
	bltu	a1, s3, .LBB0_15
.Ltmp47:
.LBB0_16:                               # %if.end9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 194 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:194:13
	bne	a6, s2, .LBB0_25
.Ltmp48:
# %bb.17:                               # %if.then11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	.loc	2 144 33                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:144:33
	lbu	a0, 1(s0)
	.loc	2 144 56 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:144:56
	lbu	a1, 0(s0)
.Ltmp49:
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:x_range <- undef
	.loc	2 0 56                  # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:56
	addi	a2, s1, 4
	addi	a3, zero, 1
.Ltmp50:
.LBB0_18:                               # %while.cond.i.i57
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x9
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x9
	.loc	1 121 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:121:41
	#APP
	lr.w    a4,0(a2)

	#NO_APP
.Ltmp51:
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x14
	#DEBUG_VALUE: bsg_lr:tmp <- $x14
	.loc	2 243 13                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:243:13
	beq	a4, a3, .LBB0_20
.Ltmp52:
# %bb.19:                               # %if.else.i.i59
                                        #   in Loop: Header=BB0_18 Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x14
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x9
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr_aq:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x9
	.loc	1 122 41                # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:122:41
	#APP
	lr.w.aq a4,0(a2)

	#NO_APP
.Ltmp53:
	#DEBUG_VALUE: bsg_lr_aq:tmp <- $x14
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x14
	.loc	2 246 17                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:246:17
	bne	a4, a3, .LBB0_18
.Ltmp54:
.LBB0_20:                               # %_Z18bsg_wait_local_intPii.exit.i
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	.loc	2 153 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:153:9
	bltu	a0, a1, .LBB0_22
.Ltmp55:
# %bb.21:                               # %for.body.preheader.i61
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	sub	a0, a0, a1
	addi	a2, a0, 1
	addi	a0, s0, 2
.Ltmp56:
	.loc	2 154 40                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:154:40
	mv	a1, zero
	call	memset
.Ltmp57:
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- undef
.LBB0_22:                               # %for.end.i63
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 157 33                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:157:33
	sw	zero, 4(s1)
.Ltmp58:
	#DEBUG_VALUE: alert_row:p_row_b <- $x8
	.loc	2 230 27                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:230:27
	lbu	a3, 0(s0)
.Ltmp59:
	#DEBUG_VALUE: alert_row:i <- $x13
	.loc	2 230 57 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:230:57
	lbu	a0, 1(s0)
.Ltmp60:
	.loc	2 230 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:230:9
	bltu	a0, a3, .LBB0_25
.Ltmp61:
# %bb.23:                               # %for.body.lr.ph.i.i66
	#DEBUG_VALUE: alert_row:i <- $x13
	#DEBUG_VALUE: alert_row:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x9
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x9
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_row:i <- $x13
	.loc	2 0 0                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	lui	a1, %hi(__bsg_y)
	lw	a1, %lo(__bsg_y)(a1)
	slli	a1, a1, 24
	or	a1, a1, s0
.Ltmp62:
	.loc	2 230 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:230:9
	addi	a2, a3, -1
	slli	a3, a3, 18
.Ltmp63:
	.loc	2 0 9                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:9
	lui	a6, 131072
	addi	a5, zero, 1
	lui	s1, 64
.Ltmp64:
.LBB0_24:                               # %for.body.i.i73
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: alert_row:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_row:i <- undef
	.loc	2 231 55 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:231:55
	or	a4, a1, a3
	or	a4, a4, a6
.Ltmp65:
	#DEBUG_VALUE: alert_row:p_remote_barrier <- $x14
	.loc	2 234 47                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:234:47
	sw	a5, 4(a4)
.Ltmp66:
	#DEBUG_VALUE: alert_row:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	2 230 44                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:230:44
	addi	a2, a2, 1
	add	a3, a3, s1
.Ltmp67:
	.loc	2 230 9 is_stmt 0       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:230:9
	bltu	a2, a0, .LBB0_24
.Ltmp68:
.LBB0_25:                               # %if.end12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	.loc	2 0 9                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:9
	addi	a0, s0, 4
	addi	a1, zero, 1
.Ltmp69:
.LBB0_26:                               # %while.cond.i.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	.loc	1 121 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:121:41
	#APP
	lr.w    a2,0(a0)

	#NO_APP
.Ltmp70:
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	#DEBUG_VALUE: bsg_lr:tmp <- $x12
	.loc	2 243 13                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:243:13
	beq	a2, a1, .LBB0_28
.Ltmp71:
# %bb.27:                               # %if.else.i.i
                                        #   in Loop: Header=BB0_26 Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr_aq:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	.loc	1 122 41                # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:122:41
	#APP
	lr.w.aq a2,0(a0)

	#NO_APP
.Ltmp72:
	#DEBUG_VALUE: bsg_lr_aq:tmp <- $x12
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	.loc	2 246 17                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:246:17
	bne	a2, a1, .LBB0_26
.Ltmp73:
.LBB0_28:                               # %_Z13bsg_tile_waitP17_bsg_row_barrier_.exit
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 168 31                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:168:31
	sw	zero, 4(s0)
.Ltmp74:
	.loc	2 203 1                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:203:1
	lw	s4, 8(sp)
	lw	s3, 12(sp)
	lw	s2, 16(sp)
.Ltmp75:
	lw	s1, 20(sp)
	lw	s0, 24(sp)
.Ltmp76:
	lw	ra, 28(sp)
	addi	sp, sp, 32
	ret
.Ltmp77:
.Lfunc_end0:
	.size	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_, .Lfunc_end0-_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
	.cfi_endproc
                                        # -- End function
	.section	.sdata,"aw",@progbits
	.p2align	2               # -- Begin function dijkstra
.LCPI1_0:
	.word	2139095040              # float +Inf
	.text
	.globl	dijkstra
	.p2align	2
	.type	dijkstra,@function
dijkstra:                               # @dijkstra
.Lfunc_begin1:
	.file	12 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/baseline/examples/dijkstra/kernel/dijkstra-set/kernel.cpp"
	.loc	12 29 0                 # kernel/dijkstra-set/kernel.cpp:29:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: dijkstra:g_mem <- $x10
	#DEBUG_VALUE: dijkstra:root <- $x11
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	addi	sp, sp, -64
	.cfi_def_cfa_offset 64
	sw	ra, 60(sp)
	sw	s0, 56(sp)
	sw	s1, 52(sp)
	sw	s2, 48(sp)
	sw	s3, 44(sp)
	sw	s4, 40(sp)
	sw	s5, 36(sp)
	sw	s6, 32(sp)
	sw	s7, 28(sp)
	sw	s8, 24(sp)
	sw	s9, 20(sp)
	sw	s10, 16(sp)
	sw	s11, 12(sp)
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	.cfi_offset s1, -12
	.cfi_offset s2, -16
	.cfi_offset s3, -20
	.cfi_offset s4, -24
	.cfi_offset s5, -28
	.cfi_offset s6, -32
	.cfi_offset s7, -36
	.cfi_offset s8, -40
	.cfi_offset s9, -44
	.cfi_offset s10, -48
	.cfi_offset s11, -52
	lui	s1, 64
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dijkstra:root <- $x11
	#DEBUG_VALUE: dijkstra:g_mem <- $x10
.Ltmp78:
	.loc	12 30 22 prologue_end   # kernel/dijkstra-set/kernel.cpp:30:22
	lw	a6, 0(a0)
.Ltmp79:
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	lw	s4, 4(a0)
.Ltmp80:
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	lw	a7, 8(a0)
.Ltmp81:
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	lw	t0, 12(a0)
.Ltmp82:
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	lw	s6, 16(a0)
.Ltmp83:
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	.loc	12 31 5                 # kernel/dijkstra-set/kernel.cpp:31:5
	slli	a0, a1, 2
.Ltmp84:
	add	s0, a3, a0
	.loc	12 31 20 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:31:20
	sw	zero, 0(s0)
	.loc	12 32 5 is_stmt 1       # kernel/dijkstra-set/kernel.cpp:32:5
	add	a0, a4, a0
	.loc	12 32 16 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:32:16
	sw	a1, 0(a0)
.Ltmp85:
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 0 32] undef
	.loc	12 44 5 is_stmt 1       # kernel/dijkstra-set/kernel.cpp:44:5
	lui	a0, %hi(__bsg_grp_org_y)
	lw	a0, %lo(__bsg_grp_org_y)(a0)
	lui	t2, %hi(__bsg_y)
	lw	a1, %lo(__bsg_y)(t2)
.Ltmp86:
	.loc	12 0 5 is_stmt 0        # kernel/dijkstra-set/kernel.cpp:0:5
	addi	s3, s1, -16
	.loc	12 44 5                 # kernel/dijkstra-set/kernel.cpp:44:5
	add	a0, a1, a0
	slli	a0, a0, 24
	lui	a1, 258048
	lui	t3, %hi(__bsg_grp_org_x)
	lw	s1, %lo(__bsg_grp_org_x)(t3)
	lui	t5, %hi(__bsg_x)
	lw	s0, %lo(__bsg_x)(t5)
	and	a0, a0, a1
	add	a1, s0, s1
	slli	a1, a1, 18
	lui	t4, 4032
	lui	s2, %hi(__bsg_tile_group_id)
	lw	s1, %lo(__bsg_tile_group_id)(s2)
	and	a1, a1, t4
	slli	s1, s1, 4
	and	s1, s1, s3
	or	a0, a0, a1
	or	a0, a0, s1
	lui	a1, 524288
	or	a0, a0, a1
.Ltmp87:
	#DEBUG_VALUE: val <- $x10
	.loc	12 0 5                  # kernel/dijkstra-set/kernel.cpp:0:5
	lui	t6, 262401
.Ltmp88:
	#DEBUG_VALUE: ptr <- undef
	.loc	12 44 5                 # kernel/dijkstra-set/kernel.cpp:44:5
	sw	a0, -756(t6)
.Ltmp89:
	#DEBUG_VALUE: empty:this <- undef
	.loc	12 46 5 is_stmt 1       # kernel/dijkstra-set/kernel.cpp:46:5
	beqz	a6, .LBB1_25
.Ltmp90:
# %bb.1:                                # %for.cond.preheader.lr.ph
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	blez	a6, .LBB1_17
.Ltmp91:
# %bb.2:                                # %for.cond.preheader.us.preheader
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 0 0 is_stmt 0        # kernel/dijkstra-set/kernel.cpp:0:0
	addi	s8, a6, -1
	slli	a0, s8, 2
	add	s5, a7, a0
	lui	a0, %hi(.LCPI1_0)
	addi	a0, a0, %lo(.LCPI1_0)
	flw	ft0, 0(a0)
	lui	a0, 131072
	addi	s11, a0, -4
	addi	s7, zero, 1
	mv	s9, a6
	j	.LBB1_4
.Ltmp92:
.LBB1_3:                                # %for.cond.cleanup37.us
                                        #   in Loop: Header=BB1_4 Depth=1
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: remove:this <- undef
	#DEBUG_VALUE: remove:i <- $x26
	#DEBUG_VALUE: word:this <- undef
	#DEBUG_VALUE: word:i <- $x26
	#DEBUG_VALUE: remove:ptr <- undef
	#DEBUG_VALUE: bit:this <- undef
	#DEBUG_VALUE: bit:i <- $x26
	#DEBUG_VALUE: remove:r <- undef
	#DEBUG_VALUE: bit:this <- undef
	#DEBUG_VALUE: bit:i <- $x26
	.file	13 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/baseline/examples/dijkstra/kernel/include/set.hpp"
	.loc	13 21 30 is_stmt 1      # kernel/include/set.hpp:21:30
	sll	a0, s7, s10
.Ltmp93:
	.loc	13 31 19                # kernel/include/set.hpp:31:19
	srai	a1, s10, 5
.Ltmp94:
	.loc	13 21 9                 # kernel/include/set.hpp:21:9
	slli	a1, a1, 2
	add	a1, a5, a1
	.loc	13 21 24 is_stmt 0      # kernel/include/set.hpp:21:24
	lw	s0, 0(a1)
	.loc	13 21 27                # kernel/include/set.hpp:21:27
	not	a0, a0
.Ltmp95:
	#DEBUG_VALUE: word:i <- undef
	#DEBUG_VALUE: word:this <- undef
	.loc	13 21 24                # kernel/include/set.hpp:21:24
	and	a0, s0, a0
	.loc	13 22 15 is_stmt 1      # kernel/include/set.hpp:22:15
	addi	s9, s9, -1
.Ltmp96:
	#DEBUG_VALUE: empty:this <- undef
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	.loc	13 21 24                # kernel/include/set.hpp:21:24
	sw	a0, 0(a1)
.Ltmp97:
	.loc	12 46 5                 # kernel/dijkstra-set/kernel.cpp:46:5
	beqz	s9, .LBB1_25
.Ltmp98:
.LBB1_4:                                # %for.cond.preheader.us
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_6 Depth 2
                                        #     Child Loop BB1_15 Depth 2
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 0 5 is_stmt 0        # kernel/dijkstra-set/kernel.cpp:0:5
	mv	s0, zero
	addi	s10, zero, -1
.Ltmp99:
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	mv	a0, a3
	fmv.s	ft1, ft0
.Ltmp100:
	#DEBUG_VALUE: v <- 0
	j	.LBB1_6
.Ltmp101:
.LBB1_5:                                # %for.inc.us
                                        #   in Loop: Header=BB1_6 Depth=2
	#DEBUG_VALUE: v <- $x8
	#DEBUG_VALUE: dbest <- $f1_f
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dbest <- $f1_f
	.loc	12 49 35 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:49:35
	addi	s0, s0, 1
.Ltmp102:
	#DEBUG_VALUE: v <- $x8
	.loc	12 49 27 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:49:27
	addi	a0, a0, 4
	beq	a6, s0, .LBB1_9
.Ltmp103:
.LBB1_6:                                # %for.body.us
                                        #   Parent Loop BB1_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dbest <- $f1_f
	#DEBUG_VALUE: v <- $x8
	#DEBUG_VALUE: in:this <- undef
	#DEBUG_VALUE: in:i <- $x8
	#DEBUG_VALUE: word:this <- undef
	.loc	13 27 16 is_stmt 1      # kernel/include/set.hpp:27:16
	srli	a1, s0, 3
.Ltmp104:
	#DEBUG_VALUE: word:i <- $x8
	.loc	13 31 19                # kernel/include/set.hpp:31:19
	and	a1, a1, s11
.Ltmp105:
	.loc	13 27 16                # kernel/include/set.hpp:27:16
	add	a1, a5, a1
	lw	a1, 0(a1)
.Ltmp106:
	#DEBUG_VALUE: bit:i <- $x8
	#DEBUG_VALUE: bit:this <- undef
	srl	a1, a1, s0
	andi	a1, a1, 1
	beqz	a1, .LBB1_5
.Ltmp107:
# %bb.7:                                # %if.then.us
                                        #   in Loop: Header=BB1_6 Depth=2
	#DEBUG_VALUE: v <- $x8
	#DEBUG_VALUE: dbest <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 51 21                # kernel/dijkstra-set/kernel.cpp:51:21
	flw	ft2, 0(a0)
	.loc	12 51 33 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:51:33
	fle.s	a1, ft1, ft2
	bnez	a1, .LBB1_5
.Ltmp108:
# %bb.8:                                # %if.then16.us
                                        #   in Loop: Header=BB1_6 Depth=2
	#DEBUG_VALUE: v <- $x8
	#DEBUG_VALUE: dbest <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: best <- $x8
	#DEBUG_VALUE: dbest <- $f2_f
	.loc	12 0 0                  # kernel/dijkstra-set/kernel.cpp:0:0
	fmv.s	ft1, ft2
.Ltmp109:
	#DEBUG_VALUE: dbest <- $f1_f
	mv	s10, s0
	j	.LBB1_5
.Ltmp110:
.LBB1_9:                                # %for.cond.for.cond.cleanup_crit_edge.us
                                        #   in Loop: Header=BB1_4 Depth=1
	#DEBUG_VALUE: dbest <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: best <- $x26
	.loc	12 61 13 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:61:13
	beq	s10, a2, .LBB1_25
.Ltmp111:
# %bb.10:                               # %if.end21.us
                                        #   in Loop: Header=BB1_4 Depth=1
	#DEBUG_VALUE: dbest <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 64 24                # kernel/dijkstra-set/kernel.cpp:64:24
	slli	a0, s10, 2
	add	a1, a3, a0
	flw	ft1, 0(a1)
.Ltmp112:
	#DEBUG_VALUE: d_best <- $f1_f
	.loc	12 66 21                # kernel/dijkstra-set/kernel.cpp:66:21
	bne	s10, s8, .LBB1_12
.Ltmp113:
# %bb.11:                               # %cond.true.us
                                        #   in Loop: Header=BB1_4 Depth=1
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 66 44 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:66:44
	lw	a0, 0(s5)
	.loc	12 66 42                # kernel/dijkstra-set/kernel.cpp:66:42
	sub	s0, s4, a0
.Ltmp114:
	#DEBUG_VALUE: dst_n <- $x8
	#DEBUG_VALUE: dst_0 <- $x10
	#DEBUG_VALUE: dst_i <- 0
	.loc	12 0 42                 # kernel/dijkstra-set/kernel.cpp:0:42
	bge	s0, s7, .LBB1_13
	j	.LBB1_3
.Ltmp115:
.LBB1_12:                               # %cond.false.us
                                        #   in Loop: Header=BB1_4 Depth=1
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 66 84                # kernel/dijkstra-set/kernel.cpp:66:84
	add	a0, a7, a0
	.loc	12 66 64                # kernel/dijkstra-set/kernel.cpp:66:64
	lw	a1, 4(a0)
	.loc	12 66 84                # kernel/dijkstra-set/kernel.cpp:66:84
	lw	a0, 0(a0)
	.loc	12 66 82                # kernel/dijkstra-set/kernel.cpp:66:82
	sub	s0, a1, a0
.Ltmp116:
	#DEBUG_VALUE: dst_n <- $x8
	#DEBUG_VALUE: dst_0 <- $x10
	#DEBUG_VALUE: dst_i <- 0
	.loc	12 68 9 is_stmt 1       # kernel/dijkstra-set/kernel.cpp:68:9
	blt	s0, s7, .LBB1_3
.Ltmp117:
.LBB1_13:                               # %for.body38.us.preheader
                                        #   in Loop: Header=BB1_4 Depth=1
	#DEBUG_VALUE: dst_n <- $x8
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dst_0 <- $x10
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	slli	a1, a0, 2
	add	a0, s6, a1
.Ltmp118:
	add	a1, t0, a1
	j	.LBB1_15
.Ltmp119:
.LBB1_14:                               # %if.end50.us
                                        #   in Loop: Header=BB1_15 Depth=2
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dst_i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	12 68 35 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:68:35
	addi	s0, s0, -1
	addi	a0, a0, 4
	addi	a1, a1, 4
.Ltmp120:
	.loc	12 68 9                 # kernel/dijkstra-set/kernel.cpp:68:9
	beqz	s0, .LBB1_3
.Ltmp121:
.LBB1_15:                               # %for.body38.us
                                        #   Parent Loop BB1_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dst_i <- undef
	.loc	12 69 23 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:69:23
	lw	s1, 0(a1)
.Ltmp122:
	#DEBUG_VALUE: dst <- $x9
	.loc	12 75 28                # kernel/dijkstra-set/kernel.cpp:75:28
	slli	ra, s1, 2
	add	s1, a3, ra
.Ltmp123:
	flw	ft3, 0(s1)
.Ltmp124:
	.loc	12 73 23                # kernel/dijkstra-set/kernel.cpp:73:23
	flw	ft2, 0(a0)
.Ltmp125:
	#DEBUG_VALUE: w <- $f2_f
	.loc	12 75 23                # kernel/dijkstra-set/kernel.cpp:75:23
	fadd.s	ft2, ft2, ft1
.Ltmp126:
	.loc	12 75 26 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:75:26
	fle.s	t1, ft3, ft2
.Ltmp127:
	.loc	12 75 17                # kernel/dijkstra-set/kernel.cpp:75:17
	bnez	t1, .LBB1_14
.Ltmp128:
# %bb.16:                               # %if.then46.us
                                        #   in Loop: Header=BB1_15 Depth=2
	#DEBUG_VALUE: d_best <- $f1_f
	#DEBUG_VALUE: best <- $x26
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x25
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 76 31 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:76:31
	fsw	ft2, 0(s1)
	.loc	12 77 17                # kernel/dijkstra-set/kernel.cpp:77:17
	add	s1, a4, ra
	.loc	12 77 27 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:77:27
	sw	s10, 0(s1)
	j	.LBB1_14
.Ltmp129:
.LBB1_17:
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 32 32] $x20
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 0 32] $x16
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 0 27                 # kernel/dijkstra-set/kernel.cpp:0:27
	addi	s7, zero, -1
	addi	s4, zero, 1
.Ltmp130:
	lui	a0, 524288
	addi	s5, a0, -1
	j	.LBB1_19
.Ltmp131:
.LBB1_18:                               # %for.cond.cleanup37
                                        #   in Loop: Header=BB1_19 Depth=1
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: remove:this <- undef
	#DEBUG_VALUE: remove:i <- -1
	#DEBUG_VALUE: word:this <- undef
	#DEBUG_VALUE: word:i <- -1
	#DEBUG_VALUE: remove:ptr <- undef
	#DEBUG_VALUE: bit:this <- undef
	#DEBUG_VALUE: bit:i <- -1
	#DEBUG_VALUE: remove:r <- undef
	#DEBUG_VALUE: bit:this <- undef
	#DEBUG_VALUE: bit:i <- -1
	#DEBUG_VALUE: word:this <- undef
	#DEBUG_VALUE: word:i <- -1
	.loc	13 21 24 is_stmt 1      # kernel/include/set.hpp:21:24
	lw	a0, -4(a5)
	and	a0, a0, s5
	.loc	13 22 15                # kernel/include/set.hpp:22:15
	addi	a6, a6, -1
.Ltmp132:
	#DEBUG_VALUE: empty:this <- undef
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	.loc	13 21 24                # kernel/include/set.hpp:21:24
	sw	a0, -4(a5)
	beqz	a6, .LBB1_25
.Ltmp133:
.LBB1_19:                               # %for.cond.preheader
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_23 Depth 2
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: v <- 0
	.loc	13 0 24 is_stmt 0       # kernel/include/set.hpp:0:24
	beq	a2, s7, .LBB1_25
.Ltmp134:
# %bb.20:                               # %cond.end
                                        #   in Loop: Header=BB1_19 Depth=1
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: d_best <- undef
	.loc	12 66 64 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:66:64
	lw	a1, 0(a7)
	.loc	12 66 84 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:66:84
	lw	a0, -4(a7)
	.loc	12 66 82                # kernel/dijkstra-set/kernel.cpp:66:82
	sub	s1, a1, a0
.Ltmp135:
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dst_0 <- $x10
	#DEBUG_VALUE: dst_n <- $x9
	.loc	12 0 82                 # kernel/dijkstra-set/kernel.cpp:0:82
	blt	s1, s4, .LBB1_18
.Ltmp136:
# %bb.21:                               # %for.body38.preheader
                                        #   in Loop: Header=BB1_19 Depth=1
	#DEBUG_VALUE: dst_n <- $x9
	#DEBUG_VALUE: dst_0 <- $x10
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	flw	ft0, -4(a3)
.Ltmp137:
	#DEBUG_VALUE: d_best <- $f0_f
	.loc	12 68 9 is_stmt 1       # kernel/dijkstra-set/kernel.cpp:68:9
	slli	a0, a0, 2
.Ltmp138:
	add	a1, s6, a0
	add	s0, t0, a0
	j	.LBB1_23
.Ltmp139:
.LBB1_22:                               # %if.end50
                                        #   in Loop: Header=BB1_23 Depth=2
	#DEBUG_VALUE: d_best <- $f0_f
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dst_i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	12 68 35 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:68:35
	addi	s1, s1, -1
	addi	a1, a1, 4
	addi	s0, s0, 4
	beqz	s1, .LBB1_18
.Ltmp140:
.LBB1_23:                               # %for.body38
                                        #   Parent Loop BB1_19 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: d_best <- $f0_f
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	#DEBUG_VALUE: dst_i <- undef
	.loc	12 69 23 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:69:23
	lw	a0, 0(s0)
.Ltmp141:
	#DEBUG_VALUE: dst <- $x10
	.loc	12 75 28                # kernel/dijkstra-set/kernel.cpp:75:28
	slli	s8, a0, 2
	add	t1, a3, s8
	flw	ft2, 0(t1)
.Ltmp142:
	.loc	12 73 23                # kernel/dijkstra-set/kernel.cpp:73:23
	flw	ft1, 0(a1)
.Ltmp143:
	#DEBUG_VALUE: w <- $f1_f
	.loc	12 75 23                # kernel/dijkstra-set/kernel.cpp:75:23
	fadd.s	ft1, ft1, ft0
.Ltmp144:
	.loc	12 75 26 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:75:26
	fle.s	a0, ft2, ft1
.Ltmp145:
	.loc	12 0 26                 # kernel/dijkstra-set/kernel.cpp:0:26
	bnez	a0, .LBB1_22
.Ltmp146:
# %bb.24:                               # %if.then46
                                        #   in Loop: Header=BB1_23 Depth=2
	#DEBUG_VALUE: d_best <- $f0_f
	#DEBUG_VALUE: dst_i <- 0
	#DEBUG_VALUE: dbest <- INF
	#DEBUG_VALUE: best <- -1
	#DEBUG_VALUE: dijkstra:unvisited <- [DW_OP_LLVM_fragment 32 32] $x16
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 76 31 is_stmt 1      # kernel/dijkstra-set/kernel.cpp:76:31
	fsw	ft1, 0(t1)
	.loc	12 77 17                # kernel/dijkstra-set/kernel.cpp:77:17
	add	a0, a4, s8
	.loc	12 77 27 is_stmt 0      # kernel/dijkstra-set/kernel.cpp:77:27
	sw	s7, 0(a0)
	j	.LBB1_22
.Ltmp147:
.LBB1_25:                               # %do.body55
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 128 32] $x22
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 96 32] $x5
	#DEBUG_VALUE: dijkstra:g <- [DW_OP_LLVM_fragment 64 32] $x17
	#DEBUG_VALUE: dijkstra:queue_mem <- $x15
	#DEBUG_VALUE: dijkstra:path <- $x14
	#DEBUG_VALUE: dijkstra:distance <- $x13
	#DEBUG_VALUE: dijkstra:goal <- $x12
	.loc	12 83 5 is_stmt 1       # kernel/dijkstra-set/kernel.cpp:83:5
	lui	a0, %hi(__bsg_grp_org_y)
	lw	a0, %lo(__bsg_grp_org_y)(a0)
	lw	a1, %lo(__bsg_y)(t2)
	add	a0, a1, a0
	lw	a1, %lo(__bsg_grp_org_x)(t3)
	lw	a2, %lo(__bsg_x)(t5)
.Ltmp148:
	slli	a0, a0, 24
	add	a1, a2, a1
	slli	a1, a1, 18
	lw	a2, %lo(__bsg_tile_group_id)(s2)
	and	a1, a1, t4
	slli	a2, a2, 4
	and	a2, a2, s3
	or	a0, a0, a1
	or	a0, a0, a2
	lui	a1, 786432
	or	a1, a0, a1
.Ltmp149:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x11
	.loc	12 85 5                 # kernel/dijkstra-set/kernel.cpp:85:5
	mv	a0, zero
.Ltmp150:
	.loc	12 83 5                 # kernel/dijkstra-set/kernel.cpp:83:5
	sw	a1, -756(t6)
.Ltmp151:
	#DEBUG_VALUE: val <- $x11
	.loc	12 85 5                 # kernel/dijkstra-set/kernel.cpp:85:5
	lw	s11, 12(sp)
	lw	s10, 16(sp)
	lw	s9, 20(sp)
	lw	s8, 24(sp)
	lw	s7, 28(sp)
	lw	s6, 32(sp)
.Ltmp152:
	lw	s5, 36(sp)
	lw	s4, 40(sp)
	lw	s3, 44(sp)
	lw	s2, 48(sp)
	lw	s1, 52(sp)
	lw	s0, 56(sp)
	lw	ra, 60(sp)
	addi	sp, sp, 64
	ret
.Ltmp153:
.Lfunc_end1:
	.size	dijkstra, .Lfunc_end1-dijkstra
	.cfi_endproc
                                        # -- End function
	.file	14 "/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/baseline/examples/dijkstra/kernel/include/graph.hpp"
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"clang version 10.0.0 (https://github.com/bespoke-silicon-group/llvm-project.git 26ed0b46f4c6c06a4ff742ef99e810b737b1d8a2)" # string offset=0
.Linfo_string1:
	.asciz	"kernel/dijkstra-set/kernel.cpp" # string offset=122
.Linfo_string2:
	.asciz	"/mnt/users/ssd3/homes/mrutt/work/bigblade-dijkstra/bsg_bladerunner/baseline/examples/dijkstra" # string offset=153
.Linfo_string3:
	.asciz	"int"                   # string offset=247
.Linfo_string4:
	.asciz	"bsg_remote_int_ptr"    # string offset=251
.Linfo_string5:
	.asciz	"_x_cord_start"         # string offset=270
.Linfo_string6:
	.asciz	"unsigned char"         # string offset=284
.Linfo_string7:
	.asciz	"_x_cord_end"           # string offset=298
.Linfo_string8:
	.asciz	"_done_list"            # string offset=310
.Linfo_string9:
	.asciz	"__ARRAY_SIZE_TYPE__"   # string offset=321
.Linfo_string10:
	.asciz	"_local_alert"          # string offset=341
.Linfo_string11:
	.asciz	"unsigned int"          # string offset=354
.Linfo_string12:
	.asciz	"_bsg_row_barrier_"     # string offset=367
.Linfo_string13:
	.asciz	"bsg_row_barrier"       # string offset=385
.Linfo_string14:
	.asciz	"_y_cord_start"         # string offset=401
.Linfo_string15:
	.asciz	"_y_cord_end"           # string offset=415
.Linfo_string16:
	.asciz	"_bsg_col_barrier_"     # string offset=427
.Linfo_string17:
	.asciz	"bsg_col_barrier"       # string offset=445
.Linfo_string18:
	.asciz	"__gnu_debug"           # string offset=461
.Linfo_string19:
	.asciz	"std"                   # string offset=473
.Linfo_string20:
	.asciz	"__debug"               # string offset=477
.Linfo_string21:
	.asciz	"abs"                   # string offset=485
.Linfo_string22:
	.asciz	"div_t"                 # string offset=489
.Linfo_string23:
	.asciz	"quot"                  # string offset=495
.Linfo_string24:
	.asciz	"long int"              # string offset=500
.Linfo_string25:
	.asciz	"rem"                   # string offset=509
.Linfo_string26:
	.asciz	"ldiv_t"                # string offset=513
.Linfo_string27:
	.asciz	"abort"                 # string offset=520
.Linfo_string28:
	.asciz	"atexit"                # string offset=526
.Linfo_string29:
	.asciz	"atof"                  # string offset=533
.Linfo_string30:
	.asciz	"double"                # string offset=538
.Linfo_string31:
	.asciz	"char"                  # string offset=545
.Linfo_string32:
	.asciz	"atoi"                  # string offset=550
.Linfo_string33:
	.asciz	"atol"                  # string offset=555
.Linfo_string34:
	.asciz	"bsearch"               # string offset=560
.Linfo_string35:
	.asciz	"size_t"                # string offset=568
.Linfo_string36:
	.asciz	"__compar_fn_t"         # string offset=575
.Linfo_string37:
	.asciz	"calloc"                # string offset=589
.Linfo_string38:
	.asciz	"div"                   # string offset=596
.Linfo_string39:
	.asciz	"exit"                  # string offset=600
.Linfo_string40:
	.asciz	"free"                  # string offset=605
.Linfo_string41:
	.asciz	"getenv"                # string offset=610
.Linfo_string42:
	.asciz	"labs"                  # string offset=617
.Linfo_string43:
	.asciz	"ldiv"                  # string offset=622
.Linfo_string44:
	.asciz	"malloc"                # string offset=627
.Linfo_string45:
	.asciz	"mblen"                 # string offset=634
.Linfo_string46:
	.asciz	"mbstowcs"              # string offset=640
.Linfo_string47:
	.asciz	"wchar_t"               # string offset=649
.Linfo_string48:
	.asciz	"mbtowc"                # string offset=657
.Linfo_string49:
	.asciz	"qsort"                 # string offset=664
.Linfo_string50:
	.asciz	"rand"                  # string offset=670
.Linfo_string51:
	.asciz	"realloc"               # string offset=675
.Linfo_string52:
	.asciz	"srand"                 # string offset=683
.Linfo_string53:
	.asciz	"strtod"                # string offset=689
.Linfo_string54:
	.asciz	"strtol"                # string offset=696
.Linfo_string55:
	.asciz	"strtoul"               # string offset=703
.Linfo_string56:
	.asciz	"long unsigned int"     # string offset=711
.Linfo_string57:
	.asciz	"system"                # string offset=729
.Linfo_string58:
	.asciz	"wcstombs"              # string offset=736
.Linfo_string59:
	.asciz	"wctomb"                # string offset=745
.Linfo_string60:
	.asciz	"__gnu_cxx"             # string offset=752
.Linfo_string61:
	.asciz	"long long int"         # string offset=762
.Linfo_string62:
	.asciz	"lldiv_t"               # string offset=776
.Linfo_string63:
	.asciz	"_Exit"                 # string offset=784
.Linfo_string64:
	.asciz	"llabs"                 # string offset=790
.Linfo_string65:
	.asciz	"lldiv"                 # string offset=796
.Linfo_string66:
	.asciz	"atoll"                 # string offset=802
.Linfo_string67:
	.asciz	"strtoll"               # string offset=808
.Linfo_string68:
	.asciz	"strtoull"              # string offset=816
.Linfo_string69:
	.asciz	"long long unsigned int" # string offset=825
.Linfo_string70:
	.asciz	"strtof"                # string offset=848
.Linfo_string71:
	.asciz	"float"                 # string offset=855
.Linfo_string72:
	.asciz	"strtold"               # string offset=861
.Linfo_string73:
	.asciz	"long double"           # string offset=869
.Linfo_string74:
	.asciz	"_ZN9__gnu_cxx3divExx"  # string offset=881
.Linfo_string75:
	.asciz	"__exception_ptr"       # string offset=902
.Linfo_string76:
	.asciz	"_M_exception_object"   # string offset=918
.Linfo_string77:
	.asciz	"exception_ptr"         # string offset=938
.Linfo_string78:
	.asciz	"_ZNSt15__exception_ptr13exception_ptr9_M_addrefEv" # string offset=952
.Linfo_string79:
	.asciz	"_M_addref"             # string offset=1002
.Linfo_string80:
	.asciz	"_ZNSt15__exception_ptr13exception_ptr10_M_releaseEv" # string offset=1012
.Linfo_string81:
	.asciz	"_M_release"            # string offset=1064
.Linfo_string82:
	.asciz	"_ZNKSt15__exception_ptr13exception_ptr6_M_getEv" # string offset=1075
.Linfo_string83:
	.asciz	"_M_get"                # string offset=1123
.Linfo_string84:
	.asciz	"decltype(nullptr)"     # string offset=1130
.Linfo_string85:
	.asciz	"nullptr_t"             # string offset=1148
.Linfo_string86:
	.asciz	"_ZNSt15__exception_ptr13exception_ptraSERKS0_" # string offset=1158
.Linfo_string87:
	.asciz	"operator="             # string offset=1204
.Linfo_string88:
	.asciz	"_ZNSt15__exception_ptr13exception_ptraSEOS0_" # string offset=1214
.Linfo_string89:
	.asciz	"~exception_ptr"        # string offset=1259
.Linfo_string90:
	.asciz	"_ZNSt15__exception_ptr13exception_ptr4swapERS0_" # string offset=1274
.Linfo_string91:
	.asciz	"swap"                  # string offset=1322
.Linfo_string92:
	.asciz	"_ZNKSt15__exception_ptr13exception_ptrcvbEv" # string offset=1327
.Linfo_string93:
	.asciz	"operator bool"         # string offset=1371
.Linfo_string94:
	.asciz	"bool"                  # string offset=1385
.Linfo_string95:
	.asciz	"_ZNKSt15__exception_ptr13exception_ptr20__cxa_exception_typeEv" # string offset=1390
.Linfo_string96:
	.asciz	"__cxa_exception_type"  # string offset=1453
.Linfo_string97:
	.asciz	"type_info"             # string offset=1474
.Linfo_string98:
	.asciz	"_ZSt17rethrow_exceptionNSt15__exception_ptr13exception_ptrE" # string offset=1484
.Linfo_string99:
	.asciz	"rethrow_exception"     # string offset=1544
.Linfo_string100:
	.asciz	"acos"                  # string offset=1562
.Linfo_string101:
	.asciz	"asin"                  # string offset=1567
.Linfo_string102:
	.asciz	"atan"                  # string offset=1572
.Linfo_string103:
	.asciz	"atan2"                 # string offset=1577
.Linfo_string104:
	.asciz	"ceil"                  # string offset=1583
.Linfo_string105:
	.asciz	"cos"                   # string offset=1588
.Linfo_string106:
	.asciz	"cosh"                  # string offset=1592
.Linfo_string107:
	.asciz	"exp"                   # string offset=1597
.Linfo_string108:
	.asciz	"fabs"                  # string offset=1601
.Linfo_string109:
	.asciz	"floor"                 # string offset=1606
.Linfo_string110:
	.asciz	"fmod"                  # string offset=1612
.Linfo_string111:
	.asciz	"frexp"                 # string offset=1617
.Linfo_string112:
	.asciz	"ldexp"                 # string offset=1623
.Linfo_string113:
	.asciz	"log"                   # string offset=1629
.Linfo_string114:
	.asciz	"log10"                 # string offset=1633
.Linfo_string115:
	.asciz	"modf"                  # string offset=1639
.Linfo_string116:
	.asciz	"pow"                   # string offset=1644
.Linfo_string117:
	.asciz	"sin"                   # string offset=1648
.Linfo_string118:
	.asciz	"sinh"                  # string offset=1652
.Linfo_string119:
	.asciz	"sqrt"                  # string offset=1657
.Linfo_string120:
	.asciz	"tan"                   # string offset=1662
.Linfo_string121:
	.asciz	"tanh"                  # string offset=1666
.Linfo_string122:
	.asciz	"_Z20bsg_row_barrier_syncP17_bsg_row_barrier_i" # string offset=1671
.Linfo_string123:
	.asciz	"bsg_row_barrier_sync"  # string offset=1717
.Linfo_string124:
	.asciz	"p_row_b"               # string offset=1738
.Linfo_string125:
	.asciz	"center_x_cord"         # string offset=1746
.Linfo_string126:
	.asciz	"p_remote_barrier"      # string offset=1760
.Linfo_string127:
	.asciz	"i"                     # string offset=1777
.Linfo_string128:
	.asciz	"_Z20bsg_col_barrier_syncP17_bsg_row_barrier_P17_bsg_col_barrier_ii" # string offset=1779
.Linfo_string129:
	.asciz	"bsg_col_barrier_sync"  # string offset=1846
.Linfo_string130:
	.asciz	"p_col_b"               # string offset=1867
.Linfo_string131:
	.asciz	"center_y_cord"         # string offset=1875
.Linfo_string132:
	.asciz	"x_range"               # string offset=1889
.Linfo_string133:
	.asciz	"_Z10poll_rangeiPh"     # string offset=1897
.Linfo_string134:
	.asciz	"poll_range"            # string offset=1915
.Linfo_string135:
	.asciz	"range"                 # string offset=1926
.Linfo_string136:
	.asciz	"p"                     # string offset=1932
.Linfo_string137:
	.asciz	"_Z21bsg_col_barrier_alertP17_bsg_col_barrier_" # string offset=1934
.Linfo_string138:
	.asciz	"bsg_col_barrier_alert" # string offset=1980
.Linfo_string139:
	.asciz	"y_range"               # string offset=2002
.Linfo_string140:
	.asciz	"_Z9alert_colP17_bsg_col_barrier_" # string offset=2010
.Linfo_string141:
	.asciz	"alert_col"             # string offset=2043
.Linfo_string142:
	.asciz	"_Z21bsg_row_barrier_alertP17_bsg_row_barrier_P17_bsg_col_barrier_" # string offset=2053
.Linfo_string143:
	.asciz	"bsg_row_barrier_alert" # string offset=2119
.Linfo_string144:
	.asciz	"_Z6bsg_lrPi"           # string offset=2141
.Linfo_string145:
	.asciz	"bsg_lr"                # string offset=2153
.Linfo_string146:
	.asciz	"tmp"                   # string offset=2160
.Linfo_string147:
	.asciz	"_Z18bsg_wait_local_intPii" # string offset=2164
.Linfo_string148:
	.asciz	"bsg_wait_local_int"    # string offset=2190
.Linfo_string149:
	.asciz	"ptr"                   # string offset=2209
.Linfo_string150:
	.asciz	"cond"                  # string offset=2213
.Linfo_string151:
	.asciz	"_Z9bsg_lr_aqPi"        # string offset=2218
.Linfo_string152:
	.asciz	"bsg_lr_aq"             # string offset=2233
.Linfo_string153:
	.asciz	"_Z9alert_rowP17_bsg_row_barrier_" # string offset=2243
.Linfo_string154:
	.asciz	"alert_row"             # string offset=2276
.Linfo_string155:
	.asciz	"_Z13bsg_tile_waitP17_bsg_row_barrier_" # string offset=2286
.Linfo_string156:
	.asciz	"bsg_tile_wait"         # string offset=2324
.Linfo_string157:
	.asciz	"_data"                 # string offset=2338
.Linfo_string158:
	.asciz	"_size"                 # string offset=2344
.Linfo_string159:
	.asciz	"DenseSet"              # string offset=2350
.Linfo_string160:
	.asciz	"_ZN8DenseSetIiE6insertEi" # string offset=2359
.Linfo_string161:
	.asciz	"insert"                # string offset=2384
.Linfo_string162:
	.asciz	"_ZN8DenseSetIiE6removeEi" # string offset=2391
.Linfo_string163:
	.asciz	"remove"                # string offset=2416
.Linfo_string164:
	.asciz	"_ZN8DenseSetIiE2inEi"  # string offset=2423
.Linfo_string165:
	.asciz	"in"                    # string offset=2444
.Linfo_string166:
	.asciz	"_ZNK8DenseSetIiE4wordEi" # string offset=2447
.Linfo_string167:
	.asciz	"word"                  # string offset=2471
.Linfo_string168:
	.asciz	"_ZNK8DenseSetIiE3bitEi" # string offset=2476
.Linfo_string169:
	.asciz	"bit"                   # string offset=2499
.Linfo_string170:
	.asciz	"_ZNK8DenseSetIiE5emptyEv" # string offset=2503
.Linfo_string171:
	.asciz	"empty"                 # string offset=2528
.Linfo_string172:
	.asciz	"T"                     # string offset=2534
.Linfo_string173:
	.asciz	"DenseSet<int>"         # string offset=2536
.Linfo_string174:
	.asciz	"this"                  # string offset=2550
.Linfo_string175:
	.asciz	"r"                     # string offset=2555
.Linfo_string176:
	.asciz	"_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_" # string offset=2557
.Linfo_string177:
	.asciz	"bsg_tile_group_barrier" # string offset=2624
.Linfo_string178:
	.asciz	"dijkstra"              # string offset=2647
.Linfo_string179:
	.asciz	"g_mem"                 # string offset=2656
.Linfo_string180:
	.asciz	"V"                     # string offset=2662
.Linfo_string181:
	.asciz	"E"                     # string offset=2664
.Linfo_string182:
	.asciz	"offsets"               # string offset=2666
.Linfo_string183:
	.asciz	"neighbors"             # string offset=2674
.Linfo_string184:
	.asciz	"weights"               # string offset=2684
.Linfo_string185:
	.asciz	"graph"                 # string offset=2692
.Linfo_string186:
	.asciz	"root"                  # string offset=2698
.Linfo_string187:
	.asciz	"goal"                  # string offset=2703
.Linfo_string188:
	.asciz	"distance"              # string offset=2708
.Linfo_string189:
	.asciz	"path"                  # string offset=2717
.Linfo_string190:
	.asciz	"queue_mem"             # string offset=2722
.Linfo_string191:
	.asciz	"g"                     # string offset=2732
.Linfo_string192:
	.asciz	"unvisited"             # string offset=2734
.Linfo_string193:
	.asciz	"val"                   # string offset=2744
.Linfo_string194:
	.asciz	"d_best"                # string offset=2748
.Linfo_string195:
	.asciz	"best"                  # string offset=2755
.Linfo_string196:
	.asciz	"dbest"                 # string offset=2760
.Linfo_string197:
	.asciz	"v"                     # string offset=2766
.Linfo_string198:
	.asciz	"dst_n"                 # string offset=2768
.Linfo_string199:
	.asciz	"dst_0"                 # string offset=2774
.Linfo_string200:
	.asciz	"dst_i"                 # string offset=2780
.Linfo_string201:
	.asciz	"dst"                   # string offset=2786
.Linfo_string202:
	.asciz	"w"                     # string offset=2790
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
	.word	.Lfunc_begin0-.Lfunc_begin0
	.word	.Ltmp0-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp0-.Lfunc_begin0
	.word	.Ltmp76-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc1:
	.word	.Lfunc_begin0-.Lfunc_begin0
	.word	.Ltmp1-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp1-.Lfunc_begin0
	.word	.Ltmp64-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc2:
	.word	.Ltmp2-.Lfunc_begin0
	.word	.Ltmp75-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	98                      # DW_OP_reg18
	.word	0
	.word	0
.Ldebug_loc3:
	.word	.Ltmp7-.Lfunc_begin0
	.word	.Ltmp8-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc4:
	.word	.Ltmp11-.Lfunc_begin0
	.word	.Ltmp12-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	98                      # DW_OP_reg18
	.word	0
	.word	0
.Ldebug_loc5:
	.word	.Ltmp11-.Lfunc_begin0
	.word	.Ltmp12-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc6:
	.word	.Ltmp11-.Lfunc_begin0
	.word	.Ltmp31-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc7:
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp26-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc8:
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp26-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc9:
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp26-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	98                      # DW_OP_reg18
	.word	0
	.word	0
.Ldebug_loc10:
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp26-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc11:
	.word	.Ltmp13-.Lfunc_begin0
	.word	.Ltmp23-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc12:
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc13:
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp16-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp17-.Lfunc_begin0
	.word	.Ltmp18-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	.Ltmp18-.Lfunc_begin0
	.word	.Ltmp21-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	126                     # DW_OP_breg14
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp21-.Lfunc_begin0
	.word	.Ltmp22-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc14:
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp22-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	2                       # 2
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc15:
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp22-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc16:
	.word	.Ltmp28-.Lfunc_begin0
	.word	.Ltmp47-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc17:
	.word	.Ltmp29-.Lfunc_begin0
	.word	.Ltmp31-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp32-.Lfunc_begin0
	.word	.Ltmp33-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp33-.Lfunc_begin0
	.word	.Ltmp36-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	123                     # DW_OP_breg11
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp36-.Lfunc_begin0
	.word	.Ltmp37-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc18:
	.word	.Ltmp29-.Lfunc_begin0
	.word	.Ltmp37-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	121                     # DW_OP_breg9
	.byte	2                       # 2
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc19:
	.word	.Ltmp29-.Lfunc_begin0
	.word	.Ltmp37-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc20:
	.word	.Ltmp29-.Lfunc_begin0
	.word	.Ltmp38-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc21:
	.word	.Ltmp37-.Lfunc_begin0
	.word	.Ltmp39-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc22:
	.word	.Ltmp40-.Lfunc_begin0
	.word	.Ltmp43-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	100                     # DW_OP_reg20
	.word	0
	.word	0
.Ldebug_loc23:
	.word	.Ltmp40-.Lfunc_begin0
	.word	.Ltmp47-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc24:
	.word	.Ltmp44-.Lfunc_begin0
	.word	.Ltmp47-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc25:
	.word	.Ltmp48-.Lfunc_begin0
	.word	.Ltmp68-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc26:
	.word	.Ltmp48-.Lfunc_begin0
	.word	.Ltmp64-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc27:
	.word	.Ltmp49-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc28:
	.word	.Ltmp49-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	121                     # DW_OP_breg9
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc29:
	.word	.Ltmp50-.Lfunc_begin0
	.word	.Ltmp52-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	121                     # DW_OP_breg9
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc30:
	.word	.Ltmp51-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc31:
	.word	.Ltmp51-.Lfunc_begin0
	.word	.Ltmp52-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc32:
	.word	.Ltmp52-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	121                     # DW_OP_breg9
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc33:
	.word	.Ltmp53-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc34:
	.word	.Ltmp54-.Lfunc_begin0
	.word	.Ltmp68-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc35:
	.word	.Ltmp58-.Lfunc_begin0
	.word	.Ltmp68-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc36:
	.word	.Ltmp59-.Lfunc_begin0
	.word	.Ltmp63-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc37:
	.word	.Ltmp65-.Lfunc_begin0
	.word	.Ltmp68-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc38:
	.word	.Ltmp68-.Lfunc_begin0
	.word	.Ltmp76-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc39:
	.word	.Ltmp68-.Lfunc_begin0
	.word	.Ltmp73-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc40:
	.word	.Ltmp68-.Lfunc_begin0
	.word	.Ltmp73-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc41:
	.word	.Ltmp69-.Lfunc_begin0
	.word	.Ltmp71-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc42:
	.word	.Ltmp70-.Lfunc_begin0
	.word	.Ltmp73-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc43:
	.word	.Ltmp70-.Lfunc_begin0
	.word	.Ltmp71-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc44:
	.word	.Ltmp71-.Lfunc_begin0
	.word	.Ltmp73-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc45:
	.word	.Ltmp72-.Lfunc_begin0
	.word	.Ltmp73-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc46:
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp84-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc47:
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp86-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc48:
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp148-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc49:
	.word	.Ltmp79-.Lfunc_begin0
	.word	.Ltmp80-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp80-.Lfunc_begin0
	.word	.Ltmp81-.Lfunc_begin0
	.half	6                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	100                     # DW_OP_reg20
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp81-.Lfunc_begin0
	.word	.Ltmp82-.Lfunc_begin0
	.half	9                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	100                     # DW_OP_reg20
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	97                      # DW_OP_reg17
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp82-.Lfunc_begin0
	.word	.Ltmp83-.Lfunc_begin0
	.half	12                      # Loc expr size
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	100                     # DW_OP_reg20
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	97                      # DW_OP_reg17
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	85                      # DW_OP_reg5
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp83-.Lfunc_begin0
	.word	.Ltmp130-.Lfunc_begin0
	.half	15                      # Loc expr size
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	100                     # DW_OP_reg20
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	97                      # DW_OP_reg17
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	85                      # DW_OP_reg5
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	102                     # DW_OP_reg22
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp130-.Lfunc_begin0
	.word	.Ltmp131-.Lfunc_begin0
	.half	14                      # Loc expr size
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	97                      # DW_OP_reg17
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	85                      # DW_OP_reg5
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	102                     # DW_OP_reg22
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp131-.Lfunc_begin0
	.word	.Ltmp152-.Lfunc_begin0
	.half	11                      # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.byte	97                      # DW_OP_reg17
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	85                      # DW_OP_reg5
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	102                     # DW_OP_reg22
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp152-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	8                       # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	8                       # 8
	.byte	97                      # DW_OP_reg17
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	85                      # DW_OP_reg5
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	0
	.word	0
.Ldebug_loc50:
	.word	.Ltmp85-.Lfunc_begin0
	.word	.Ltmp92-.Lfunc_begin0
	.half	5                       # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp92-.Lfunc_begin0
	.word	.Ltmp98-.Lfunc_begin0
	.half	5                       # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	105                     # DW_OP_reg25
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp99-.Lfunc_begin0
	.word	.Ltmp129-.Lfunc_begin0
	.half	5                       # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	105                     # DW_OP_reg25
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	.Ltmp129-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.half	5                       # Loc expr size
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.byte	96                      # DW_OP_reg16
	.byte	147                     # DW_OP_piece
	.byte	4                       # 4
	.word	0
	.word	0
.Ldebug_loc51:
	.word	.Ltmp87-.Lfunc_begin0
	.word	.Ltmp90-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc52:
	.word	.Ltmp92-.Lfunc_begin0
	.word	.Ltmp98-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	33                      # 33
	.word	.Ltmp112-.Lfunc_begin0
	.word	.Ltmp129-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	33                      # 33
	.word	.Ltmp137-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	32                      # 32
	.word	0
	.word	0
.Ldebug_loc53:
	.word	.Ltmp92-.Lfunc_begin0
	.word	.Ltmp98-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	.Ltmp99-.Lfunc_begin0
	.word	.Ltmp101-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	127                     # -1
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp101-.Lfunc_begin0
	.word	.Ltmp108-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	.Ltmp108-.Lfunc_begin0
	.word	.Ltmp110-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	.Ltmp110-.Lfunc_begin0
	.word	.Ltmp129-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	.Ltmp131-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	127                     # -1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc54:
	.word	.Ltmp92-.Lfunc_begin0
	.word	.Ltmp98-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	.Ltmp131-.Lfunc_begin0
	.word	.Ltmp133-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	127                     # -1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc55:
	.word	.Ltmp131-.Lfunc_begin0
	.word	.Ltmp133-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	127                     # -1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc56:
	.word	.Ltmp99-.Lfunc_begin0
	.word	.Ltmp101-.Lfunc_begin0
	.half	7                       # Loc expr size
	.byte	16                      # DW_OP_constu
	.byte	128                     # 2139095040
	.byte	128                     # 
	.byte	128                     # 
	.byte	252                     # 
	.byte	7                       # 
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp101-.Lfunc_begin0
	.word	.Ltmp108-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	33                      # 33
	.word	.Ltmp108-.Lfunc_begin0
	.word	.Ltmp109-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	34                      # 34
	.word	.Ltmp109-.Lfunc_begin0
	.word	.Ltmp112-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	33                      # 33
	.word	.Ltmp131-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.half	7                       # Loc expr size
	.byte	16                      # DW_OP_constu
	.byte	128                     # 2139095040
	.byte	128                     # 
	.byte	128                     # 
	.byte	252                     # 
	.byte	7                       # 
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc57:
	.word	.Ltmp100-.Lfunc_begin0
	.word	.Ltmp101-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp101-.Lfunc_begin0
	.word	.Ltmp110-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	.Ltmp133-.Lfunc_begin0
	.word	.Ltmp134-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc58:
	.word	.Ltmp103-.Lfunc_begin0
	.word	.Ltmp107-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc59:
	.word	.Ltmp104-.Lfunc_begin0
	.word	.Ltmp107-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc60:
	.word	.Ltmp114-.Lfunc_begin0
	.word	.Ltmp115-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	.Ltmp116-.Lfunc_begin0
	.word	.Ltmp119-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	.Ltmp135-.Lfunc_begin0
	.word	.Ltmp139-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc61:
	.word	.Ltmp114-.Lfunc_begin0
	.word	.Ltmp115-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp116-.Lfunc_begin0
	.word	.Ltmp118-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp135-.Lfunc_begin0
	.word	.Ltmp138-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc62:
	.word	.Ltmp114-.Lfunc_begin0
	.word	.Ltmp115-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp116-.Lfunc_begin0
	.word	.Ltmp119-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp128-.Lfunc_begin0
	.word	.Ltmp129-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp135-.Lfunc_begin0
	.word	.Ltmp139-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp146-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc63:
	.word	.Ltmp122-.Lfunc_begin0
	.word	.Ltmp123-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	.Ltmp141-.Lfunc_begin0
	.word	.Ltmp145-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc64:
	.word	.Ltmp125-.Lfunc_begin0
	.word	.Ltmp126-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	34                      # 34
	.word	.Ltmp143-.Lfunc_begin0
	.word	.Ltmp144-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	144                     # DW_OP_regx
	.byte	33                      # 33
	.word	0
	.word	0
.Ldebug_loc65:
	.word	.Ltmp149-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
	.section	.debug_abbrev,"",@progbits
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	14                      # DW_FORM_strp
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	16                      # DW_AT_stmt_list
	.byte	23                      # DW_FORM_sec_offset
	.byte	27                      # DW_AT_comp_dir
	.byte	14                      # DW_FORM_strp
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	53                      # DW_TAG_volatile_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	54                      # DW_AT_calling_convention
	.byte	11                      # DW_FORM_data1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
	.byte	33                      # DW_TAG_subrange_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	34                      # DW_AT_lower_bound
	.byte	11                      # DW_FORM_data1
	.byte	55                      # DW_AT_count
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	10                      # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
	.byte	57                      # DW_TAG_namespace
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	12                      # Abbreviation Code
	.byte	58                      # DW_TAG_imported_module
	.byte	0                       # DW_CHILDREN_no
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	24                      # DW_AT_import
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
	.byte	57                      # DW_TAG_namespace
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	14                      # Abbreviation Code
	.byte	8                       # DW_TAG_imported_declaration
	.byte	0                       # DW_CHILDREN_no
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	24                      # DW_AT_import
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	15                      # Abbreviation Code
	.byte	2                       # DW_TAG_class_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	54                      # DW_AT_calling_convention
	.byte	11                      # DW_FORM_data1
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	16                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	99                      # DW_AT_explicit
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	17                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	52                      # DW_AT_artificial
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	18                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	19                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	20                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	21                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	22                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	23                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	24                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	99                      # DW_AT_explicit
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	25                      # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	26                      # Abbreviation Code
	.byte	2                       # DW_TAG_class_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	27                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.ascii	"\207\001"              # DW_AT_noreturn
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	28                      # Abbreviation Code
	.byte	8                       # DW_TAG_imported_declaration
	.byte	0                       # DW_CHILDREN_no
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	24                      # DW_AT_import
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	29                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	30                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	0                       # DW_CHILDREN_no
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	31                      # Abbreviation Code
	.byte	19                      # DW_TAG_structure_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	54                      # DW_AT_calling_convention
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	32                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.ascii	"\207\001"              # DW_AT_noreturn
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	33                      # Abbreviation Code
	.byte	21                      # DW_TAG_subroutine_type
	.byte	0                       # DW_CHILDREN_no
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	34                      # Abbreviation Code
	.byte	38                      # DW_TAG_const_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	35                      # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	36                      # Abbreviation Code
	.byte	38                      # DW_TAG_const_type
	.byte	0                       # DW_CHILDREN_no
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	37                      # Abbreviation Code
	.byte	21                      # DW_TAG_subroutine_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	38                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.ascii	"\207\001"              # DW_AT_noreturn
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	39                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	40                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	41                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	5                       # DW_FORM_data2
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	60                      # DW_AT_declaration
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	42                      # Abbreviation Code
	.byte	16                      # DW_TAG_reference_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	43                      # Abbreviation Code
	.byte	59                      # DW_TAG_unspecified_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	44                      # Abbreviation Code
	.byte	66                      # DW_TAG_rvalue_reference_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	45                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	32                      # DW_AT_inline
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	46                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	47                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	48                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	32                      # DW_AT_inline
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	49                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	64                      # DW_AT_frame_base
	.byte	24                      # DW_FORM_exprloc
	.ascii	"\227B"                 # DW_AT_GNU_all_call_sites
	.byte	25                      # DW_FORM_flag_present
	.byte	110                     # DW_AT_linkage_name
	.byte	14                      # DW_FORM_strp
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	50                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	51                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	52                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	85                      # DW_AT_ranges
	.byte	23                      # DW_FORM_sec_offset
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	87                      # DW_AT_call_column
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	53                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	54                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	55                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	87                      # DW_AT_call_column
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	56                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	57                      # Abbreviation Code
	.byte	13                      # DW_TAG_member
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	56                      # DW_AT_data_member_location
	.byte	11                      # DW_FORM_data1
	.byte	50                      # DW_AT_accessibility
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	58                      # Abbreviation Code
	.byte	47                      # DW_TAG_template_type_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	59                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	71                      # DW_AT_specification
	.byte	19                      # DW_FORM_ref4
	.byte	32                      # DW_AT_inline
	.byte	11                      # DW_FORM_data1
	.byte	100                     # DW_AT_object_pointer
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	60                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	52                      # DW_AT_artificial
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	61                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	64                      # DW_AT_frame_base
	.byte	24                      # DW_FORM_exprloc
	.ascii	"\227B"                 # DW_AT_GNU_all_call_sites
	.byte	25                      # DW_FORM_flag_present
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	62                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	24                      # DW_FORM_exprloc
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	63                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	64                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	85                      # DW_AT_ranges
	.byte	23                      # DW_FORM_sec_offset
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	65                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
	.section	.debug_info,"",@progbits
.Lcu_begin0:
	.word	.Ldebug_info_end0-.Ldebug_info_start0 # Length of Unit
.Ldebug_info_start0:
	.half	4                       # DWARF version number
	.word	.debug_abbrev           # Offset Into Abbrev. Section
	.byte	4                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x12d6 DW_TAG_compile_unit
	.word	.Linfo_string0          # DW_AT_producer
	.half	26                      # DW_AT_language
	.word	.Linfo_string1          # DW_AT_name
	.word	.Lline_table_start0     # DW_AT_stmt_list
	.word	.Linfo_string2          # DW_AT_comp_dir
	.word	.Lfunc_begin0           # DW_AT_low_pc
	.word	.Lfunc_end1-.Lfunc_begin0 # DW_AT_high_pc
	.byte	2                       # Abbrev [2] 0x26:0xb DW_TAG_typedef
	.word	49                      # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	20                      # DW_AT_decl_line
	.byte	3                       # Abbrev [3] 0x31:0x5 DW_TAG_pointer_type
	.word	54                      # DW_AT_type
	.byte	4                       # Abbrev [4] 0x36:0x5 DW_TAG_volatile_type
	.word	59                      # DW_AT_type
	.byte	5                       # Abbrev [5] 0x3b:0x7 DW_TAG_base_type
	.word	.Linfo_string3          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x42:0x5 DW_TAG_pointer_type
	.word	71                      # DW_AT_type
	.byte	2                       # Abbrev [2] 0x47:0xb DW_TAG_typedef
	.word	82                      # DW_AT_type
	.word	.Linfo_string13         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	6                       # Abbrev [6] 0x52:0x3a DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.word	.Linfo_string12         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x5b:0xc DW_TAG_member
	.word	.Linfo_string5          # DW_AT_name
	.word	140                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x67:0xc DW_TAG_member
	.word	.Linfo_string7          # DW_AT_name
	.word	140                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	45                      # DW_AT_decl_line
	.byte	1                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x73:0xc DW_TAG_member
	.word	.Linfo_string8          # DW_AT_name
	.word	147                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x7f:0xc DW_TAG_member
	.word	.Linfo_string10         # DW_AT_name
	.word	167                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x8c:0x7 DW_TAG_base_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	8                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	8                       # Abbrev [8] 0x93:0xd DW_TAG_array_type
	.word	140                     # DW_AT_type
	.byte	9                       # Abbrev [9] 0x98:0x7 DW_TAG_subrange_type
	.word	160                     # DW_AT_type
	.byte	0                       # DW_AT_lower_bound
	.byte	1                       # DW_AT_count
	.byte	0                       # End Of Children Mark
	.byte	10                      # Abbrev [10] 0xa0:0x7 DW_TAG_base_type
	.word	.Linfo_string9          # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	7                       # DW_AT_encoding
	.byte	5                       # Abbrev [5] 0xa7:0x7 DW_TAG_base_type
	.word	.Linfo_string11         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0xae:0x5 DW_TAG_pointer_type
	.word	179                     # DW_AT_type
	.byte	2                       # Abbrev [2] 0xb3:0xb DW_TAG_typedef
	.word	190                     # DW_AT_type
	.word	.Linfo_string17         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.byte	6                       # Abbrev [6] 0xbe:0x3a DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.word	.Linfo_string16         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0xc7:0xc DW_TAG_member
	.word	.Linfo_string14         # DW_AT_name
	.word	140                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0xd3:0xc DW_TAG_member
	.word	.Linfo_string15         # DW_AT_name
	.word	140                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.byte	1                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0xdf:0xc DW_TAG_member
	.word	.Linfo_string8          # DW_AT_name
	.word	147                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0xeb:0xc DW_TAG_member
	.word	.Linfo_string10         # DW_AT_name
	.word	167                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0xf8:0x5 DW_TAG_pointer_type
	.word	59                      # DW_AT_type
	.byte	11                      # Abbrev [11] 0xfd:0xd DW_TAG_namespace
	.word	.Linfo_string18         # DW_AT_name
	.byte	12                      # Abbrev [12] 0x102:0x7 DW_TAG_imported_module
	.byte	3                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.word	271                     # DW_AT_import
	.byte	0                       # End Of Children Mark
	.byte	11                      # Abbrev [11] 0x10a:0x32d DW_TAG_namespace
	.word	.Linfo_string19         # DW_AT_name
	.byte	13                      # Abbrev [13] 0x10f:0x5 DW_TAG_namespace
	.word	.Linfo_string20         # DW_AT_name
	.byte	14                      # Abbrev [14] 0x114:0x7 DW_TAG_imported_declaration
	.byte	5                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.word	1079                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x11b:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	127                     # DW_AT_decl_line
	.word	1096                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x122:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	128                     # DW_AT_decl_line
	.word	1108                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x129:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	130                     # DW_AT_decl_line
	.word	1156                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x130:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	134                     # DW_AT_decl_line
	.word	1163                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x137:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	140                     # DW_AT_decl_line
	.word	1186                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x13e:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	141                     # DW_AT_decl_line
	.word	1227                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x145:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	142                     # DW_AT_decl_line
	.word	1244                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x14c:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	143                     # DW_AT_decl_line
	.word	1261                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x153:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	144                     # DW_AT_decl_line
	.word	1348                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x15a:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	145                     # DW_AT_decl_line
	.word	1370                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x161:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	146                     # DW_AT_decl_line
	.word	1392                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x168:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	147                     # DW_AT_decl_line
	.word	1405                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x16f:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	148                     # DW_AT_decl_line
	.word	1418                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x176:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	149                     # DW_AT_decl_line
	.word	1440                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x17d:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	150                     # DW_AT_decl_line
	.word	1457                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x184:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	151                     # DW_AT_decl_line
	.word	1479                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x18b:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	153                     # DW_AT_decl_line
	.word	1496                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x192:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	154                     # DW_AT_decl_line
	.word	1518                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x199:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	155                     # DW_AT_decl_line
	.word	1557                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1a0:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	157                     # DW_AT_decl_line
	.word	1584                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1a7:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	163                     # DW_AT_decl_line
	.word	1612                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1ae:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	164                     # DW_AT_decl_line
	.word	1623                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1b5:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	165                     # DW_AT_decl_line
	.word	1645                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1bc:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	166                     # DW_AT_decl_line
	.word	1658                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1c3:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	167                     # DW_AT_decl_line
	.word	1685                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1ca:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	168                     # DW_AT_decl_line
	.word	1712                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1d1:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	169                     # DW_AT_decl_line
	.word	1746                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1d8:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	171                     # DW_AT_decl_line
	.word	1763                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1df:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	172                     # DW_AT_decl_line
	.word	1800                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1e6:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	240                     # DW_AT_decl_line
	.word	1917                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1ed:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	242                     # DW_AT_decl_line
	.word	1965                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1f4:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	244                     # DW_AT_decl_line
	.word	1978                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x1fb:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	245                     # DW_AT_decl_line
	.word	1890                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x202:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	246                     # DW_AT_decl_line
	.word	1996                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x209:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	248                     # DW_AT_decl_line
	.word	2019                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x210:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	249                     # DW_AT_decl_line
	.word	2100                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x217:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	250                     # DW_AT_decl_line
	.word	2037                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x21e:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	251                     # DW_AT_decl_line
	.word	2065                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x225:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	252                     # DW_AT_decl_line
	.word	2129                    # DW_AT_import
	.byte	11                      # Abbrev [11] 0x22c:0x13a DW_TAG_namespace
	.word	.Linfo_string75         # DW_AT_name
	.byte	15                      # Abbrev [15] 0x231:0x12d DW_TAG_class_type
	.byte	4                       # DW_AT_calling_convention
	.word	.Linfo_string77         # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	8                       # DW_AT_decl_file
	.byte	79                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x23a:0xc DW_TAG_member
	.word	.Linfo_string76         # DW_AT_name
	.word	1298                    # DW_AT_type
	.byte	8                       # DW_AT_decl_file
	.byte	81                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	16                      # Abbrev [16] 0x246:0x12 DW_TAG_subprogram
	.word	.Linfo_string77         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
                                        # DW_AT_explicit
	.byte	17                      # Abbrev [17] 0x24d:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x252:0x5 DW_TAG_formal_parameter
	.word	1298                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x258:0x11 DW_TAG_subprogram
	.word	.Linfo_string78         # DW_AT_linkage_name
	.word	.Linfo_string79         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	85                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	17                      # Abbrev [17] 0x263:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x269:0x11 DW_TAG_subprogram
	.word	.Linfo_string80         # DW_AT_linkage_name
	.word	.Linfo_string81         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	17                      # Abbrev [17] 0x274:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	20                      # Abbrev [20] 0x27a:0x15 DW_TAG_subprogram
	.word	.Linfo_string82         # DW_AT_linkage_name
	.word	.Linfo_string83         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	88                      # DW_AT_decl_line
	.word	1298                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	17                      # Abbrev [17] 0x289:0x5 DW_TAG_formal_parameter
	.word	2164                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	21                      # Abbrev [21] 0x28f:0xe DW_TAG_subprogram
	.word	.Linfo_string77         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	96                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x297:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	21                      # Abbrev [21] 0x29d:0x13 DW_TAG_subprogram
	.word	.Linfo_string77         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	98                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x2a5:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x2aa:0x5 DW_TAG_formal_parameter
	.word	2174                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	21                      # Abbrev [21] 0x2b0:0x13 DW_TAG_subprogram
	.word	.Linfo_string77         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x2b8:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x2bd:0x5 DW_TAG_formal_parameter
	.word	870                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	21                      # Abbrev [21] 0x2c3:0x13 DW_TAG_subprogram
	.word	.Linfo_string77         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	105                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x2cb:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x2d0:0x5 DW_TAG_formal_parameter
	.word	2184                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0x2d6:0x1b DW_TAG_subprogram
	.word	.Linfo_string86         # DW_AT_linkage_name
	.word	.Linfo_string87         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	118                     # DW_AT_decl_line
	.word	2189                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x2e6:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x2eb:0x5 DW_TAG_formal_parameter
	.word	2174                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0x2f1:0x1b DW_TAG_subprogram
	.word	.Linfo_string88         # DW_AT_linkage_name
	.word	.Linfo_string87         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	122                     # DW_AT_decl_line
	.word	2189                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x301:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x306:0x5 DW_TAG_formal_parameter
	.word	2184                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	21                      # Abbrev [21] 0x30c:0xe DW_TAG_subprogram
	.word	.Linfo_string89         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	129                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x314:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	23                      # Abbrev [23] 0x31a:0x17 DW_TAG_subprogram
	.word	.Linfo_string90         # DW_AT_linkage_name
	.word	.Linfo_string91         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	132                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x326:0x5 DW_TAG_formal_parameter
	.word	2159                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0x32b:0x5 DW_TAG_formal_parameter
	.word	2189                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	24                      # Abbrev [24] 0x331:0x16 DW_TAG_subprogram
	.word	.Linfo_string92         # DW_AT_linkage_name
	.word	.Linfo_string93         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	144                     # DW_AT_decl_line
	.word	2194                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
                                        # DW_AT_explicit
	.byte	17                      # Abbrev [17] 0x341:0x5 DW_TAG_formal_parameter
	.word	2164                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0x347:0x16 DW_TAG_subprogram
	.word	.Linfo_string95         # DW_AT_linkage_name
	.word	.Linfo_string96         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	153                     # DW_AT_decl_line
	.word	2201                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0x357:0x5 DW_TAG_formal_parameter
	.word	2164                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	14                      # Abbrev [14] 0x35e:0x7 DW_TAG_imported_declaration
	.byte	8                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.word	894                     # DW_AT_import
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x366:0xc DW_TAG_typedef
	.word	2179                    # DW_AT_type
	.word	.Linfo_string85         # DW_AT_name
	.byte	9                       # DW_AT_decl_file
	.half	258                     # DW_AT_decl_line
	.byte	26                      # Abbrev [26] 0x372:0x5 DW_TAG_class_type
	.word	.Linfo_string97         # DW_AT_name
                                        # DW_AT_declaration
	.byte	14                      # Abbrev [14] 0x377:0x7 DW_TAG_imported_declaration
	.byte	8                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.word	561                     # DW_AT_import
	.byte	27                      # Abbrev [27] 0x37e:0x11 DW_TAG_subprogram
	.word	.Linfo_string98         # DW_AT_linkage_name
	.word	.Linfo_string99         # DW_AT_name
	.byte	8                       # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
                                        # DW_AT_noreturn
	.byte	18                      # Abbrev [18] 0x389:0x5 DW_TAG_formal_parameter
	.word	561                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	14                      # Abbrev [14] 0x38f:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
	.word	2211                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x396:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	102                     # DW_AT_decl_line
	.word	2228                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x39d:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
	.word	2245                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x3a4:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	140                     # DW_AT_decl_line
	.word	2262                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x3ab:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.word	2284                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x3b2:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	180                     # DW_AT_decl_line
	.word	2301                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x3b9:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	199                     # DW_AT_decl_line
	.word	2318                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x3c0:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	218                     # DW_AT_decl_line
	.word	2335                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x3c7:0x7 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.byte	237                     # DW_AT_decl_line
	.word	2352                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3ce:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	256                     # DW_AT_decl_line
	.word	2369                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3d6:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	275                     # DW_AT_decl_line
	.word	2386                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3de:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	296                     # DW_AT_decl_line
	.word	2408                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3e6:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	315                     # DW_AT_decl_line
	.word	2430                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3ee:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	334                     # DW_AT_decl_line
	.word	2452                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3f6:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	353                     # DW_AT_decl_line
	.word	2469                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x3fe:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	372                     # DW_AT_decl_line
	.word	2486                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x406:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	384                     # DW_AT_decl_line
	.word	2513                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x40e:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	421                     # DW_AT_decl_line
	.word	2535                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x416:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	440                     # DW_AT_decl_line
	.word	2552                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x41e:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	459                     # DW_AT_decl_line
	.word	2569                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x426:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	478                     # DW_AT_decl_line
	.word	2586                    # DW_AT_import
	.byte	28                      # Abbrev [28] 0x42e:0x8 DW_TAG_imported_declaration
	.byte	11                      # DW_AT_decl_file
	.half	497                     # DW_AT_decl_line
	.word	2603                    # DW_AT_import
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x437:0x11 DW_TAG_subprogram
	.word	.Linfo_string21         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	70                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x442:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x448:0xb DW_TAG_typedef
	.word	1107                    # DW_AT_type
	.word	.Linfo_string22         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	39                      # DW_AT_decl_line
	.byte	30                      # Abbrev [30] 0x453:0x1 DW_TAG_structure_type
                                        # DW_AT_declaration
	.byte	2                       # Abbrev [2] 0x454:0xb DW_TAG_typedef
	.word	1119                    # DW_AT_type
	.word	.Linfo_string26         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	45                      # DW_AT_decl_line
	.byte	31                      # Abbrev [31] 0x45f:0x1e DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.byte	8                       # DW_AT_byte_size
	.byte	4                       # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x464:0xc DW_TAG_member
	.word	.Linfo_string23         # DW_AT_name
	.word	1149                    # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x470:0xc DW_TAG_member
	.word	.Linfo_string25         # DW_AT_name
	.word	1149                    # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x47d:0x7 DW_TAG_base_type
	.word	.Linfo_string24         # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	32                      # Abbrev [32] 0x484:0x7 DW_TAG_subprogram
	.word	.Linfo_string27         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
                                        # DW_AT_noreturn
	.byte	29                      # Abbrev [29] 0x48b:0x11 DW_TAG_subprogram
	.word	.Linfo_string28         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	76                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x496:0x5 DW_TAG_formal_parameter
	.word	1180                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x49c:0x5 DW_TAG_pointer_type
	.word	1185                    # DW_AT_type
	.byte	33                      # Abbrev [33] 0x4a1:0x1 DW_TAG_subroutine_type
	.byte	29                      # Abbrev [29] 0x4a2:0x11 DW_TAG_subprogram
	.word	.Linfo_string29         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	77                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x4ad:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x4b3:0x7 DW_TAG_base_type
	.word	.Linfo_string30         # DW_AT_name
	.byte	4                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x4ba:0x5 DW_TAG_pointer_type
	.word	1215                    # DW_AT_type
	.byte	34                      # Abbrev [34] 0x4bf:0x5 DW_TAG_const_type
	.word	1220                    # DW_AT_type
	.byte	5                       # Abbrev [5] 0x4c4:0x7 DW_TAG_base_type
	.word	.Linfo_string31         # DW_AT_name
	.byte	8                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	29                      # Abbrev [29] 0x4cb:0x11 DW_TAG_subprogram
	.word	.Linfo_string32         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	81                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x4d6:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x4dc:0x11 DW_TAG_subprogram
	.word	.Linfo_string33         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
	.word	1149                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x4e7:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x4ed:0x25 DW_TAG_subprogram
	.word	.Linfo_string34         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	85                      # DW_AT_decl_line
	.word	1298                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x4f8:0x5 DW_TAG_formal_parameter
	.word	1299                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x4fd:0x5 DW_TAG_formal_parameter
	.word	1299                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x502:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x507:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x50c:0x5 DW_TAG_formal_parameter
	.word	1316                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	35                      # Abbrev [35] 0x512:0x1 DW_TAG_pointer_type
	.byte	3                       # Abbrev [3] 0x513:0x5 DW_TAG_pointer_type
	.word	1304                    # DW_AT_type
	.byte	36                      # Abbrev [36] 0x518:0x1 DW_TAG_const_type
	.byte	2                       # Abbrev [2] 0x519:0xb DW_TAG_typedef
	.word	167                     # DW_AT_type
	.word	.Linfo_string35         # DW_AT_name
	.byte	7                       # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.byte	2                       # Abbrev [2] 0x524:0xb DW_TAG_typedef
	.word	1327                    # DW_AT_type
	.word	.Linfo_string36         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	57                      # DW_AT_decl_line
	.byte	3                       # Abbrev [3] 0x52f:0x5 DW_TAG_pointer_type
	.word	1332                    # DW_AT_type
	.byte	37                      # Abbrev [37] 0x534:0x10 DW_TAG_subroutine_type
	.word	59                      # DW_AT_type
	.byte	18                      # Abbrev [18] 0x539:0x5 DW_TAG_formal_parameter
	.word	1299                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x53e:0x5 DW_TAG_formal_parameter
	.word	1299                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x544:0x16 DW_TAG_subprogram
	.word	.Linfo_string37         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.word	1298                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x54f:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x554:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x55a:0x16 DW_TAG_subprogram
	.word	.Linfo_string38         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	1096                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x565:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	18                      # Abbrev [18] 0x56a:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	38                      # Abbrev [38] 0x570:0xd DW_TAG_subprogram
	.word	.Linfo_string39         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
                                        # DW_AT_noreturn
	.byte	18                      # Abbrev [18] 0x577:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	39                      # Abbrev [39] 0x57d:0xd DW_TAG_subprogram
	.word	.Linfo_string40         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	94                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x584:0x5 DW_TAG_formal_parameter
	.word	1298                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x58a:0x11 DW_TAG_subprogram
	.word	.Linfo_string41         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	95                      # DW_AT_decl_line
	.word	1435                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x595:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x59b:0x5 DW_TAG_pointer_type
	.word	1220                    # DW_AT_type
	.byte	29                      # Abbrev [29] 0x5a0:0x11 DW_TAG_subprogram
	.word	.Linfo_string42         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	1149                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x5ab:0x5 DW_TAG_formal_parameter
	.word	1149                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x5b1:0x16 DW_TAG_subprogram
	.word	.Linfo_string43         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	104                     # DW_AT_decl_line
	.word	1108                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x5bc:0x5 DW_TAG_formal_parameter
	.word	1149                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x5c1:0x5 DW_TAG_formal_parameter
	.word	1149                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x5c7:0x11 DW_TAG_subprogram
	.word	.Linfo_string44         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	105                     # DW_AT_decl_line
	.word	1298                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x5d2:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x5d8:0x16 DW_TAG_subprogram
	.word	.Linfo_string45         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	106                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x5e3:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x5e8:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x5ee:0x1b DW_TAG_subprogram
	.word	.Linfo_string46         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.word	1305                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x5f9:0x5 DW_TAG_formal_parameter
	.word	1545                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x5fe:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x603:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x609:0x5 DW_TAG_pointer_type
	.word	1550                    # DW_AT_type
	.byte	5                       # Abbrev [5] 0x60e:0x7 DW_TAG_base_type
	.word	.Linfo_string47         # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	29                      # Abbrev [29] 0x615:0x1b DW_TAG_subprogram
	.word	.Linfo_string48         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	108                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x620:0x5 DW_TAG_formal_parameter
	.word	1545                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x625:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x62a:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	39                      # Abbrev [39] 0x630:0x1c DW_TAG_subprogram
	.word	.Linfo_string49         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	140                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x637:0x5 DW_TAG_formal_parameter
	.word	1298                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x63c:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x641:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x646:0x5 DW_TAG_formal_parameter
	.word	1316                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	40                      # Abbrev [40] 0x64c:0xb DW_TAG_subprogram
	.word	.Linfo_string50         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	141                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	29                      # Abbrev [29] 0x657:0x16 DW_TAG_subprogram
	.word	.Linfo_string51         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	142                     # DW_AT_decl_line
	.word	1298                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x662:0x5 DW_TAG_formal_parameter
	.word	1298                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x667:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	39                      # Abbrev [39] 0x66d:0xd DW_TAG_subprogram
	.word	.Linfo_string52         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	156                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x674:0x5 DW_TAG_formal_parameter
	.word	167                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x67a:0x16 DW_TAG_subprogram
	.word	.Linfo_string53         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	157                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x685:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x68a:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x690:0x5 DW_TAG_pointer_type
	.word	1435                    # DW_AT_type
	.byte	29                      # Abbrev [29] 0x695:0x1b DW_TAG_subprogram
	.word	.Linfo_string54         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	168                     # DW_AT_decl_line
	.word	1149                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x6a0:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x6a5:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x6aa:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x6b0:0x1b DW_TAG_subprogram
	.word	.Linfo_string55         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	170                     # DW_AT_decl_line
	.word	1739                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x6bb:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x6c0:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x6c5:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x6cb:0x7 DW_TAG_base_type
	.word	.Linfo_string56         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	29                      # Abbrev [29] 0x6d2:0x11 DW_TAG_subprogram
	.word	.Linfo_string57         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	188                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x6dd:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x6e3:0x1b DW_TAG_subprogram
	.word	.Linfo_string58         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	114                     # DW_AT_decl_line
	.word	1305                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x6ee:0x5 DW_TAG_formal_parameter
	.word	1435                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x6f3:0x5 DW_TAG_formal_parameter
	.word	1790                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x6f8:0x5 DW_TAG_formal_parameter
	.word	1305                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x6fe:0x5 DW_TAG_pointer_type
	.word	1795                    # DW_AT_type
	.byte	34                      # Abbrev [34] 0x703:0x5 DW_TAG_const_type
	.word	1550                    # DW_AT_type
	.byte	29                      # Abbrev [29] 0x708:0x16 DW_TAG_subprogram
	.word	.Linfo_string59         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	110                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x713:0x5 DW_TAG_formal_parameter
	.word	1435                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x718:0x5 DW_TAG_formal_parameter
	.word	1550                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	11                      # Abbrev [11] 0x71e:0x5f DW_TAG_namespace
	.word	.Linfo_string60         # DW_AT_name
	.byte	14                      # Abbrev [14] 0x723:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	200                     # DW_AT_decl_line
	.word	1917                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x72a:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	206                     # DW_AT_decl_line
	.word	1965                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x731:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	210                     # DW_AT_decl_line
	.word	1978                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x738:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	216                     # DW_AT_decl_line
	.word	1996                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x73f:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	227                     # DW_AT_decl_line
	.word	2019                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x746:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	228                     # DW_AT_decl_line
	.word	2037                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x74d:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	229                     # DW_AT_decl_line
	.word	2065                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x754:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	231                     # DW_AT_decl_line
	.word	2100                    # DW_AT_import
	.byte	14                      # Abbrev [14] 0x75b:0x7 DW_TAG_imported_declaration
	.byte	6                       # DW_AT_decl_file
	.byte	232                     # DW_AT_decl_line
	.word	2129                    # DW_AT_import
	.byte	20                      # Abbrev [20] 0x762:0x1a DW_TAG_subprogram
	.word	.Linfo_string74         # DW_AT_linkage_name
	.word	.Linfo_string38         # DW_AT_name
	.byte	6                       # DW_AT_decl_file
	.byte	213                     # DW_AT_decl_line
	.word	1917                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x771:0x5 DW_TAG_formal_parameter
	.word	1958                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x776:0x5 DW_TAG_formal_parameter
	.word	1958                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	2                       # Abbrev [2] 0x77d:0xb DW_TAG_typedef
	.word	1928                    # DW_AT_type
	.word	.Linfo_string62         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.byte	31                      # Abbrev [31] 0x788:0x1e DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.byte	16                      # DW_AT_byte_size
	.byte	4                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x78d:0xc DW_TAG_member
	.word	.Linfo_string23         # DW_AT_name
	.word	1958                    # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x799:0xc DW_TAG_member
	.word	.Linfo_string25         # DW_AT_name
	.word	1958                    # DW_AT_type
	.byte	4                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x7a6:0x7 DW_TAG_base_type
	.word	.Linfo_string61         # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	38                      # Abbrev [38] 0x7ad:0xd DW_TAG_subprogram
	.word	.Linfo_string63         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	199                     # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
                                        # DW_AT_noreturn
	.byte	18                      # Abbrev [18] 0x7b4:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	41                      # Abbrev [41] 0x7ba:0x12 DW_TAG_subprogram
	.word	.Linfo_string64         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.half	264                     # DW_AT_decl_line
	.word	1958                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x7c6:0x5 DW_TAG_formal_parameter
	.word	1958                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	41                      # Abbrev [41] 0x7cc:0x17 DW_TAG_subprogram
	.word	.Linfo_string65         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.half	265                     # DW_AT_decl_line
	.word	1917                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x7d8:0x5 DW_TAG_formal_parameter
	.word	1958                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x7dd:0x5 DW_TAG_formal_parameter
	.word	1958                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	41                      # Abbrev [41] 0x7e3:0x12 DW_TAG_subprogram
	.word	.Linfo_string66         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.half	260                     # DW_AT_decl_line
	.word	1958                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x7ef:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	41                      # Abbrev [41] 0x7f5:0x1c DW_TAG_subprogram
	.word	.Linfo_string67         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.half	266                     # DW_AT_decl_line
	.word	1958                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x801:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x806:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x80b:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	41                      # Abbrev [41] 0x811:0x1c DW_TAG_subprogram
	.word	.Linfo_string68         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.half	270                     # DW_AT_decl_line
	.word	2093                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x81d:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x822:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x827:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x82d:0x7 DW_TAG_base_type
	.word	.Linfo_string69         # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	29                      # Abbrev [29] 0x834:0x16 DW_TAG_subprogram
	.word	.Linfo_string70         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	160                     # DW_AT_decl_line
	.word	2122                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x83f:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x844:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x84a:0x7 DW_TAG_base_type
	.word	.Linfo_string71         # DW_AT_name
	.byte	4                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	41                      # Abbrev [41] 0x851:0x17 DW_TAG_subprogram
	.word	.Linfo_string72         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.half	321                     # DW_AT_decl_line
	.word	2152                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x85d:0x5 DW_TAG_formal_parameter
	.word	1210                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x862:0x5 DW_TAG_formal_parameter
	.word	1680                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x868:0x7 DW_TAG_base_type
	.word	.Linfo_string73         # DW_AT_name
	.byte	4                       # DW_AT_encoding
	.byte	16                      # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x86f:0x5 DW_TAG_pointer_type
	.word	561                     # DW_AT_type
	.byte	3                       # Abbrev [3] 0x874:0x5 DW_TAG_pointer_type
	.word	2169                    # DW_AT_type
	.byte	34                      # Abbrev [34] 0x879:0x5 DW_TAG_const_type
	.word	561                     # DW_AT_type
	.byte	42                      # Abbrev [42] 0x87e:0x5 DW_TAG_reference_type
	.word	2169                    # DW_AT_type
	.byte	43                      # Abbrev [43] 0x883:0x5 DW_TAG_unspecified_type
	.word	.Linfo_string84         # DW_AT_name
	.byte	44                      # Abbrev [44] 0x888:0x5 DW_TAG_rvalue_reference_type
	.word	561                     # DW_AT_type
	.byte	42                      # Abbrev [42] 0x88d:0x5 DW_TAG_reference_type
	.word	561                     # DW_AT_type
	.byte	5                       # Abbrev [5] 0x892:0x7 DW_TAG_base_type
	.word	.Linfo_string94         # DW_AT_name
	.byte	2                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x899:0x5 DW_TAG_pointer_type
	.word	2206                    # DW_AT_type
	.byte	34                      # Abbrev [34] 0x89e:0x5 DW_TAG_const_type
	.word	882                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0x8a3:0x11 DW_TAG_subprogram
	.word	.Linfo_string100        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	102                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x8ae:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x8b4:0x11 DW_TAG_subprogram
	.word	.Linfo_string101        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x8bf:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x8c5:0x11 DW_TAG_subprogram
	.word	.Linfo_string102        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x8d0:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x8d6:0x16 DW_TAG_subprogram
	.word	.Linfo_string103        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	104                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x8e1:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x8e6:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x8ec:0x11 DW_TAG_subprogram
	.word	.Linfo_string104        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x8f7:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x8fd:0x11 DW_TAG_subprogram
	.word	.Linfo_string105        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x908:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x90e:0x11 DW_TAG_subprogram
	.word	.Linfo_string106        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	105                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x919:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x91f:0x11 DW_TAG_subprogram
	.word	.Linfo_string107        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	107                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x92a:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x930:0x11 DW_TAG_subprogram
	.word	.Linfo_string108        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	94                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x93b:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x941:0x11 DW_TAG_subprogram
	.word	.Linfo_string109        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	95                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x94c:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x952:0x16 DW_TAG_subprogram
	.word	.Linfo_string110        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	113                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x95d:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x962:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x968:0x16 DW_TAG_subprogram
	.word	.Linfo_string111        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	91                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x973:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x978:0x5 DW_TAG_formal_parameter
	.word	248                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x97e:0x16 DW_TAG_subprogram
	.word	.Linfo_string112        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	108                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x989:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x98e:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x994:0x11 DW_TAG_subprogram
	.word	.Linfo_string113        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	109                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x99f:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x9a5:0x11 DW_TAG_subprogram
	.word	.Linfo_string114        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	110                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x9b0:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x9b6:0x16 DW_TAG_subprogram
	.word	.Linfo_string115        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x9c1:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x9c6:0x5 DW_TAG_formal_parameter
	.word	2508                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x9cc:0x5 DW_TAG_pointer_type
	.word	1203                    # DW_AT_type
	.byte	29                      # Abbrev [29] 0x9d1:0x16 DW_TAG_subprogram
	.word	.Linfo_string116        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	111                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x9dc:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	18                      # Abbrev [18] 0x9e1:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x9e7:0x11 DW_TAG_subprogram
	.word	.Linfo_string117        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	88                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0x9f2:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x9f8:0x11 DW_TAG_subprogram
	.word	.Linfo_string118        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	106                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0xa03:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xa09:0x11 DW_TAG_subprogram
	.word	.Linfo_string119        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0xa14:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xa1a:0x11 DW_TAG_subprogram
	.word	.Linfo_string120        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	89                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0xa25:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xa2b:0x11 DW_TAG_subprogram
	.word	.Linfo_string121        # DW_AT_name
	.byte	10                      # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.word	1203                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	18                      # Abbrev [18] 0xa36:0x5 DW_TAG_formal_parameter
	.word	1203                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xa3c:0x39 DW_TAG_subprogram
	.word	.Linfo_string122        # DW_AT_linkage_name
	.word	.Linfo_string123        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xa48:0xb DW_TAG_formal_parameter
	.word	.Linfo_string124        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	46                      # Abbrev [46] 0xa53:0xb DW_TAG_formal_parameter
	.word	.Linfo_string125        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xa5e:0xb DW_TAG_variable
	.word	.Linfo_string126        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	94                      # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xa69:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xa75:0x5a DW_TAG_subprogram
	.word	.Linfo_string128        # DW_AT_linkage_name
	.word	.Linfo_string129        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xa81:0xb DW_TAG_formal_parameter
	.word	.Linfo_string124        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	46                      # Abbrev [46] 0xa8c:0xb DW_TAG_formal_parameter
	.word	.Linfo_string130        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	46                      # Abbrev [46] 0xa97:0xb DW_TAG_formal_parameter
	.word	.Linfo_string125        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	46                      # Abbrev [46] 0xaa2:0xb DW_TAG_formal_parameter
	.word	.Linfo_string131        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xaad:0xb DW_TAG_variable
	.word	.Linfo_string132        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	108                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xab8:0xb DW_TAG_variable
	.word	.Linfo_string126        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	105                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0xac3:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	104                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xacf:0x2e DW_TAG_subprogram
	.word	.Linfo_string133        # DW_AT_linkage_name
	.word	.Linfo_string134        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	207                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xadb:0xb DW_TAG_formal_parameter
	.word	.Linfo_string135        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	207                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	46                      # Abbrev [46] 0xae6:0xb DW_TAG_formal_parameter
	.word	.Linfo_string136        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	207                     # DW_AT_decl_line
	.word	2813                    # DW_AT_type
	.byte	47                      # Abbrev [47] 0xaf1:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	208                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0xafd:0x5 DW_TAG_pointer_type
	.word	140                     # DW_AT_type
	.byte	45                      # Abbrev [45] 0xb02:0x2e DW_TAG_subprogram
	.word	.Linfo_string137        # DW_AT_linkage_name
	.word	.Linfo_string138        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xb0e:0xb DW_TAG_formal_parameter
	.word	.Linfo_string130        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0xb19:0xb DW_TAG_variable
	.word	.Linfo_string139        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	124                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xb24:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	123                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xb30:0x2e DW_TAG_subprogram
	.word	.Linfo_string140        # DW_AT_linkage_name
	.word	.Linfo_string141        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	216                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xb3c:0xb DW_TAG_formal_parameter
	.word	.Linfo_string130        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	216                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0xb47:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xb52:0xb DW_TAG_variable
	.word	.Linfo_string126        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	218                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xb5e:0x39 DW_TAG_subprogram
	.word	.Linfo_string142        # DW_AT_linkage_name
	.word	.Linfo_string143        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	142                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xb6a:0xb DW_TAG_formal_parameter
	.word	.Linfo_string124        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	142                     # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	46                      # Abbrev [46] 0xb75:0xb DW_TAG_formal_parameter
	.word	.Linfo_string130        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	142                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0xb80:0xb DW_TAG_variable
	.word	.Linfo_string132        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	144                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xb8b:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	143                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	48                      # Abbrev [48] 0xb97:0x27 DW_TAG_subprogram
	.word	.Linfo_string144        # DW_AT_linkage_name
	.word	.Linfo_string145        # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xba7:0xb DW_TAG_formal_parameter
	.word	.Linfo_string136        # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
	.word	248                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0xbb2:0xb DW_TAG_variable
	.word	.Linfo_string146        # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	48                      # Abbrev [48] 0xbbe:0x32 DW_TAG_subprogram
	.word	.Linfo_string147        # DW_AT_linkage_name
	.word	.Linfo_string148        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	239                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xbce:0xb DW_TAG_formal_parameter
	.word	.Linfo_string149        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	239                     # DW_AT_decl_line
	.word	248                     # DW_AT_type
	.byte	46                      # Abbrev [46] 0xbd9:0xb DW_TAG_formal_parameter
	.word	.Linfo_string150        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	239                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xbe4:0xb DW_TAG_variable
	.word	.Linfo_string146        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	240                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	48                      # Abbrev [48] 0xbf0:0x27 DW_TAG_subprogram
	.word	.Linfo_string151        # DW_AT_linkage_name
	.word	.Linfo_string152        # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	122                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xc00:0xb DW_TAG_formal_parameter
	.word	.Linfo_string136        # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	122                     # DW_AT_decl_line
	.word	248                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0xc0b:0xb DW_TAG_variable
	.word	.Linfo_string146        # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	122                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xc17:0x2e DW_TAG_subprogram
	.word	.Linfo_string153        # DW_AT_linkage_name
	.word	.Linfo_string154        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	227                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xc23:0xb DW_TAG_formal_parameter
	.word	.Linfo_string124        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	227                     # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xc2e:0xb DW_TAG_variable
	.word	.Linfo_string127        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	228                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0xc39:0xb DW_TAG_variable
	.word	.Linfo_string126        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	229                     # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	45                      # Abbrev [45] 0xc45:0x18 DW_TAG_subprogram
	.word	.Linfo_string155        # DW_AT_linkage_name
	.word	.Linfo_string156        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	165                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	46                      # Abbrev [46] 0xc51:0xb DW_TAG_formal_parameter
	.word	.Linfo_string124        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	165                     # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	49                      # Abbrev [49] 0xc5d:0x2c8 DW_TAG_subprogram
	.word	.Lfunc_begin0           # DW_AT_low_pc
	.word	.Lfunc_end0-.Lfunc_begin0 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string176        # DW_AT_linkage_name
	.word	.Linfo_string177        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	174                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	50                      # Abbrev [50] 0xc72:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc0            # DW_AT_location
	.word	.Linfo_string124        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	174                     # DW_AT_decl_line
	.word	66                      # DW_AT_type
	.byte	50                      # Abbrev [50] 0xc81:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc1            # DW_AT_location
	.word	.Linfo_string130        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	174                     # DW_AT_decl_line
	.word	174                     # DW_AT_type
	.byte	51                      # Abbrev [51] 0xc90:0xf DW_TAG_variable
	.word	.Ldebug_loc2            # DW_AT_location
	.word	.Linfo_string125        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	175                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	51                      # Abbrev [51] 0xc9f:0xf DW_TAG_variable
	.word	.Ldebug_loc6            # DW_AT_location
	.word	.Linfo_string131        # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	177                     # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	52                      # Abbrev [52] 0xcae:0x28 DW_TAG_inlined_subroutine
	.word	2620                    # DW_AT_abstract_origin
	.word	.Ldebug_ranges0         # DW_AT_ranges
	.byte	2                       # DW_AT_call_file
	.byte	185                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xcba:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc5            # DW_AT_location
	.word	2632                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xcc3:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc4            # DW_AT_location
	.word	2643                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xccc:0x9 DW_TAG_variable
	.word	.Ldebug_loc3            # DW_AT_location
	.word	2654                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xcd6:0x73 DW_TAG_inlined_subroutine
	.word	2677                    # DW_AT_abstract_origin
	.word	.Ltmp12                 # DW_AT_low_pc
	.word	.Ltmp25-.Ltmp12         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	189                     # DW_AT_call_line
	.byte	17                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xce6:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc7            # DW_AT_location
	.word	2689                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xcef:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc8            # DW_AT_location
	.word	2700                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xcf8:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc9            # DW_AT_location
	.word	2711                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xd01:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc10           # DW_AT_location
	.word	2722                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xd0a:0x9 DW_TAG_variable
	.word	.Ldebug_loc11           # DW_AT_location
	.word	2733                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xd13:0x9 DW_TAG_variable
	.word	.Ldebug_loc12           # DW_AT_location
	.word	2744                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0xd1c:0x2c DW_TAG_inlined_subroutine
	.word	2767                    # DW_AT_abstract_origin
	.word	.Ltmp14                 # DW_AT_low_pc
	.word	.Ltmp22-.Ltmp14         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	109                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xd2c:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc15           # DW_AT_location
	.word	2779                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xd35:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc14           # DW_AT_location
	.word	2790                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xd3e:0x9 DW_TAG_variable
	.word	.Ldebug_loc13           # DW_AT_location
	.word	2801                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	52                      # Abbrev [52] 0xd49:0x80 DW_TAG_inlined_subroutine
	.word	2818                    # DW_AT_abstract_origin
	.word	.Ldebug_ranges1         # DW_AT_ranges
	.byte	2                       # DW_AT_call_file
	.byte	192                     # DW_AT_call_line
	.byte	17                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xd55:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc16           # DW_AT_location
	.word	2830                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xd5e:0x9 DW_TAG_variable
	.word	.Ldebug_loc20           # DW_AT_location
	.word	2841                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xd67:0x9 DW_TAG_variable
	.word	.Ldebug_loc21           # DW_AT_location
	.word	2852                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0xd70:0x2c DW_TAG_inlined_subroutine
	.word	2767                    # DW_AT_abstract_origin
	.word	.Ltmp29                 # DW_AT_low_pc
	.word	.Ltmp37-.Ltmp29         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	125                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xd80:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc19           # DW_AT_location
	.word	2779                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xd89:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc18           # DW_AT_location
	.word	2790                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xd92:0x9 DW_TAG_variable
	.word	.Ldebug_loc17           # DW_AT_location
	.word	2801                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xd9c:0x2c DW_TAG_inlined_subroutine
	.word	2864                    # DW_AT_abstract_origin
	.word	.Ltmp40                 # DW_AT_low_pc
	.word	.Ltmp47-.Ltmp40         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	135                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xdac:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc23           # DW_AT_location
	.word	2876                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xdb5:0x9 DW_TAG_variable
	.word	.Ldebug_loc22           # DW_AT_location
	.word	2887                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xdbe:0x9 DW_TAG_variable
	.word	.Ldebug_loc24           # DW_AT_location
	.word	2898                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xdc9:0xcf DW_TAG_inlined_subroutine
	.word	2910                    # DW_AT_abstract_origin
	.word	.Ltmp48                 # DW_AT_low_pc
	.word	.Ltmp68-.Ltmp48         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	195                     # DW_AT_call_line
	.byte	17                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xdd9:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc25           # DW_AT_location
	.word	2922                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xde2:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc26           # DW_AT_location
	.word	2933                    # DW_AT_abstract_origin
	.byte	56                      # Abbrev [56] 0xdeb:0x5 DW_TAG_variable
	.word	2944                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xdf0:0x9 DW_TAG_variable
	.word	.Ldebug_loc34           # DW_AT_location
	.word	2955                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0xdf9:0x72 DW_TAG_inlined_subroutine
	.word	3006                    # DW_AT_abstract_origin
	.word	.Ltmp50                 # DW_AT_low_pc
	.word	.Ltmp54-.Ltmp50         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	146                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xe09:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc28           # DW_AT_location
	.word	3022                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xe12:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc27           # DW_AT_location
	.word	3033                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xe1b:0x9 DW_TAG_variable
	.word	.Ldebug_loc30           # DW_AT_location
	.word	3044                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0xe24:0x23 DW_TAG_inlined_subroutine
	.word	2967                    # DW_AT_abstract_origin
	.word	.Ltmp50                 # DW_AT_low_pc
	.word	.Ltmp51-.Ltmp50         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	242                     # DW_AT_call_line
	.byte	15                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xe34:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc29           # DW_AT_location
	.word	2983                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xe3d:0x9 DW_TAG_variable
	.word	.Ldebug_loc31           # DW_AT_location
	.word	2994                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xe47:0x23 DW_TAG_inlined_subroutine
	.word	3056                    # DW_AT_abstract_origin
	.word	.Ltmp52                 # DW_AT_low_pc
	.word	.Ltmp53-.Ltmp52         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	245                     # DW_AT_call_line
	.byte	19                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xe57:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc32           # DW_AT_location
	.word	3072                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xe60:0x9 DW_TAG_variable
	.word	.Ldebug_loc33           # DW_AT_location
	.word	3083                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xe6b:0x2c DW_TAG_inlined_subroutine
	.word	3095                    # DW_AT_abstract_origin
	.word	.Ltmp58                 # DW_AT_low_pc
	.word	.Ltmp68-.Ltmp58         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	159                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xe7b:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc35           # DW_AT_location
	.word	3107                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xe84:0x9 DW_TAG_variable
	.word	.Ldebug_loc36           # DW_AT_location
	.word	3118                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xe8d:0x9 DW_TAG_variable
	.word	.Ldebug_loc37           # DW_AT_location
	.word	3129                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xe98:0x8c DW_TAG_inlined_subroutine
	.word	3141                    # DW_AT_abstract_origin
	.word	.Ltmp69                 # DW_AT_low_pc
	.word	.Ltmp74-.Ltmp69         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	197                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xea8:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc38           # DW_AT_location
	.word	3153                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0xeb1:0x72 DW_TAG_inlined_subroutine
	.word	3006                    # DW_AT_abstract_origin
	.word	.Ltmp69                 # DW_AT_low_pc
	.word	.Ltmp73-.Ltmp69         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	166                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xec1:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc39           # DW_AT_location
	.word	3022                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0xeca:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc40           # DW_AT_location
	.word	3033                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xed3:0x9 DW_TAG_variable
	.word	.Ldebug_loc42           # DW_AT_location
	.word	3044                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0xedc:0x23 DW_TAG_inlined_subroutine
	.word	2967                    # DW_AT_abstract_origin
	.word	.Ltmp69                 # DW_AT_low_pc
	.word	.Ltmp70-.Ltmp69         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	242                     # DW_AT_call_line
	.byte	15                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xeec:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc41           # DW_AT_location
	.word	2983                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xef5:0x9 DW_TAG_variable
	.word	.Ldebug_loc43           # DW_AT_location
	.word	2994                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	55                      # Abbrev [55] 0xeff:0x23 DW_TAG_inlined_subroutine
	.word	3056                    # DW_AT_abstract_origin
	.word	.Ltmp71                 # DW_AT_low_pc
	.word	.Ltmp72-.Ltmp71         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	245                     # DW_AT_call_line
	.byte	19                      # DW_AT_call_column
	.byte	53                      # Abbrev [53] 0xf0f:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc44           # DW_AT_location
	.word	3072                    # DW_AT_abstract_origin
	.byte	54                      # Abbrev [54] 0xf18:0x9 DW_TAG_variable
	.word	.Ldebug_loc45           # DW_AT_location
	.word	3083                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0xf25:0xda DW_TAG_class_type
	.byte	5                       # DW_AT_calling_convention
	.word	.Linfo_string173        # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	13                      # DW_AT_decl_file
	.byte	6                       # DW_AT_decl_line
	.byte	57                      # Abbrev [57] 0xf2e:0xd DW_TAG_member
	.word	.Linfo_string157        # DW_AT_name
	.word	248                     # DW_AT_type
	.byte	13                      # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	57                      # Abbrev [57] 0xf3b:0xd DW_TAG_member
	.word	.Linfo_string158        # DW_AT_name
	.word	59                      # DW_AT_type
	.byte	13                      # DW_AT_decl_file
	.byte	41                      # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	21                      # Abbrev [21] 0xf48:0x18 DW_TAG_subprogram
	.word	.Linfo_string159        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	8                       # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xf50:0x5 DW_TAG_formal_parameter
	.word	4095                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0xf55:0x5 DW_TAG_formal_parameter
	.word	248                     # DW_AT_type
	.byte	18                      # Abbrev [18] 0xf5a:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	23                      # Abbrev [23] 0xf60:0x17 DW_TAG_subprogram
	.word	.Linfo_string160        # DW_AT_linkage_name
	.word	.Linfo_string161        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	13                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xf6c:0x5 DW_TAG_formal_parameter
	.word	4095                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0xf71:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	23                      # Abbrev [23] 0xf77:0x17 DW_TAG_subprogram
	.word	.Linfo_string162        # DW_AT_linkage_name
	.word	.Linfo_string163        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	18                      # DW_AT_decl_line
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xf83:0x5 DW_TAG_formal_parameter
	.word	4095                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0xf88:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0xf8e:0x1b DW_TAG_subprogram
	.word	.Linfo_string164        # DW_AT_linkage_name
	.word	.Linfo_string165        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.word	2194                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xf9e:0x5 DW_TAG_formal_parameter
	.word	4095                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0xfa3:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0xfa9:0x1b DW_TAG_subprogram
	.word	.Linfo_string166        # DW_AT_linkage_name
	.word	.Linfo_string167        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xfb9:0x5 DW_TAG_formal_parameter
	.word	4100                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0xfbe:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0xfc4:0x1b DW_TAG_subprogram
	.word	.Linfo_string168        # DW_AT_linkage_name
	.word	.Linfo_string169        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xfd4:0x5 DW_TAG_formal_parameter
	.word	4100                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	18                      # Abbrev [18] 0xfd9:0x5 DW_TAG_formal_parameter
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	22                      # Abbrev [22] 0xfdf:0x16 DW_TAG_subprogram
	.word	.Linfo_string170        # DW_AT_linkage_name
	.word	.Linfo_string171        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
	.word	2194                    # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	1                       # DW_AT_accessibility
                                        # DW_ACCESS_public
	.byte	17                      # Abbrev [17] 0xfef:0x5 DW_TAG_formal_parameter
	.word	4100                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	0                       # End Of Children Mark
	.byte	58                      # Abbrev [58] 0xff5:0x9 DW_TAG_template_type_parameter
	.word	59                      # DW_AT_type
	.word	.Linfo_string172        # DW_AT_name
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0xfff:0x5 DW_TAG_pointer_type
	.word	3877                    # DW_AT_type
	.byte	3                       # Abbrev [3] 0x1004:0x5 DW_TAG_pointer_type
	.word	4105                    # DW_AT_type
	.byte	34                      # Abbrev [34] 0x1009:0x5 DW_TAG_const_type
	.word	3877                    # DW_AT_type
	.byte	59                      # Abbrev [59] 0x100e:0x35 DW_TAG_subprogram
	.word	3959                    # DW_AT_specification
	.byte	1                       # DW_AT_inline
	.word	4120                    # DW_AT_object_pointer
	.byte	60                      # Abbrev [60] 0x1018:0x9 DW_TAG_formal_parameter
	.word	.Linfo_string174        # DW_AT_name
	.word	4163                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	46                      # Abbrev [46] 0x1021:0xb DW_TAG_formal_parameter
	.word	.Linfo_string127        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	18                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	47                      # Abbrev [47] 0x102c:0xb DW_TAG_variable
	.word	.Linfo_string149        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	19                      # DW_AT_decl_line
	.word	248                     # DW_AT_type
	.byte	47                      # Abbrev [47] 0x1037:0xb DW_TAG_variable
	.word	.Linfo_string175        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	20                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x1043:0x5 DW_TAG_pointer_type
	.word	3877                    # DW_AT_type
	.byte	59                      # Abbrev [59] 0x1048:0x1f DW_TAG_subprogram
	.word	4009                    # DW_AT_specification
	.byte	1                       # DW_AT_inline
	.word	4178                    # DW_AT_object_pointer
	.byte	60                      # Abbrev [60] 0x1052:0x9 DW_TAG_formal_parameter
	.word	.Linfo_string174        # DW_AT_name
	.word	4199                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	46                      # Abbrev [46] 0x105b:0xb DW_TAG_formal_parameter
	.word	.Linfo_string127        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x1067:0x5 DW_TAG_pointer_type
	.word	4105                    # DW_AT_type
	.byte	59                      # Abbrev [59] 0x106c:0x1f DW_TAG_subprogram
	.word	3982                    # DW_AT_specification
	.byte	1                       # DW_AT_inline
	.word	4214                    # DW_AT_object_pointer
	.byte	60                      # Abbrev [60] 0x1076:0x9 DW_TAG_formal_parameter
	.word	.Linfo_string174        # DW_AT_name
	.word	4163                    # DW_AT_type
                                        # DW_AT_artificial
	.byte	46                      # Abbrev [46] 0x107f:0xb DW_TAG_formal_parameter
	.word	.Linfo_string127        # DW_AT_name
	.byte	13                      # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	61                      # Abbrev [61] 0x108b:0x205 DW_TAG_subprogram
	.word	.Lfunc_begin1           # DW_AT_low_pc
	.word	.Lfunc_end1-.Lfunc_begin1 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string178        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
                                        # DW_AT_external
	.byte	50                      # Abbrev [50] 0x10a0:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc46           # DW_AT_location
	.word	.Linfo_string179        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	23                      # DW_AT_decl_line
	.word	4752                    # DW_AT_type
	.byte	50                      # Abbrev [50] 0x10af:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc47           # DW_AT_location
	.word	.Linfo_string186        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	24                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	50                      # Abbrev [50] 0x10be:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc48           # DW_AT_location
	.word	.Linfo_string187        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	25                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	62                      # Abbrev [62] 0x10cd:0xd DW_TAG_formal_parameter
	.byte	1                       # DW_AT_location
	.byte	93
	.word	.Linfo_string188        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	26                      # DW_AT_decl_line
	.word	4827                    # DW_AT_type
	.byte	62                      # Abbrev [62] 0x10da:0xd DW_TAG_formal_parameter
	.byte	1                       # DW_AT_location
	.byte	94
	.word	.Linfo_string189        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	27                      # DW_AT_decl_line
	.word	248                     # DW_AT_type
	.byte	62                      # Abbrev [62] 0x10e7:0xd DW_TAG_formal_parameter
	.byte	1                       # DW_AT_location
	.byte	95
	.word	.Linfo_string190        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	28                      # DW_AT_decl_line
	.word	248                     # DW_AT_type
	.byte	51                      # Abbrev [51] 0x10f4:0xf DW_TAG_variable
	.word	.Ldebug_loc49           # DW_AT_location
	.word	.Linfo_string191        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.word	4757                    # DW_AT_type
	.byte	51                      # Abbrev [51] 0x1103:0xf DW_TAG_variable
	.word	.Ldebug_loc50           # DW_AT_location
	.word	.Linfo_string192        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.word	3877                    # DW_AT_type
	.byte	63                      # Abbrev [63] 0x1112:0x2e DW_TAG_lexical_block
	.word	.Ltmp85                 # DW_AT_low_pc
	.word	.Ltmp89-.Ltmp85         # DW_AT_high_pc
	.byte	51                      # Abbrev [51] 0x111b:0xf DW_TAG_variable
	.word	.Ldebug_loc51           # DW_AT_location
	.word	.Linfo_string193        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	63                      # Abbrev [63] 0x112a:0x15 DW_TAG_lexical_block
	.word	.Ltmp88                 # DW_AT_low_pc
	.word	.Ltmp89-.Ltmp88         # DW_AT_high_pc
	.byte	47                      # Abbrev [47] 0x1133:0xb DW_TAG_variable
	.word	.Linfo_string149        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.word	38                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	64                      # Abbrev [64] 0x1140:0x125 DW_TAG_lexical_block
	.word	.Ldebug_ranges5         # DW_AT_ranges
	.byte	51                      # Abbrev [51] 0x1145:0xf DW_TAG_variable
	.word	.Ldebug_loc52           # DW_AT_location
	.word	.Linfo_string194        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	64                      # DW_AT_decl_line
	.word	2122                    # DW_AT_type
	.byte	51                      # Abbrev [51] 0x1154:0xf DW_TAG_variable
	.word	.Ldebug_loc53           # DW_AT_location
	.word	.Linfo_string195        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	51                      # Abbrev [51] 0x1163:0xf DW_TAG_variable
	.word	.Ldebug_loc56           # DW_AT_location
	.word	.Linfo_string196        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.word	2122                    # DW_AT_type
	.byte	51                      # Abbrev [51] 0x1172:0xf DW_TAG_variable
	.word	.Ldebug_loc60           # DW_AT_location
	.word	.Linfo_string198        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	51                      # Abbrev [51] 0x1181:0xf DW_TAG_variable
	.word	.Ldebug_loc61           # DW_AT_location
	.word	.Linfo_string199        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	52                      # Abbrev [52] 0x1190:0x44 DW_TAG_inlined_subroutine
	.word	4110                    # DW_AT_abstract_origin
	.word	.Ldebug_ranges2         # DW_AT_ranges
	.byte	12                      # DW_AT_call_file
	.byte	80                      # DW_AT_call_line
	.byte	19                      # DW_AT_call_column
	.byte	65                      # Abbrev [65] 0x119c:0x5 DW_TAG_formal_parameter
	.word	4120                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0x11a1:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc54           # DW_AT_location
	.word	4129                    # DW_AT_abstract_origin
	.byte	56                      # Abbrev [56] 0x11aa:0x5 DW_TAG_variable
	.word	4140                    # DW_AT_abstract_origin
	.byte	56                      # Abbrev [56] 0x11af:0x5 DW_TAG_variable
	.word	4151                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0x11b4:0x1f DW_TAG_inlined_subroutine
	.word	4168                    # DW_AT_abstract_origin
	.word	.Ltmp93                 # DW_AT_low_pc
	.word	.Ltmp94-.Ltmp93         # DW_AT_high_pc
	.byte	13                      # DW_AT_call_file
	.byte	21                      # DW_AT_call_line
	.byte	15                      # DW_AT_call_column
	.byte	65                      # Abbrev [65] 0x11c4:0x5 DW_TAG_formal_parameter
	.word	4178                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0x11c9:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc55           # DW_AT_location
	.word	4187                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	63                      # Abbrev [63] 0x11d4:0x57 DW_TAG_lexical_block
	.word	.Ltmp101                # DW_AT_low_pc
	.word	.Ltmp108-.Ltmp101       # DW_AT_high_pc
	.byte	51                      # Abbrev [51] 0x11dd:0xf DW_TAG_variable
	.word	.Ldebug_loc57           # DW_AT_location
	.word	.Linfo_string197        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	55                      # Abbrev [55] 0x11ec:0x3e DW_TAG_inlined_subroutine
	.word	4204                    # DW_AT_abstract_origin
	.word	.Ltmp103                # DW_AT_low_pc
	.word	.Ltmp107-.Ltmp103       # DW_AT_high_pc
	.byte	12                      # DW_AT_call_file
	.byte	50                      # DW_AT_call_line
	.byte	27                      # DW_AT_call_column
	.byte	65                      # Abbrev [65] 0x11fc:0x5 DW_TAG_formal_parameter
	.word	4214                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0x1201:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc58           # DW_AT_location
	.word	4223                    # DW_AT_abstract_origin
	.byte	55                      # Abbrev [55] 0x120a:0x1f DW_TAG_inlined_subroutine
	.word	4168                    # DW_AT_abstract_origin
	.word	.Ltmp104                # DW_AT_low_pc
	.word	.Ltmp105-.Ltmp104       # DW_AT_high_pc
	.byte	13                      # DW_AT_call_file
	.byte	27                      # DW_AT_call_line
	.byte	22                      # DW_AT_call_column
	.byte	65                      # Abbrev [65] 0x121a:0x5 DW_TAG_formal_parameter
	.word	4178                    # DW_AT_abstract_origin
	.byte	53                      # Abbrev [53] 0x121f:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc59           # DW_AT_location
	.word	4187                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	64                      # Abbrev [64] 0x122b:0x39 DW_TAG_lexical_block
	.word	.Ldebug_ranges4         # DW_AT_ranges
	.byte	51                      # Abbrev [51] 0x1230:0xf DW_TAG_variable
	.word	.Ldebug_loc62           # DW_AT_location
	.word	.Linfo_string200        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	68                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	64                      # Abbrev [64] 0x123f:0x24 DW_TAG_lexical_block
	.word	.Ldebug_ranges3         # DW_AT_ranges
	.byte	51                      # Abbrev [51] 0x1244:0xf DW_TAG_variable
	.word	.Ldebug_loc63           # DW_AT_location
	.word	.Linfo_string201        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	51                      # Abbrev [51] 0x1253:0xf DW_TAG_variable
	.word	.Ldebug_loc64           # DW_AT_location
	.word	.Linfo_string202        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.word	2122                    # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	64                      # Abbrev [64] 0x1265:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges6         # DW_AT_ranges
	.byte	51                      # Abbrev [51] 0x126a:0xf DW_TAG_variable
	.word	.Ldebug_loc65           # DW_AT_location
	.word	.Linfo_string193        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
	.word	59                      # DW_AT_type
	.byte	63                      # Abbrev [63] 0x1279:0x15 DW_TAG_lexical_block
	.word	.Ltmp150                # DW_AT_low_pc
	.word	.Ltmp151-.Ltmp150       # DW_AT_high_pc
	.byte	47                      # Abbrev [47] 0x1282:0xb DW_TAG_variable
	.word	.Linfo_string149        # DW_AT_name
	.byte	12                      # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
	.word	38                      # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x1290:0x5 DW_TAG_pointer_type
	.word	4757                    # DW_AT_type
	.byte	6                       # Abbrev [6] 0x1295:0x46 DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.word	.Linfo_string185        # DW_AT_name
	.byte	20                      # DW_AT_byte_size
	.byte	14                      # DW_AT_decl_file
	.byte	3                       # DW_AT_decl_line
	.byte	7                       # Abbrev [7] 0x129e:0xc DW_TAG_member
	.word	.Linfo_string180        # DW_AT_name
	.word	59                      # DW_AT_type
	.byte	14                      # DW_AT_decl_file
	.byte	4                       # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x12aa:0xc DW_TAG_member
	.word	.Linfo_string181        # DW_AT_name
	.word	59                      # DW_AT_type
	.byte	14                      # DW_AT_decl_file
	.byte	5                       # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x12b6:0xc DW_TAG_member
	.word	.Linfo_string182        # DW_AT_name
	.word	248                     # DW_AT_type
	.byte	14                      # DW_AT_decl_file
	.byte	6                       # DW_AT_decl_line
	.byte	8                       # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x12c2:0xc DW_TAG_member
	.word	.Linfo_string183        # DW_AT_name
	.word	248                     # DW_AT_type
	.byte	14                      # DW_AT_decl_file
	.byte	7                       # DW_AT_decl_line
	.byte	12                      # DW_AT_data_member_location
	.byte	7                       # Abbrev [7] 0x12ce:0xc DW_TAG_member
	.word	.Linfo_string184        # DW_AT_name
	.word	4827                    # DW_AT_type
	.byte	14                      # DW_AT_decl_file
	.byte	8                       # DW_AT_decl_line
	.byte	16                      # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x12db:0x5 DW_TAG_pointer_type
	.word	2122                    # DW_AT_type
	.byte	0                       # End Of Children Mark
.Ldebug_info_end0:
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.word	.Ltmp2-.Lfunc_begin0
	.word	.Ltmp3-.Lfunc_begin0
	.word	.Ltmp4-.Lfunc_begin0
	.word	.Ltmp5-.Lfunc_begin0
	.word	.Ltmp6-.Lfunc_begin0
	.word	.Ltmp9-.Lfunc_begin0
	.word	0
	.word	0
.Ldebug_ranges1:
	.word	.Ltmp28-.Lfunc_begin0
	.word	.Ltmp39-.Lfunc_begin0
	.word	.Ltmp40-.Lfunc_begin0
	.word	.Ltmp47-.Lfunc_begin0
	.word	0
	.word	0
.Ldebug_ranges2:
	.word	.Ltmp92-.Lfunc_begin0
	.word	.Ltmp97-.Lfunc_begin0
	.word	.Ltmp131-.Lfunc_begin0
	.word	.Ltmp133-.Lfunc_begin0
	.word	0
	.word	0
.Ldebug_ranges3:
	.word	.Ltmp121-.Lfunc_begin0
	.word	.Ltmp129-.Lfunc_begin0
	.word	.Ltmp140-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.word	0
	.word	0
.Ldebug_ranges4:
	.word	.Ltmp116-.Lfunc_begin0
	.word	.Ltmp129-.Lfunc_begin0
	.word	.Ltmp137-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.word	0
	.word	0
.Ldebug_ranges5:
	.word	.Ltmp91-.Lfunc_begin0
	.word	.Ltmp97-.Lfunc_begin0
	.word	.Ltmp101-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.word	0
	.word	0
.Ldebug_ranges6:
	.word	.Ltmp147-.Lfunc_begin0
	.word	.Ltmp149-.Lfunc_begin0
	.word	.Ltmp150-.Lfunc_begin0
	.word	.Ltmp151-.Lfunc_begin0
	.word	0
	.word	0
	.ident	"clang version 10.0.0 (https://github.com/bespoke-silicon-group/llvm-project.git 26ed0b46f4c6c06a4ff742ef99e810b737b1d8a2)"
	.section	".note.GNU-stack","",@progbits
	.section	.debug_line,"",@progbits
.Lline_table_start0:
