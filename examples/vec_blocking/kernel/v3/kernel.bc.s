	.text
	.file	"kernel.cpp"
	.file	1 "/mnt/users/spin0/no_backup/eafurst/bsg_bladerunner/llvm-baseline/examples/vec_blocking/kernel/include/vector_add.hpp"
	.file	2 "/mnt/users/spin0/no_backup/eafurst/bsg_bladerunner/bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h"
	.file	3 "/mnt/users/spin0/no_backup/eafurst/bsg_bladerunner/llvm-baseline/examples/vec_blocking/kernel/v3/kernel.cpp"
	.file	4 "/mnt/users/spin0/no_backup/eafurst/bsg_bladerunner/bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h"
	.globl	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_ # -- Begin function _Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
	.p2align	2
	.type	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_,@function
_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_: # @_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
.Lfunc_begin0:
	.loc	2 172 0                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:172:0
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
	.cfi_offset ra, -4
	.cfi_offset s0, -8
	.cfi_offset s1, -12
	.cfi_offset s2, -16
	.cfi_offset s3, -20
	mv	s0, a0
.Ltmp0:
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 173 39 prologue_end   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:173:39
	lbu	a2, 0(a0)
	.loc	2 173 64 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:173:64
	lbu	a0, 1(a0)
	mv	s3, a1
.Ltmp1:
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	.loc	2 92 66 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:92:66
	lui	a6, %hi(__bsg_y)
	lw	a3, %lo(__bsg_y)(a6)
.Ltmp2:
	.loc	2 173 53                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:173:53
	add	a0, a0, a2
	.loc	2 173 76 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:173:76
	srli	s2, a0, 1
.Ltmp3:
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	.loc	2 175 39 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:39
	lbu	a4, 0(a1)
.Ltmp4:
	.loc	2 92 66                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:92:66
	slli	a3, a3, 24
	slli	a7, s2, 18
	.loc	2 96 39                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:96:39
	lui	s1, %hi(__bsg_x)
	lw	a5, %lo(__bsg_x)(s1)
	.loc	2 92 66                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:92:66
	or	a1, a7, s0
	or	a1, a1, a3
.Ltmp5:
	.loc	2 175 64                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:64
	lbu	a0, 1(s3)
.Ltmp6:
	.loc	2 96 45                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:96:45
	sub	a2, a5, a2
	lui	a5, 131072
	.loc	2 92 66                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:92:66
	or	a1, a1, a5
.Ltmp7:
	#DEBUG_VALUE: bsg_row_barrier_sync:p_remote_barrier <- $x11
	.loc	2 96 9                  # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:96:9
	add	a1, a1, a2
.Ltmp8:
	.loc	2 0 9 is_stmt 0         # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:9
	addi	a2, zero, 1
	.loc	2 96 72                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:96:72
	sb	a2, 2(a1)
.Ltmp9:
	.loc	2 186 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:186:13
	lw	a3, %lo(__bsg_x)(s1)
.Ltmp10:
	.loc	2 175 53                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:53
	add	a0, a0, a4
	.loc	2 175 76 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:175:76
	srli	a2, a0, 1
.Ltmp11:
	#DEBUG_VALUE: bsg_row_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_row_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	.loc	2 186 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:186:13
	bne	a3, s2, .LBB0_6
.Ltmp12:
# %bb.1:                                # %if.then
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x12
	.loc	2 106 33                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:106:33
	lbu	a0, 1(s0)
	.loc	2 106 56 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:106:56
	lbu	a1, 0(s0)
	.loc	2 103 66 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:103:66
	slli	a3, a2, 24
	or	a4, a7, s3
	or	a3, a4, a3
	.loc	2 106 45                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:106:45
	sub	a4, a0, a1
.Ltmp13:
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x14
	.loc	2 103 66                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:103:66
	or	a3, a3, a5
.Ltmp14:
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x13
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: poll_range:range <- $x14
	.loc	2 208 17                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:208:17
	bltz	a4, .LBB0_5
.Ltmp15:
# %bb.2:                                # %for.body.i.i.preheader
	#DEBUG_VALUE: poll_range:range <- $x14
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x14
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 17 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:17
	mv	a5, zero
.Ltmp16:
.LBB0_3:                                # %for.body.i.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: poll_range:range <- $x14
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x14
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	mv	s1, a5
.Ltmp17:
	#DEBUG_VALUE: poll_range:i <- $x9
	.loc	2 209 30 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:209:30
	add	a0, s0, a5
	lbu	a0, 2(a0)
.Ltmp18:
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x9
	.loc	2 0 30 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:30
	mv	a5, zero
.Ltmp19:
	.loc	2 209 30                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:209:30
	beqz	a0, .LBB0_3
.Ltmp20:
# %bb.4:                                # %for.cond.i.i
                                        #   in Loop: Header=BB0_3 Depth=1
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x9
	#DEBUG_VALUE: poll_range:range <- $x14
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x14
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 208 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:208:41
	addi	a5, s1, 1
.Ltmp21:
	#DEBUG_VALUE: poll_range:i <- $x15
	.loc	2 208 17 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:208:17
	bne	s1, a4, .LBB0_3
.Ltmp22:
.LBB0_5:                                # %_Z20bsg_col_barrier_syncP17_bsg_row_barrier_P17_bsg_col_barrier_ii.exit
	#DEBUG_VALUE: bsg_col_barrier_sync:p_remote_barrier <- $x13
	#DEBUG_VALUE: bsg_col_barrier_sync:x_range <- $x14
	#DEBUG_VALUE: bsg_col_barrier_sync:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_col_barrier_sync:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_col_barrier_sync:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_sync:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 109 39 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:109:39
	lui	a0, %hi(__bsg_y)
	lw	a0, %lo(__bsg_y)(a0)
	.loc	2 109 57 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:109:57
	lbu	a1, 0(s3)
	.loc	2 109 45                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:109:45
	sub	a0, a0, a1
	.loc	2 109 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:109:9
	add	a0, a3, a0
	addi	a1, zero, 1
	.loc	2 109 72                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:109:72
	sb	a1, 2(a0)
.Ltmp23:
	.loc	2 189 13 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:189:13
	lui	a0, %hi(__bsg_x)
	lw	a3, %lo(__bsg_x)(a0)
.Ltmp24:
.LBB0_6:                                # %if.end
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 189 36 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:189:36
	bne	a3, s2, .LBB0_17
.Ltmp25:
# %bb.7:                                # %if.end
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 0                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	lw	a0, %lo(__bsg_y)(a6)
	.loc	2 189 36                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:189:36
	bne	a0, a2, .LBB0_17
.Ltmp26:
# %bb.8:                                # %if.then8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_y_cord <- $x12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	.loc	2 122 33 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:122:33
	lbu	a2, 1(s3)
.Ltmp27:
	.loc	2 122 56 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:122:56
	lbu	a3, 0(s3)
	.loc	2 122 45                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:122:45
	sub	a1, a2, a3
.Ltmp28:
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x19
	#DEBUG_VALUE: poll_range:range <- $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	.loc	2 208 17 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:208:17
	bltz	a1, .LBB0_12
.Ltmp29:
# %bb.9:                                # %for.body.i.i49.preheader
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: poll_range:range <- $x11
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x19
	#DEBUG_VALUE: poll_range:i <- 0
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 0 17 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:17
	mv	a5, zero
.Ltmp30:
.LBB0_10:                               # %for.body.i.i49
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: poll_range:range <- $x11
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x19
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	mv	a4, a5
.Ltmp31:
	#DEBUG_VALUE: poll_range:i <- $x14
	.loc	2 209 30 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:209:30
	add	a0, s3, a5
	lbu	a0, 2(a0)
.Ltmp32:
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x14
	.loc	2 0 30 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:30
	mv	a5, zero
.Ltmp33:
	.loc	2 209 30                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:209:30
	beqz	a0, .LBB0_10
.Ltmp34:
# %bb.11:                               # %for.cond.i.i45
                                        #   in Loop: Header=BB0_10 Depth=1
	#DEBUG_VALUE: poll_range:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] $x14
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: poll_range:range <- $x11
	#DEBUG_VALUE: poll_range:p <- [DW_OP_plus_uconst 2, DW_OP_stack_value] $x19
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 208 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:208:41
	addi	a5, a4, 1
.Ltmp35:
	#DEBUG_VALUE: poll_range:i <- $x15
	.loc	2 208 17 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:208:17
	bne	a4, a1, .LBB0_10
.Ltmp36:
.LBB0_12:                               # %_Z10poll_rangeiPh.exit.i
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_col:p_col_b <- $x19
	#DEBUG_VALUE: alert_col:i <- $x13
	.loc	2 217 9 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:217:9
	bltu	a2, a3, .LBB0_15
.Ltmp37:
# %bb.13:                               # %for.body.lr.ph.i12.i
	#DEBUG_VALUE: alert_col:i <- $x13
	#DEBUG_VALUE: alert_col:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_col:i <- $x13
	.loc	2 0 0 is_stmt 0         # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	or	a0, a7, s3
.Ltmp38:
	.loc	2 217 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:217:9
	addi	a4, a3, -1
	slli	a3, a3, 24
.Ltmp39:
	.loc	2 0 9                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:9
	lui	a6, 131072
	addi	a7, zero, 1
	lui	a5, 4096
.Ltmp40:
.LBB0_14:                               # %for.body.i14.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: alert_col:p_col_b <- $x19
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_col:i <- undef
	.loc	2 218 55 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:218:55
	or	s1, a0, a3
	or	s1, s1, a6
.Ltmp41:
	#DEBUG_VALUE: alert_col:p_remote_barrier <- $x9
	.loc	2 221 47                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:221:47
	sw	a7, 4(s1)
.Ltmp42:
	#DEBUG_VALUE: alert_col:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	2 217 44                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:217:44
	addi	a4, a4, 1
	add	a3, a3, a5
.Ltmp43:
	.loc	2 217 9 is_stmt 0       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:217:9
	bltu	a4, a2, .LBB0_14
.Ltmp44:
.LBB0_15:                               # %_Z9alert_colP17_bsg_col_barrier_.exit.i
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_col_barrier_alert:i <- 0
	.loc	2 131 9 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:131:9
	bltz	a1, .LBB0_18
.Ltmp45:
# %bb.16:                               # %for.body.preheader.i
	#DEBUG_VALUE: bsg_col_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_col_barrier_alert:y_range <- $x11
	#DEBUG_VALUE: bsg_col_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	addi	a2, a1, 1
	addi	a0, s3, 2
.Ltmp46:
	.loc	2 132 40                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:132:40
	mv	a1, zero
.Ltmp47:
	call	memset
.Ltmp48:
	#DEBUG_VALUE: bsg_col_barrier_alert:i <- undef
	.loc	2 192 13                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:192:13
	lui	a0, %hi(__bsg_x)
	lw	a3, %lo(__bsg_x)(a0)
.Ltmp49:
.LBB0_17:                               # %if.end9
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 192 13 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:192:13
	bne	a3, s2, .LBB0_27
.Ltmp50:
.LBB0_18:                               # %if.then11
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	.loc	2 142 33 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:142:33
	lbu	a6, 1(s0)
	.loc	2 142 56 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:142:56
	lbu	a7, 0(s0)
.Ltmp51:
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:x_range <- undef
	.loc	2 0 56                  # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:56
	addi	a0, s3, 4
	addi	a1, zero, 1
.Ltmp52:
.LBB0_19:                               # %while.cond.i.i57
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x19
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x19
	.loc	4 111 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:111:41
	#APP
	lr.w    a2,0(a0)

	#NO_APP
.Ltmp53:
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	#DEBUG_VALUE: bsg_lr:tmp <- $x12
	.loc	2 241 13                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:241:13
	beq	a2, a1, .LBB0_21
.Ltmp54:
# %bb.20:                               # %if.else.i.i59
                                        #   in Loop: Header=BB0_19 Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x19
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr_aq:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x19
	.loc	4 112 41                # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:112:41
	#APP
	lr.w.aq a2,0(a0)

	#NO_APP
.Ltmp55:
	#DEBUG_VALUE: bsg_lr_aq:tmp <- $x12
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	.loc	2 244 17                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:244:17
	bne	a2, a1, .LBB0_19
.Ltmp56:
.LBB0_21:                               # %_Z18bsg_wait_local_intPii.exit.i
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_row:p_row_b <- $x8
	.loc	2 228 27                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:228:27
	lbu	a0, 0(s0)
.Ltmp57:
	#DEBUG_VALUE: alert_row:i <- $x10
	.loc	2 228 57 is_stmt 0      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:228:57
	lbu	a2, 1(s0)
.Ltmp58:
	.loc	2 228 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:228:9
	bltu	a2, a0, .LBB0_24
.Ltmp59:
# %bb.22:                               # %for.body.lr.ph.i.i63
	#DEBUG_VALUE: alert_row:i <- $x10
	#DEBUG_VALUE: alert_row:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_row:i <- $x10
	.loc	2 0 0                   # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:0
	lui	a1, %hi(__bsg_y)
	lw	a1, %lo(__bsg_y)(a1)
	slli	a1, a1, 24
	or	a3, a1, s0
.Ltmp60:
	.loc	2 228 9                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:228:9
	addi	a4, a0, -1
	slli	a5, a0, 18
	lui	t0, 131072
	addi	a1, zero, 1
	lui	s1, 64
.Ltmp61:
.LBB0_23:                               # %for.body.i.i70
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: alert_row:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: alert_row:i <- undef
	.loc	2 229 55 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:229:55
	or	a0, a3, a5
	or	a0, a0, t0
.Ltmp62:
	#DEBUG_VALUE: alert_row:p_remote_barrier <- $x10
	.loc	2 232 47                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:232:47
	sw	a1, 4(a0)
.Ltmp63:
	#DEBUG_VALUE: alert_row:i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	2 228 44                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:228:44
	addi	a4, a4, 1
	add	a5, a5, s1
.Ltmp64:
	.loc	2 228 9 is_stmt 0       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:228:9
	bltu	a4, a2, .LBB0_23
.Ltmp65:
.LBB0_24:                               # %_Z9alert_rowP17_bsg_row_barrier_.exit.i
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	.loc	2 153 9 is_stmt 1       # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:153:9
	bltu	a6, a7, .LBB0_26
.Ltmp66:
# %bb.25:                               # %for.body.preheader.i72
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	sub	a0, a6, a7
	addi	a2, a0, 1
	addi	a0, s0, 2
.Ltmp67:
	.loc	2 154 40                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:154:40
	mv	a1, zero
	call	memset
.Ltmp68:
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- undef
.LBB0_26:                               # %_Z21bsg_row_barrier_alertP17_bsg_row_barrier_P17_bsg_col_barrier_.exit
	#DEBUG_VALUE: bsg_row_barrier_alert:i <- 0
	#DEBUG_VALUE: bsg_row_barrier_alert:p_col_b <- $x19
	#DEBUG_VALUE: bsg_row_barrier_alert:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 157 33                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:157:33
	sw	zero, 4(s3)
.Ltmp69:
.LBB0_27:                               # %if.end12
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	.loc	2 0 33 is_stmt 0        # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:0:33
	addi	a0, s0, 4
	addi	a1, zero, 1
.Ltmp70:
.LBB0_28:                               # %while.cond.i.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	.loc	4 111 41 is_stmt 1      # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:111:41
	#APP
	lr.w    a2,0(a0)

	#NO_APP
.Ltmp71:
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	#DEBUG_VALUE: bsg_lr:tmp <- $x12
	.loc	2 241 13                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:241:13
	beq	a2, a1, .LBB0_30
.Ltmp72:
# %bb.29:                               # %if.else.i.i
                                        #   in Loop: Header=BB0_28 Depth=1
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	#DEBUG_VALUE: bsg_wait_local_int:cond <- 1
	#DEBUG_VALUE: bsg_wait_local_int:ptr <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	#DEBUG_VALUE: bsg_lr_aq:p <- [DW_OP_plus_uconst 4, DW_OP_stack_value] $x8
	.loc	4 112 41                # bsg_manycore/software/bsg_manycore_lib/bsg_manycore.h:112:41
	#APP
	lr.w.aq a2,0(a0)

	#NO_APP
.Ltmp73:
	#DEBUG_VALUE: bsg_lr_aq:tmp <- $x12
	#DEBUG_VALUE: bsg_wait_local_int:tmp <- $x12
	.loc	2 244 17                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:244:17
	bne	a2, a1, .LBB0_28
.Ltmp74:
.LBB0_30:                               # %_Z13bsg_tile_waitP17_bsg_row_barrier_.exit
	#DEBUG_VALUE: bsg_tile_wait:p_row_b <- $x8
	#DEBUG_VALUE: bsg_tile_group_barrier:center_x_cord <- $x18
	#DEBUG_VALUE: bsg_tile_group_barrier:p_col_b <- $x19
	#DEBUG_VALUE: bsg_tile_group_barrier:p_row_b <- $x8
	.loc	2 166 31                # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:166:31
	sw	zero, 4(s0)
.Ltmp75:
	.loc	2 201 1                 # bsg_manycore/software/bsg_manycore_lib/bsg_tile_group_barrier.h:201:1
	lw	s3, 12(sp)
.Ltmp76:
	lw	s2, 16(sp)
.Ltmp77:
	lw	s1, 20(sp)
	lw	s0, 24(sp)
.Ltmp78:
	lw	ra, 28(sp)
	addi	sp, sp, 32
	ret
.Ltmp79:
.Lfunc_end0:
	.size	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_, .Lfunc_end0-_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
	.cfi_endproc
                                        # -- End function
	.globl	kernel_vector_add_int   # -- Begin function kernel_vector_add_int
	.p2align	2
	.type	kernel_vector_add_int,@function
kernel_vector_add_int:                  # @kernel_vector_add_int
.Lfunc_begin1:
	.loc	3 33 0                  # kernel/v3/kernel.cpp:33:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_int:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_int:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_int:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_int:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_int:block_size_y <- $x14
	#DEBUG_VALUE: kernel_vector_add_int:block_size_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_int:tag <- $x16
	#DEBUG_VALUE: kernel_vector_add_int:iter <- $x17
	addi	sp, sp, -64
	.cfi_def_cfa_offset 64
.Ltmp80:
	.loc	3 34 17 prologue_end    # kernel/v3/kernel.cpp:34:17
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
	lui	t2, %hi(__bsg_grp_org_y)
	lw	a4, %lo(__bsg_grp_org_y)(t2)
.Ltmp81:
	lui	t3, %hi(__bsg_y)
	lw	s0, %lo(__bsg_y)(t3)
	lui	s1, 64
	addi	s1, s1, -16
	add	t0, s0, a4
	lui	a4, %hi(__bsg_grp_org_x)
	lw	t1, %lo(__bsg_grp_org_x)(a4)
	lui	a4, %hi(__bsg_x)
	lw	t4, %lo(__bsg_x)(a4)
	slli	s0, t0, 24
	lui	a4, 258048
	and	t0, s0, a4
	add	a4, t4, t1
	lui	s0, %hi(__bsg_tile_group_id)
	lw	t1, %lo(__bsg_tile_group_id)(s0)
	slli	a4, a4, 18
	lui	s0, 4032
	and	a4, a4, s0
	slli	s0, t1, 4
	and	s0, s0, s1
	or	a4, t0, a4
	or	a4, a4, s0
	lui	s0, 524288
	or	a4, a4, s0
.Ltmp82:
	#DEBUG_VALUE: val <- $x14
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	s0, 266241
.Ltmp83:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 34 17                 # kernel/v3/kernel.cpp:34:17
	sw	a4, -756(s0)
.Ltmp84:
	#DEBUG_VALUE: kernel_vector_add_int:rc <- undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	t0, %lo(__bsg_grp_org_y)(t2)
	lw	a4, %lo(__bsg_y)(t3)
.Ltmp85:
	#DEBUG_VALUE: kernel_vector_add_int:iter <- $x17
	#DEBUG_VALUE: kernel_vector_add_int:tag <- $x16
	sw	a5, 8(sp)
.Ltmp86:
	#DEBUG_VALUE: kernel_vector_add_int:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	sw	a3, 4(sp)
.Ltmp87:
	#DEBUG_VALUE: kernel_vector_add_int:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	sw	a2, 0(sp)
.Ltmp88:
	#DEBUG_VALUE: kernel_vector_add_int:C <- [$x2+0]
	mv	s5, a1
.Ltmp89:
	#DEBUG_VALUE: kernel_vector_add_int:B <- $x21
	mv	s10, a0
.Ltmp90:
	#DEBUG_VALUE: kernel_vector_add_int:A <- $x26
	add	a0, a4, t0
	slli	a1, a0, 24
.Ltmp91:
	#DEBUG_VALUE: i <- 0
	andi	s8, a6, 15
.Ltmp92:
	.loc	3 36 17 is_stmt 1       # kernel/v3/kernel.cpp:36:17
	addi	s9, a7, 1
.Ltmp93:
	.loc	3 34 17                 # kernel/v3/kernel.cpp:34:17
	lui	s11, %hi(__bsg_grp_org_x)
	lui	s6, %hi(__bsg_x)
	lui	s7, 258048
	lui	s2, %hi(__bsg_tile_group_id)
	lui	s3, 4032
	lui	s4, 266241
	lui	s0, %hi(__bsg_y)
.Ltmp94:
.LBB1_1:                                # %do.body11
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: i <- 0
	#DEBUG_VALUE: kernel_vector_add_int:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_int:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_int:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: i <- undef
	.loc	3 37 25                 # kernel/v3/kernel.cpp:37:25
	lw	a0, %lo(__bsg_grp_org_x)(s11)
	lw	a2, %lo(__bsg_x)(s6)
	and	a1, a1, s7
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	add	a0, a2, a0
	slli	a0, a0, 18
	and	a0, a0, s3
	slli	a2, a3, 4
	and	a2, a2, s1
	or	a1, a1, s8
	or	a0, a1, a0
	or	a0, a0, a2
.Ltmp95:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x10
	.loc	3 37 25 is_stmt 0       # kernel/v3/kernel.cpp:37:25
	sw	a0, -756(s4)
.Ltmp96:
	.loc	3 38 30 is_stmt 1       # kernel/v3/kernel.cpp:38:30
	mv	a0, s10
.Ltmp97:
	mv	a1, s5
	lw	a2, 0(sp)
	lw	a3, 4(sp)
	lw	a4, 8(sp)
	call	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj
.Ltmp98:
	.loc	3 34 17                 # kernel/v3/kernel.cpp:34:17
	lui	a5, %hi(__bsg_grp_org_y)
.Ltmp99:
	.loc	3 40 25                 # kernel/v3/kernel.cpp:40:25
	lw	a1, %lo(__bsg_grp_org_y)(a5)
	lw	a2, %lo(__bsg_y)(s0)
	lw	a3, %lo(__bsg_grp_org_x)(s11)
	lw	a4, %lo(__bsg_x)(s6)
	add	a1, a2, a1
	slli	a1, a1, 24
	add	a2, a4, a3
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	and	a1, a1, s7
	slli	a2, a2, 18
	and	a2, a2, s3
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, s8, a1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 262144
	or	a1, a1, a2
.Ltmp100:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x11
	.loc	3 40 25 is_stmt 0       # kernel/v3/kernel.cpp:40:25
	sw	a1, -756(s4)
.Ltmp101:
	#DEBUG_VALUE: i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	a1, %lo(__bsg_grp_org_y)(a5)
.Ltmp102:
	lw	a2, %lo(__bsg_y)(s0)
.Ltmp103:
	#DEBUG_VALUE: kernel_vector_add_int:rc <- $x10
	add	a1, a2, a1
.Ltmp104:
	.loc	3 36 34 is_stmt 1       # kernel/v3/kernel.cpp:36:34
	addi	s9, s9, -1
.Ltmp105:
	.loc	3 0 0 is_stmt 0         # kernel/v3/kernel.cpp:0:0
	slli	a1, a1, 24
.Ltmp106:
	.loc	3 36 17                 # kernel/v3/kernel.cpp:36:17
	bnez	s9, .LBB1_1
.Ltmp107:
# %bb.2:                                # %for.cond.cleanup
	#DEBUG_VALUE: kernel_vector_add_int:rc <- $x10
	#DEBUG_VALUE: kernel_vector_add_int:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_int:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_int:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int:rc <- $x10
	.loc	3 42 17 is_stmt 1       # kernel/v3/kernel.cpp:42:17
	lui	a2, %hi(__bsg_grp_org_x)
	lw	a2, %lo(__bsg_grp_org_x)(a2)
	lui	a3, %hi(__bsg_x)
	lw	a3, %lo(__bsg_x)(a3)
	add	a2, a3, a2
	lui	a3, %hi(__bsg_tile_group_id)
	lw	a3, %lo(__bsg_tile_group_id)(a3)
	slli	a2, a2, 18
	lui	a4, 4032
	and	a2, a2, a4
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 786432
	or	a1, a1, a2
.Ltmp108:
	#DEBUG_VALUE: val <- $x11
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	a2, 266241
.Ltmp109:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 42 17                 # kernel/v3/kernel.cpp:42:17
	sw	a1, -756(a2)
.Ltmp110:
	.loc	3 44 17 is_stmt 1       # kernel/v3/kernel.cpp:44:17
	lw	s11, 12(sp)
	lw	s10, 16(sp)
.Ltmp111:
	lw	s9, 20(sp)
	lw	s8, 24(sp)
	lw	s7, 28(sp)
	lw	s6, 32(sp)
	lw	s5, 36(sp)
.Ltmp112:
	lw	s4, 40(sp)
	lw	s3, 44(sp)
	lw	s2, 48(sp)
	lw	s1, 52(sp)
	lw	s0, 56(sp)
	lw	ra, 60(sp)
	addi	sp, sp, 64
	ret
.Ltmp113:
.Lfunc_end1:
	.size	kernel_vector_add_int, .Lfunc_end1-kernel_vector_add_int
	.cfi_endproc
                                        # -- End function
	.section	.text._Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj,"axG",@progbits,_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj,comdat
	.weak	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj # -- Begin function _Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj
	.p2align	2
	.type	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj,@function
_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj: # @_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj
.Lfunc_begin2:
	.loc	1 87 0                  # kernel/include/vector_add.hpp:87:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:block_size_x <- $x14
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
.Ltmp114:
	.loc	1 92 26 prologue_end    # kernel/include/vector_add.hpp:92:26
	sw	ra, 12(sp)
	.cfi_offset ra, -4
	lui	a3, %hi(__bsg_tile_group_id_x)
.Ltmp115:
	lw	a5, %lo(__bsg_tile_group_id_x)(a3)
.Ltmp116:
	.loc	1 100 28                # kernel/include/vector_add.hpp:100:28
	lui	a3, %hi(__bsg_id)
	lw	a3, %lo(__bsg_id)(a3)
.Ltmp117:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:block_size_x <- $x14
	.loc	1 92 48                 # kernel/include/vector_add.hpp:92:48
	mul	a5, a5, a4
.Ltmp118:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:start <- $x15
	.loc	1 93 30                 # kernel/include/vector_add.hpp:93:30
	add	a6, a5, a4
.Ltmp119:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:end <- $x16
	.loc	1 100 26                # kernel/include/vector_add.hpp:100:26
	add	t0, a5, a3
.Ltmp120:
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bgeu	t0, a6, .LBB2_7
.Ltmp121:
# %bb.1:                                # %for.body.preheader
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:start <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	sub	a5, a4, a3
.Ltmp122:
	not	a3, a3
	andi	t1, a5, 7
	add	a7, a3, a4
	beqz	t1, .LBB2_4
.Ltmp123:
# %bb.2:                                # %for.body.prol.preheader
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	slli	a3, t0, 2
	add	t3, a2, a3
	add	a5, a1, a3
	add	a3, a0, a3
.Ltmp124:
.LBB2_3:                                # %for.body.prol
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	#DEBUG_VALUE: iter_x <- $x5
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	lw	t2, 0(a3)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	lw	a4, 0(a5)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a4, t2
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a4, 0(t3)
.Ltmp125:
	.loc	1 100 59 is_stmt 1      # kernel/include/vector_add.hpp:100:59
	addi	t0, t0, 1
.Ltmp126:
	#DEBUG_VALUE: iter_x <- $x5
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	addi	t1, t1, -1
	addi	t3, t3, 4
	addi	a5, a5, 4
	addi	a3, a3, 4
	bnez	t1, .LBB2_3
.Ltmp127:
.LBB2_4:                                # %for.body.prol.loopexit
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	.loc	1 0 2                   # kernel/include/vector_add.hpp:0:2
	addi	a3, zero, 7
	.loc	1 100 2                 # kernel/include/vector_add.hpp:100:2
	bltu	a7, a3, .LBB2_7
.Ltmp128:
# %bb.5:                                # %for.body.preheader1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>:A <- $x10
	sub	a3, a6, t0
	slli	a4, t0, 2
	addi	a4, a4, 16
	add	a2, a2, a4
.Ltmp129:
	add	a1, a1, a4
.Ltmp130:
	add	a0, a0, a4
.Ltmp131:
.LBB2_6:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- undef
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	lw	a6, -16(a0)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	lw	a7, -16(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	t0, -12(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	a5, -12(a1)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a7, a6
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a4, -16(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a5, t0
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	a7, -8(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	t0, -8(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	t1, -4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	a4, -4(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a6, -12(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a5, -8(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a4, t1
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	a7, 0(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	t0, 0(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	t1, 4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	a4, 4(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a6, -4(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a5, 0(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a4, t1
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	a7, 8(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	t0, 8(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lw	t1, 12(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lw	a4, 12(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a6, 4(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a5, 8(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a4, t1
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sw	a4, 12(a2)
.Ltmp132:
	#DEBUG_VALUE: iter_x <- [DW_OP_plus_uconst 8, DW_OP_stack_value] undef
	.loc	1 100 45 is_stmt 1      # kernel/include/vector_add.hpp:100:45
	addi	a3, a3, -8
	addi	a2, a2, 32
	addi	a1, a1, 32
	addi	a0, a0, 32
.Ltmp133:
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bnez	a3, .LBB2_6
.Ltmp134:
.LBB2_7:                                # %for.cond.cleanup
	.loc	1 104 2 is_stmt 1       # kernel/include/vector_add.hpp:104:2
	lui	a0, %hi(r_barrier)
	addi	a0, a0, %lo(r_barrier)
	lui	a1, %hi(c_barrier)
	addi	a1, a1, %lo(c_barrier)
	call	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
.Ltmp135:
	.loc	1 106 9                 # kernel/include/vector_add.hpp:106:9
	mv	a0, zero
	lw	ra, 12(sp)
	addi	sp, sp, 16
	ret
.Ltmp136:
.Lfunc_end2:
	.size	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj, .Lfunc_end2-_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj
	.cfi_endproc
                                        # -- End function
	.text
	.globl	kernel_vector_add_int16 # -- Begin function kernel_vector_add_int16
	.p2align	2
	.type	kernel_vector_add_int16,@function
kernel_vector_add_int16:                # @kernel_vector_add_int16
.Lfunc_begin3:
	.loc	3 51 0                  # kernel/v3/kernel.cpp:51:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_int16:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_int16:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_int16:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_int16:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_int16:block_size_y <- $x14
	#DEBUG_VALUE: kernel_vector_add_int16:block_size_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_int16:tag <- $x16
	#DEBUG_VALUE: kernel_vector_add_int16:iter <- $x17
	addi	sp, sp, -64
	.cfi_def_cfa_offset 64
.Ltmp137:
	.loc	3 52 17 prologue_end    # kernel/v3/kernel.cpp:52:17
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
	lui	t2, %hi(__bsg_grp_org_y)
	lw	a4, %lo(__bsg_grp_org_y)(t2)
.Ltmp138:
	lui	t3, %hi(__bsg_y)
	lw	s0, %lo(__bsg_y)(t3)
	lui	s1, 64
	addi	s1, s1, -16
	add	t0, s0, a4
	lui	a4, %hi(__bsg_grp_org_x)
	lw	t1, %lo(__bsg_grp_org_x)(a4)
	lui	a4, %hi(__bsg_x)
	lw	t4, %lo(__bsg_x)(a4)
	slli	s0, t0, 24
	lui	a4, 258048
	and	t0, s0, a4
	add	a4, t4, t1
	lui	s0, %hi(__bsg_tile_group_id)
	lw	t1, %lo(__bsg_tile_group_id)(s0)
	slli	a4, a4, 18
	lui	s0, 4032
	and	a4, a4, s0
	slli	s0, t1, 4
	and	s0, s0, s1
	or	a4, t0, a4
	or	a4, a4, s0
	lui	s0, 524288
	or	a4, a4, s0
.Ltmp139:
	#DEBUG_VALUE: val <- $x14
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	s0, 266241
.Ltmp140:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 52 17                 # kernel/v3/kernel.cpp:52:17
	sw	a4, -756(s0)
.Ltmp141:
	#DEBUG_VALUE: kernel_vector_add_int16:rc <- undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	t0, %lo(__bsg_grp_org_y)(t2)
	lw	a4, %lo(__bsg_y)(t3)
.Ltmp142:
	#DEBUG_VALUE: kernel_vector_add_int16:iter <- $x17
	#DEBUG_VALUE: kernel_vector_add_int16:tag <- $x16
	sw	a5, 8(sp)
.Ltmp143:
	#DEBUG_VALUE: kernel_vector_add_int16:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	sw	a3, 4(sp)
.Ltmp144:
	#DEBUG_VALUE: kernel_vector_add_int16:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	sw	a2, 0(sp)
.Ltmp145:
	#DEBUG_VALUE: kernel_vector_add_int16:C <- [$x2+0]
	mv	s5, a1
.Ltmp146:
	#DEBUG_VALUE: kernel_vector_add_int16:B <- $x21
	mv	s10, a0
.Ltmp147:
	#DEBUG_VALUE: kernel_vector_add_int16:A <- $x26
	add	a0, a4, t0
	slli	a1, a0, 24
.Ltmp148:
	#DEBUG_VALUE: i <- 0
	andi	s8, a6, 15
.Ltmp149:
	.loc	3 54 17 is_stmt 1       # kernel/v3/kernel.cpp:54:17
	addi	s9, a7, 1
.Ltmp150:
	.loc	3 52 17                 # kernel/v3/kernel.cpp:52:17
	lui	s11, %hi(__bsg_grp_org_x)
	lui	s6, %hi(__bsg_x)
	lui	s7, 258048
	lui	s2, %hi(__bsg_tile_group_id)
	lui	s3, 4032
	lui	s4, 266241
	lui	s0, %hi(__bsg_y)
.Ltmp151:
.LBB3_1:                                # %do.body11
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: i <- 0
	#DEBUG_VALUE: kernel_vector_add_int16:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_int16:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_int16:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int16:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int16:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: i <- undef
	.loc	3 55 25                 # kernel/v3/kernel.cpp:55:25
	lw	a0, %lo(__bsg_grp_org_x)(s11)
	lw	a2, %lo(__bsg_x)(s6)
	and	a1, a1, s7
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	add	a0, a2, a0
	slli	a0, a0, 18
	and	a0, a0, s3
	slli	a2, a3, 4
	and	a2, a2, s1
	or	a1, a1, s8
	or	a0, a1, a0
	or	a0, a0, a2
.Ltmp152:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x10
	.loc	3 55 25 is_stmt 0       # kernel/v3/kernel.cpp:55:25
	sw	a0, -756(s4)
.Ltmp153:
	.loc	3 56 30 is_stmt 1       # kernel/v3/kernel.cpp:56:30
	mv	a0, s10
.Ltmp154:
	mv	a1, s5
	lw	a2, 0(sp)
	lw	a3, 4(sp)
	lw	a4, 8(sp)
	call	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj
.Ltmp155:
	.loc	3 52 17                 # kernel/v3/kernel.cpp:52:17
	lui	a5, %hi(__bsg_grp_org_y)
.Ltmp156:
	.loc	3 58 25                 # kernel/v3/kernel.cpp:58:25
	lw	a1, %lo(__bsg_grp_org_y)(a5)
	lw	a2, %lo(__bsg_y)(s0)
	lw	a3, %lo(__bsg_grp_org_x)(s11)
	lw	a4, %lo(__bsg_x)(s6)
	add	a1, a2, a1
	slli	a1, a1, 24
	add	a2, a4, a3
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	and	a1, a1, s7
	slli	a2, a2, 18
	and	a2, a2, s3
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, s8, a1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 262144
	or	a1, a1, a2
.Ltmp157:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x11
	.loc	3 58 25 is_stmt 0       # kernel/v3/kernel.cpp:58:25
	sw	a1, -756(s4)
.Ltmp158:
	#DEBUG_VALUE: i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	a1, %lo(__bsg_grp_org_y)(a5)
.Ltmp159:
	lw	a2, %lo(__bsg_y)(s0)
.Ltmp160:
	#DEBUG_VALUE: kernel_vector_add_int16:rc <- $x10
	add	a1, a2, a1
.Ltmp161:
	.loc	3 54 34 is_stmt 1       # kernel/v3/kernel.cpp:54:34
	addi	s9, s9, -1
.Ltmp162:
	.loc	3 0 0 is_stmt 0         # kernel/v3/kernel.cpp:0:0
	slli	a1, a1, 24
.Ltmp163:
	.loc	3 54 17                 # kernel/v3/kernel.cpp:54:17
	bnez	s9, .LBB3_1
.Ltmp164:
# %bb.2:                                # %for.cond.cleanup
	#DEBUG_VALUE: kernel_vector_add_int16:rc <- $x10
	#DEBUG_VALUE: kernel_vector_add_int16:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_int16:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_int16:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int16:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int16:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int16:rc <- $x10
	.loc	3 60 17 is_stmt 1       # kernel/v3/kernel.cpp:60:17
	lui	a2, %hi(__bsg_grp_org_x)
	lw	a2, %lo(__bsg_grp_org_x)(a2)
	lui	a3, %hi(__bsg_x)
	lw	a3, %lo(__bsg_x)(a3)
	add	a2, a3, a2
	lui	a3, %hi(__bsg_tile_group_id)
	lw	a3, %lo(__bsg_tile_group_id)(a3)
	slli	a2, a2, 18
	lui	a4, 4032
	and	a2, a2, a4
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 786432
	or	a1, a1, a2
.Ltmp165:
	#DEBUG_VALUE: val <- $x11
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	a2, 266241
.Ltmp166:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 60 17                 # kernel/v3/kernel.cpp:60:17
	sw	a1, -756(a2)
.Ltmp167:
	.loc	3 62 17 is_stmt 1       # kernel/v3/kernel.cpp:62:17
	lw	s11, 12(sp)
	lw	s10, 16(sp)
.Ltmp168:
	lw	s9, 20(sp)
	lw	s8, 24(sp)
	lw	s7, 28(sp)
	lw	s6, 32(sp)
	lw	s5, 36(sp)
.Ltmp169:
	lw	s4, 40(sp)
	lw	s3, 44(sp)
	lw	s2, 48(sp)
	lw	s1, 52(sp)
	lw	s0, 56(sp)
	lw	ra, 60(sp)
	addi	sp, sp, 64
	ret
.Ltmp170:
.Lfunc_end3:
	.size	kernel_vector_add_int16, .Lfunc_end3-kernel_vector_add_int16
	.cfi_endproc
                                        # -- End function
	.section	.text._Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj,"axG",@progbits,_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj,comdat
	.weak	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj # -- Begin function _Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj
	.p2align	2
	.type	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj,@function
_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj: # @_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj
.Lfunc_begin4:
	.loc	1 87 0                  # kernel/include/vector_add.hpp:87:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:block_size_x <- $x14
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
.Ltmp171:
	.loc	1 92 26 prologue_end    # kernel/include/vector_add.hpp:92:26
	sw	ra, 12(sp)
	.cfi_offset ra, -4
	lui	a3, %hi(__bsg_tile_group_id_x)
.Ltmp172:
	lw	a5, %lo(__bsg_tile_group_id_x)(a3)
.Ltmp173:
	.loc	1 100 28                # kernel/include/vector_add.hpp:100:28
	lui	a3, %hi(__bsg_id)
	lw	a3, %lo(__bsg_id)(a3)
.Ltmp174:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:block_size_x <- $x14
	.loc	1 92 48                 # kernel/include/vector_add.hpp:92:48
	mul	a5, a5, a4
.Ltmp175:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:start <- $x15
	.loc	1 93 30                 # kernel/include/vector_add.hpp:93:30
	add	a6, a5, a4
.Ltmp176:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:end <- $x16
	.loc	1 100 26                # kernel/include/vector_add.hpp:100:26
	add	t0, a5, a3
.Ltmp177:
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bgeu	t0, a6, .LBB4_7
.Ltmp178:
# %bb.1:                                # %for.body.preheader
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:start <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	sub	a5, a4, a3
.Ltmp179:
	not	a3, a3
	andi	t1, a5, 7
	add	a7, a3, a4
	beqz	t1, .LBB4_4
.Ltmp180:
# %bb.2:                                # %for.body.prol.preheader
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	slli	a3, t0, 1
	add	t3, a2, a3
	add	a5, a1, a3
	add	a3, a0, a3
.Ltmp181:
.LBB4_3:                                # %for.body.prol
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	#DEBUG_VALUE: iter_x <- $x5
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	lh	t2, 0(a3)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	lh	a4, 0(a5)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a4, t2
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a4, 0(t3)
.Ltmp182:
	.loc	1 100 59 is_stmt 1      # kernel/include/vector_add.hpp:100:59
	addi	t0, t0, 1
.Ltmp183:
	#DEBUG_VALUE: iter_x <- $x5
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	addi	t1, t1, -1
	addi	t3, t3, 2
	addi	a5, a5, 2
	addi	a3, a3, 2
	bnez	t1, .LBB4_3
.Ltmp184:
.LBB4_4:                                # %for.body.prol.loopexit
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	.loc	1 0 2                   # kernel/include/vector_add.hpp:0:2
	addi	a3, zero, 7
	.loc	1 100 2                 # kernel/include/vector_add.hpp:100:2
	bltu	a7, a3, .LBB4_7
.Ltmp185:
# %bb.5:                                # %for.body.preheader1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>:A <- $x10
	sub	a3, a6, t0
	slli	a4, t0, 1
	addi	a4, a4, 8
	add	a2, a2, a4
.Ltmp186:
	add	a1, a1, a4
.Ltmp187:
	add	a0, a0, a4
.Ltmp188:
.LBB4_6:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- undef
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	lh	a6, -8(a0)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	lh	a7, -8(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	t0, -6(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	a5, -6(a1)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a7, a6
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a4, -8(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a5, t0
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	a7, -4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	t0, -4(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	t1, -2(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	a4, -2(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a6, -6(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a5, -4(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a4, t1
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	a7, 0(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	t0, 0(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	t1, 2(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	a4, 2(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a6, -2(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a5, 0(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a4, t1
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	a7, 4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	t0, 4(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lh	t1, 6(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lh	a4, 6(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a6, 2(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a5, 4(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a4, t1
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sh	a4, 6(a2)
.Ltmp189:
	#DEBUG_VALUE: iter_x <- [DW_OP_plus_uconst 8, DW_OP_stack_value] undef
	.loc	1 100 45 is_stmt 1      # kernel/include/vector_add.hpp:100:45
	addi	a3, a3, -8
	addi	a2, a2, 16
	addi	a1, a1, 16
	addi	a0, a0, 16
.Ltmp190:
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bnez	a3, .LBB4_6
.Ltmp191:
.LBB4_7:                                # %for.cond.cleanup
	.loc	1 104 2 is_stmt 1       # kernel/include/vector_add.hpp:104:2
	lui	a0, %hi(r_barrier)
	addi	a0, a0, %lo(r_barrier)
	lui	a1, %hi(c_barrier)
	addi	a1, a1, %lo(c_barrier)
	call	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
.Ltmp192:
	.loc	1 106 9                 # kernel/include/vector_add.hpp:106:9
	mv	a0, zero
	lw	ra, 12(sp)
	addi	sp, sp, 16
	ret
.Ltmp193:
.Lfunc_end4:
	.size	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj, .Lfunc_end4-_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj
	.cfi_endproc
                                        # -- End function
	.text
	.globl	kernel_vector_add_int8  # -- Begin function kernel_vector_add_int8
	.p2align	2
	.type	kernel_vector_add_int8,@function
kernel_vector_add_int8:                 # @kernel_vector_add_int8
.Lfunc_begin5:
	.loc	3 69 0                  # kernel/v3/kernel.cpp:69:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_int8:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_int8:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_int8:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_int8:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_int8:block_size_y <- $x14
	#DEBUG_VALUE: kernel_vector_add_int8:block_size_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_int8:tag <- $x16
	#DEBUG_VALUE: kernel_vector_add_int8:iter <- $x17
	addi	sp, sp, -64
	.cfi_def_cfa_offset 64
.Ltmp194:
	.loc	3 70 17 prologue_end    # kernel/v3/kernel.cpp:70:17
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
	lui	t2, %hi(__bsg_grp_org_y)
	lw	a4, %lo(__bsg_grp_org_y)(t2)
.Ltmp195:
	lui	t3, %hi(__bsg_y)
	lw	s0, %lo(__bsg_y)(t3)
	lui	s1, 64
	addi	s1, s1, -16
	add	t0, s0, a4
	lui	a4, %hi(__bsg_grp_org_x)
	lw	t1, %lo(__bsg_grp_org_x)(a4)
	lui	a4, %hi(__bsg_x)
	lw	t4, %lo(__bsg_x)(a4)
	slli	s0, t0, 24
	lui	a4, 258048
	and	t0, s0, a4
	add	a4, t4, t1
	lui	s0, %hi(__bsg_tile_group_id)
	lw	t1, %lo(__bsg_tile_group_id)(s0)
	slli	a4, a4, 18
	lui	s0, 4032
	and	a4, a4, s0
	slli	s0, t1, 4
	and	s0, s0, s1
	or	a4, t0, a4
	or	a4, a4, s0
	lui	s0, 524288
	or	a4, a4, s0
.Ltmp196:
	#DEBUG_VALUE: val <- $x14
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	s0, 266241
.Ltmp197:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 70 17                 # kernel/v3/kernel.cpp:70:17
	sw	a4, -756(s0)
.Ltmp198:
	#DEBUG_VALUE: kernel_vector_add_int8:rc <- undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	t0, %lo(__bsg_grp_org_y)(t2)
	lw	a4, %lo(__bsg_y)(t3)
.Ltmp199:
	#DEBUG_VALUE: kernel_vector_add_int8:iter <- $x17
	#DEBUG_VALUE: kernel_vector_add_int8:tag <- $x16
	sw	a5, 8(sp)
.Ltmp200:
	#DEBUG_VALUE: kernel_vector_add_int8:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	sw	a3, 4(sp)
.Ltmp201:
	#DEBUG_VALUE: kernel_vector_add_int8:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	sw	a2, 0(sp)
.Ltmp202:
	#DEBUG_VALUE: kernel_vector_add_int8:C <- [$x2+0]
	mv	s5, a1
.Ltmp203:
	#DEBUG_VALUE: kernel_vector_add_int8:B <- $x21
	mv	s10, a0
.Ltmp204:
	#DEBUG_VALUE: kernel_vector_add_int8:A <- $x26
	add	a0, a4, t0
	slli	a1, a0, 24
.Ltmp205:
	#DEBUG_VALUE: i <- 0
	andi	s8, a6, 15
.Ltmp206:
	.loc	3 72 17 is_stmt 1       # kernel/v3/kernel.cpp:72:17
	addi	s9, a7, 1
.Ltmp207:
	.loc	3 70 17                 # kernel/v3/kernel.cpp:70:17
	lui	s11, %hi(__bsg_grp_org_x)
	lui	s6, %hi(__bsg_x)
	lui	s7, 258048
	lui	s2, %hi(__bsg_tile_group_id)
	lui	s3, 4032
	lui	s4, 266241
	lui	s0, %hi(__bsg_y)
.Ltmp208:
.LBB5_1:                                # %do.body11
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: i <- 0
	#DEBUG_VALUE: kernel_vector_add_int8:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_int8:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_int8:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int8:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int8:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: i <- undef
	.loc	3 73 25                 # kernel/v3/kernel.cpp:73:25
	lw	a0, %lo(__bsg_grp_org_x)(s11)
	lw	a2, %lo(__bsg_x)(s6)
	and	a1, a1, s7
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	add	a0, a2, a0
	slli	a0, a0, 18
	and	a0, a0, s3
	slli	a2, a3, 4
	and	a2, a2, s1
	or	a1, a1, s8
	or	a0, a1, a0
	or	a0, a0, a2
.Ltmp209:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x10
	.loc	3 73 25 is_stmt 0       # kernel/v3/kernel.cpp:73:25
	sw	a0, -756(s4)
.Ltmp210:
	.loc	3 74 30 is_stmt 1       # kernel/v3/kernel.cpp:74:30
	mv	a0, s10
.Ltmp211:
	mv	a1, s5
	lw	a2, 0(sp)
	lw	a3, 4(sp)
	lw	a4, 8(sp)
	call	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj
.Ltmp212:
	.loc	3 70 17                 # kernel/v3/kernel.cpp:70:17
	lui	a5, %hi(__bsg_grp_org_y)
.Ltmp213:
	.loc	3 76 25                 # kernel/v3/kernel.cpp:76:25
	lw	a1, %lo(__bsg_grp_org_y)(a5)
	lw	a2, %lo(__bsg_y)(s0)
	lw	a3, %lo(__bsg_grp_org_x)(s11)
	lw	a4, %lo(__bsg_x)(s6)
	add	a1, a2, a1
	slli	a1, a1, 24
	add	a2, a4, a3
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	and	a1, a1, s7
	slli	a2, a2, 18
	and	a2, a2, s3
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, s8, a1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 262144
	or	a1, a1, a2
.Ltmp214:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x11
	.loc	3 76 25 is_stmt 0       # kernel/v3/kernel.cpp:76:25
	sw	a1, -756(s4)
.Ltmp215:
	#DEBUG_VALUE: i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	a1, %lo(__bsg_grp_org_y)(a5)
.Ltmp216:
	lw	a2, %lo(__bsg_y)(s0)
.Ltmp217:
	#DEBUG_VALUE: kernel_vector_add_int8:rc <- $x10
	add	a1, a2, a1
.Ltmp218:
	.loc	3 72 34 is_stmt 1       # kernel/v3/kernel.cpp:72:34
	addi	s9, s9, -1
.Ltmp219:
	.loc	3 0 0 is_stmt 0         # kernel/v3/kernel.cpp:0:0
	slli	a1, a1, 24
.Ltmp220:
	.loc	3 72 17                 # kernel/v3/kernel.cpp:72:17
	bnez	s9, .LBB5_1
.Ltmp221:
# %bb.2:                                # %for.cond.cleanup
	#DEBUG_VALUE: kernel_vector_add_int8:rc <- $x10
	#DEBUG_VALUE: kernel_vector_add_int8:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_int8:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_int8:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int8:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int8:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_int8:rc <- $x10
	.loc	3 78 17 is_stmt 1       # kernel/v3/kernel.cpp:78:17
	lui	a2, %hi(__bsg_grp_org_x)
	lw	a2, %lo(__bsg_grp_org_x)(a2)
	lui	a3, %hi(__bsg_x)
	lw	a3, %lo(__bsg_x)(a3)
	add	a2, a3, a2
	lui	a3, %hi(__bsg_tile_group_id)
	lw	a3, %lo(__bsg_tile_group_id)(a3)
	slli	a2, a2, 18
	lui	a4, 4032
	and	a2, a2, a4
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 786432
	or	a1, a1, a2
.Ltmp222:
	#DEBUG_VALUE: val <- $x11
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	a2, 266241
.Ltmp223:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 78 17                 # kernel/v3/kernel.cpp:78:17
	sw	a1, -756(a2)
.Ltmp224:
	.loc	3 80 17 is_stmt 1       # kernel/v3/kernel.cpp:80:17
	lw	s11, 12(sp)
	lw	s10, 16(sp)
.Ltmp225:
	lw	s9, 20(sp)
	lw	s8, 24(sp)
	lw	s7, 28(sp)
	lw	s6, 32(sp)
	lw	s5, 36(sp)
.Ltmp226:
	lw	s4, 40(sp)
	lw	s3, 44(sp)
	lw	s2, 48(sp)
	lw	s1, 52(sp)
	lw	s0, 56(sp)
	lw	ra, 60(sp)
	addi	sp, sp, 64
	ret
.Ltmp227:
.Lfunc_end5:
	.size	kernel_vector_add_int8, .Lfunc_end5-kernel_vector_add_int8
	.cfi_endproc
                                        # -- End function
	.section	.text._Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj,"axG",@progbits,_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj,comdat
	.weak	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj # -- Begin function _Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj
	.p2align	2
	.type	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj,@function
_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj: # @_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj
.Lfunc_begin6:
	.loc	1 87 0                  # kernel/include/vector_add.hpp:87:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:block_size_x <- $x14
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
.Ltmp228:
	.loc	1 92 26 prologue_end    # kernel/include/vector_add.hpp:92:26
	sw	ra, 12(sp)
	.cfi_offset ra, -4
	lui	a3, %hi(__bsg_tile_group_id_x)
.Ltmp229:
	lw	a5, %lo(__bsg_tile_group_id_x)(a3)
.Ltmp230:
	.loc	1 100 28                # kernel/include/vector_add.hpp:100:28
	lui	a3, %hi(__bsg_id)
	lw	a3, %lo(__bsg_id)(a3)
.Ltmp231:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:block_size_x <- $x14
	.loc	1 92 48                 # kernel/include/vector_add.hpp:92:48
	mul	a5, a5, a4
.Ltmp232:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:start <- $x15
	.loc	1 93 30                 # kernel/include/vector_add.hpp:93:30
	add	a6, a5, a4
.Ltmp233:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:end <- $x16
	.loc	1 100 26                # kernel/include/vector_add.hpp:100:26
	add	a5, a5, a3
.Ltmp234:
	#DEBUG_VALUE: iter_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:A <- $x10
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bgeu	a5, a6, .LBB6_6
.Ltmp235:
# %bb.1:                                # %for.body.preheader
	#DEBUG_VALUE: iter_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:A <- $x10
	sub	a7, a4, a3
	not	t0, a3
	andi	a3, a7, 7
	add	a7, t0, a4
	beqz	a3, .LBB6_3
.Ltmp236:
.LBB6_2:                                # %for.body.prol
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:A <- $x10
	#DEBUG_VALUE: iter_x <- $x15
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	add	a4, a0, a5
	lb	t0, 0(a4)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	add	a4, a1, a5
	lb	a4, 0(a4)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	t0, a4, t0
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	add	a4, a2, a5
	sb	t0, 0(a4)
.Ltmp237:
	.loc	1 100 2 is_stmt 1       # kernel/include/vector_add.hpp:100:2
	addi	a3, a3, -1
.Ltmp238:
	.loc	1 100 59 is_stmt 0      # kernel/include/vector_add.hpp:100:59
	addi	a5, a5, 1
.Ltmp239:
	#DEBUG_VALUE: iter_x <- $x15
	.loc	1 100 2                 # kernel/include/vector_add.hpp:100:2
	bnez	a3, .LBB6_2
.Ltmp240:
.LBB6_3:                                # %for.body.prol.loopexit
	#DEBUG_VALUE: iter_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:A <- $x10
	.loc	1 0 2                   # kernel/include/vector_add.hpp:0:2
	addi	a3, zero, 7
	.loc	1 100 2                 # kernel/include/vector_add.hpp:100:2
	bltu	a7, a3, .LBB6_6
.Ltmp241:
# %bb.4:                                # %for.body.preheader1
	#DEBUG_VALUE: iter_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>:A <- $x10
	sub	a3, a6, a5
	addi	a4, a5, 3
	add	a2, a2, a4
.Ltmp242:
	add	a1, a1, a4
.Ltmp243:
	add	a0, a0, a4
.Ltmp244:
.LBB6_5:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- undef
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	lb	a6, -3(a0)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	lb	a7, -3(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	t0, -2(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	a5, -2(a1)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a7, a6
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a4, -3(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a5, t0
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	a7, -1(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	t0, -1(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	t1, 0(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	a4, 0(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a6, -2(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a5, -1(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a4, t1
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	a7, 1(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	t0, 1(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	t1, 2(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	a4, 2(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a6, 0(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a5, 1(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a6, a4, t1
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	a7, 3(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	t0, 3(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	lb	t1, 4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	lb	a4, 4(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a6, 2(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a5, t0, a7
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a5, 3(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	add	a4, a4, t1
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	sb	a4, 4(a2)
.Ltmp245:
	#DEBUG_VALUE: iter_x <- [DW_OP_plus_uconst 8, DW_OP_stack_value] undef
	.loc	1 100 45 is_stmt 1      # kernel/include/vector_add.hpp:100:45
	addi	a3, a3, -8
	addi	a2, a2, 8
	addi	a1, a1, 8
	addi	a0, a0, 8
.Ltmp246:
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bnez	a3, .LBB6_5
.Ltmp247:
.LBB6_6:                                # %for.cond.cleanup
	.loc	1 104 2 is_stmt 1       # kernel/include/vector_add.hpp:104:2
	lui	a0, %hi(r_barrier)
	addi	a0, a0, %lo(r_barrier)
	lui	a1, %hi(c_barrier)
	addi	a1, a1, %lo(c_barrier)
	call	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
.Ltmp248:
	.loc	1 106 9                 # kernel/include/vector_add.hpp:106:9
	mv	a0, zero
	lw	ra, 12(sp)
	addi	sp, sp, 16
	ret
.Ltmp249:
.Lfunc_end6:
	.size	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj, .Lfunc_end6-_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj
	.cfi_endproc
                                        # -- End function
	.text
	.globl	kernel_vector_add_float # -- Begin function kernel_vector_add_float
	.p2align	2
	.type	kernel_vector_add_float,@function
kernel_vector_add_float:                # @kernel_vector_add_float
.Lfunc_begin7:
	.loc	3 87 0                  # kernel/v3/kernel.cpp:87:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_float:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_float:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_float:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_float:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_float:block_size_y <- $x14
	#DEBUG_VALUE: kernel_vector_add_float:block_size_x <- $x15
	#DEBUG_VALUE: kernel_vector_add_float:tag <- $x16
	#DEBUG_VALUE: kernel_vector_add_float:iter <- $x17
	addi	sp, sp, -64
	.cfi_def_cfa_offset 64
.Ltmp250:
	.loc	3 88 17 prologue_end    # kernel/v3/kernel.cpp:88:17
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
	lui	t2, %hi(__bsg_grp_org_y)
	lw	a4, %lo(__bsg_grp_org_y)(t2)
.Ltmp251:
	lui	t3, %hi(__bsg_y)
	lw	s0, %lo(__bsg_y)(t3)
	lui	s1, 64
	addi	s1, s1, -16
	add	t0, s0, a4
	lui	a4, %hi(__bsg_grp_org_x)
	lw	t1, %lo(__bsg_grp_org_x)(a4)
	lui	a4, %hi(__bsg_x)
	lw	t4, %lo(__bsg_x)(a4)
	slli	s0, t0, 24
	lui	a4, 258048
	and	t0, s0, a4
	add	a4, t4, t1
	lui	s0, %hi(__bsg_tile_group_id)
	lw	t1, %lo(__bsg_tile_group_id)(s0)
	slli	a4, a4, 18
	lui	s0, 4032
	and	a4, a4, s0
	slli	s0, t1, 4
	and	s0, s0, s1
	or	a4, t0, a4
	or	a4, a4, s0
	lui	s0, 524288
	or	a4, a4, s0
.Ltmp252:
	#DEBUG_VALUE: val <- $x14
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	s0, 266241
.Ltmp253:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 88 17                 # kernel/v3/kernel.cpp:88:17
	sw	a4, -756(s0)
.Ltmp254:
	#DEBUG_VALUE: kernel_vector_add_float:rc <- undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	t0, %lo(__bsg_grp_org_y)(t2)
	lw	a4, %lo(__bsg_y)(t3)
.Ltmp255:
	#DEBUG_VALUE: kernel_vector_add_float:iter <- $x17
	#DEBUG_VALUE: kernel_vector_add_float:tag <- $x16
	sw	a5, 8(sp)
.Ltmp256:
	#DEBUG_VALUE: kernel_vector_add_float:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	sw	a3, 4(sp)
.Ltmp257:
	#DEBUG_VALUE: kernel_vector_add_float:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	sw	a2, 0(sp)
.Ltmp258:
	#DEBUG_VALUE: kernel_vector_add_float:C <- [$x2+0]
	mv	s5, a1
.Ltmp259:
	#DEBUG_VALUE: kernel_vector_add_float:B <- $x21
	mv	s10, a0
.Ltmp260:
	#DEBUG_VALUE: kernel_vector_add_float:A <- $x26
	add	a0, a4, t0
	slli	a1, a0, 24
.Ltmp261:
	#DEBUG_VALUE: i <- 0
	andi	s8, a6, 15
.Ltmp262:
	.loc	3 90 17 is_stmt 1       # kernel/v3/kernel.cpp:90:17
	addi	s9, a7, 1
.Ltmp263:
	.loc	3 88 17                 # kernel/v3/kernel.cpp:88:17
	lui	s11, %hi(__bsg_grp_org_x)
	lui	s6, %hi(__bsg_x)
	lui	s7, 258048
	lui	s2, %hi(__bsg_tile_group_id)
	lui	s3, 4032
	lui	s4, 266241
	lui	s0, %hi(__bsg_y)
.Ltmp264:
.LBB7_1:                                # %do.body11
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: i <- 0
	#DEBUG_VALUE: kernel_vector_add_float:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_float:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_float:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_float:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_float:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: i <- undef
	.loc	3 91 25                 # kernel/v3/kernel.cpp:91:25
	lw	a0, %lo(__bsg_grp_org_x)(s11)
	lw	a2, %lo(__bsg_x)(s6)
	and	a1, a1, s7
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	add	a0, a2, a0
	slli	a0, a0, 18
	and	a0, a0, s3
	slli	a2, a3, 4
	and	a2, a2, s1
	or	a1, a1, s8
	or	a0, a1, a0
	or	a0, a0, a2
.Ltmp265:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x10
	.loc	3 91 25 is_stmt 0       # kernel/v3/kernel.cpp:91:25
	sw	a0, -756(s4)
.Ltmp266:
	.loc	3 92 30 is_stmt 1       # kernel/v3/kernel.cpp:92:30
	mv	a0, s10
.Ltmp267:
	mv	a1, s5
	lw	a2, 0(sp)
	lw	a3, 4(sp)
	lw	a4, 8(sp)
	call	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj
.Ltmp268:
	.loc	3 88 17                 # kernel/v3/kernel.cpp:88:17
	lui	a5, %hi(__bsg_grp_org_y)
.Ltmp269:
	.loc	3 94 25                 # kernel/v3/kernel.cpp:94:25
	lw	a1, %lo(__bsg_grp_org_y)(a5)
	lw	a2, %lo(__bsg_y)(s0)
	lw	a3, %lo(__bsg_grp_org_x)(s11)
	lw	a4, %lo(__bsg_x)(s6)
	add	a1, a2, a1
	slli	a1, a1, 24
	add	a2, a4, a3
	lw	a3, %lo(__bsg_tile_group_id)(s2)
	and	a1, a1, s7
	slli	a2, a2, 18
	and	a2, a2, s3
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, s8, a1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 262144
	or	a1, a1, a2
.Ltmp270:
	#DEBUG_VALUE: ptr <- undef
	#DEBUG_VALUE: val <- $x11
	.loc	3 94 25 is_stmt 0       # kernel/v3/kernel.cpp:94:25
	sw	a1, -756(s4)
.Ltmp271:
	#DEBUG_VALUE: i <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.loc	3 0 0                   # kernel/v3/kernel.cpp:0:0
	lw	a1, %lo(__bsg_grp_org_y)(a5)
.Ltmp272:
	lw	a2, %lo(__bsg_y)(s0)
.Ltmp273:
	#DEBUG_VALUE: kernel_vector_add_float:rc <- $x10
	add	a1, a2, a1
.Ltmp274:
	.loc	3 90 34 is_stmt 1       # kernel/v3/kernel.cpp:90:34
	addi	s9, s9, -1
.Ltmp275:
	.loc	3 0 0 is_stmt 0         # kernel/v3/kernel.cpp:0:0
	slli	a1, a1, 24
.Ltmp276:
	.loc	3 90 17                 # kernel/v3/kernel.cpp:90:17
	bnez	s9, .LBB7_1
.Ltmp277:
# %bb.2:                                # %for.cond.cleanup
	#DEBUG_VALUE: kernel_vector_add_float:rc <- $x10
	#DEBUG_VALUE: kernel_vector_add_float:A <- $x26
	#DEBUG_VALUE: kernel_vector_add_float:B <- $x21
	#DEBUG_VALUE: kernel_vector_add_float:C <- [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_float:WIDTH <- [DW_OP_plus_uconst 4] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_float:block_size_x <- [DW_OP_plus_uconst 8] [$x2+0]
	#DEBUG_VALUE: kernel_vector_add_float:rc <- $x10
	.loc	3 96 17 is_stmt 1       # kernel/v3/kernel.cpp:96:17
	lui	a2, %hi(__bsg_grp_org_x)
	lw	a2, %lo(__bsg_grp_org_x)(a2)
	lui	a3, %hi(__bsg_x)
	lw	a3, %lo(__bsg_x)(a3)
	add	a2, a3, a2
	lui	a3, %hi(__bsg_tile_group_id)
	lw	a3, %lo(__bsg_tile_group_id)(a3)
	slli	a2, a2, 18
	lui	a4, 4032
	and	a2, a2, a4
	slli	a3, a3, 4
	and	a3, a3, s1
	or	a1, a1, a2
	or	a1, a1, a3
	lui	a2, 786432
	or	a1, a1, a2
.Ltmp278:
	#DEBUG_VALUE: val <- $x11
	.loc	3 0 17 is_stmt 0        # kernel/v3/kernel.cpp:0:17
	lui	a2, 266241
.Ltmp279:
	#DEBUG_VALUE: ptr <- undef
	.loc	3 96 17                 # kernel/v3/kernel.cpp:96:17
	sw	a1, -756(a2)
.Ltmp280:
	.loc	3 98 17 is_stmt 1       # kernel/v3/kernel.cpp:98:17
	lw	s11, 12(sp)
	lw	s10, 16(sp)
.Ltmp281:
	lw	s9, 20(sp)
	lw	s8, 24(sp)
	lw	s7, 28(sp)
	lw	s6, 32(sp)
	lw	s5, 36(sp)
.Ltmp282:
	lw	s4, 40(sp)
	lw	s3, 44(sp)
	lw	s2, 48(sp)
	lw	s1, 52(sp)
	lw	s0, 56(sp)
	lw	ra, 60(sp)
	addi	sp, sp, 64
	ret
.Ltmp283:
.Lfunc_end7:
	.size	kernel_vector_add_float, .Lfunc_end7-kernel_vector_add_float
	.cfi_endproc
                                        # -- End function
	.section	.text._Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj,"axG",@progbits,_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj,comdat
	.weak	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj # -- Begin function _Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj
	.p2align	2
	.type	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj,@function
_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj: # @_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj
.Lfunc_begin8:
	.loc	1 87 0                  # kernel/include/vector_add.hpp:87:0
	.cfi_startproc
# %bb.0:                                # %entry
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:WIDTH <- $x13
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:block_size_x <- $x14
	addi	sp, sp, -16
	.cfi_def_cfa_offset 16
.Ltmp284:
	.loc	1 92 26 prologue_end    # kernel/include/vector_add.hpp:92:26
	sw	ra, 12(sp)
	.cfi_offset ra, -4
	lui	a3, %hi(__bsg_tile_group_id_x)
.Ltmp285:
	lw	a5, %lo(__bsg_tile_group_id_x)(a3)
.Ltmp286:
	.loc	1 100 28                # kernel/include/vector_add.hpp:100:28
	lui	a3, %hi(__bsg_id)
	lw	a3, %lo(__bsg_id)(a3)
.Ltmp287:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:block_size_x <- $x14
	.loc	1 92 48                 # kernel/include/vector_add.hpp:92:48
	mul	a5, a5, a4
.Ltmp288:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:start <- $x15
	.loc	1 93 30                 # kernel/include/vector_add.hpp:93:30
	add	a6, a5, a4
.Ltmp289:
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	.loc	1 100 26                # kernel/include/vector_add.hpp:100:26
	add	t0, a5, a3
.Ltmp290:
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bgeu	t0, a6, .LBB8_7
.Ltmp291:
# %bb.1:                                # %for.body.preheader
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:start <- $x15
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	sub	a5, a4, a3
.Ltmp292:
	not	a3, a3
	andi	t1, a5, 7
	add	a7, a3, a4
	beqz	t1, .LBB8_4
.Ltmp293:
# %bb.2:                                # %for.body.prol.preheader
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:block_size_x <- $x14
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	slli	a3, t0, 2
	add	a4, a2, a3
.Ltmp294:
	add	a5, a1, a3
	add	a3, a0, a3
.Ltmp295:
.LBB8_3:                                # %for.body.prol
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	#DEBUG_VALUE: iter_x <- $x5
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	flw	ft0, 0(a3)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	flw	ft1, 0(a5)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft1, ft0
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, 0(a4)
.Ltmp296:
	.loc	1 100 59 is_stmt 1      # kernel/include/vector_add.hpp:100:59
	addi	t0, t0, 1
.Ltmp297:
	#DEBUG_VALUE: iter_x <- $x5
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	addi	t1, t1, -1
	addi	a4, a4, 4
	addi	a5, a5, 4
	addi	a3, a3, 4
	bnez	t1, .LBB8_3
.Ltmp298:
.LBB8_4:                                # %for.body.prol.loopexit
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	.loc	1 0 2                   # kernel/include/vector_add.hpp:0:2
	addi	a3, zero, 7
	.loc	1 100 2                 # kernel/include/vector_add.hpp:100:2
	bltu	a7, a3, .LBB8_7
.Ltmp299:
# %bb.5:                                # %for.body.preheader1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:C <- $x12
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:B <- $x11
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:A <- $x10
	sub	a3, a6, t0
	slli	a4, t0, 2
	addi	a4, a4, 16
	add	a2, a2, a4
.Ltmp300:
	add	a1, a1, a4
.Ltmp301:
	add	a0, a0, a4
.Ltmp302:
.LBB8_6:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: iter_x <- $x5
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	#DEBUG_VALUE: iter_x <- undef
	.loc	1 101 29 is_stmt 1      # kernel/include/vector_add.hpp:101:29
	flw	ft0, -16(a0)
	.loc	1 101 41 is_stmt 0      # kernel/include/vector_add.hpp:101:41
	flw	ft1, -16(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft2, -12(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft3, -12(a1)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft1, ft0
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, -16(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft3, ft2
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft1, -8(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft2, -8(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft3, -4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft4, -4(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, -12(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft2, ft1
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, -8(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft4, ft3
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft1, 0(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft2, 0(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft3, 4(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft4, 4(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, -4(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft2, ft1
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, 0(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft4, ft3
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft1, 8(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft2, 8(a1)
	.loc	1 101 29                # kernel/include/vector_add.hpp:101:29
	flw	ft3, 12(a0)
	.loc	1 101 41                # kernel/include/vector_add.hpp:101:41
	flw	ft4, 12(a1)
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, 4(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft2, ft1
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, 8(a2)
	.loc	1 101 39                # kernel/include/vector_add.hpp:101:39
	fadd.s	ft0, ft4, ft3
	.loc	1 101 27                # kernel/include/vector_add.hpp:101:27
	fsw	ft0, 12(a2)
.Ltmp303:
	#DEBUG_VALUE: iter_x <- [DW_OP_plus_uconst 8, DW_OP_stack_value] undef
	.loc	1 100 45 is_stmt 1      # kernel/include/vector_add.hpp:100:45
	addi	a3, a3, -8
	addi	a2, a2, 32
	addi	a1, a1, 32
	addi	a0, a0, 32
.Ltmp304:
	.loc	1 100 2 is_stmt 0       # kernel/include/vector_add.hpp:100:2
	bnez	a3, .LBB8_6
.Ltmp305:
.LBB8_7:                                # %for.cond.cleanup
	#DEBUG_VALUE: kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>:end <- $x16
	.loc	1 104 2 is_stmt 1       # kernel/include/vector_add.hpp:104:2
	lui	a0, %hi(r_barrier)
	addi	a0, a0, %lo(r_barrier)
	lui	a1, %hi(c_barrier)
	addi	a1, a1, %lo(c_barrier)
	call	_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_
.Ltmp306:
	.loc	1 106 9                 # kernel/include/vector_add.hpp:106:9
	mv	a0, zero
	lw	ra, 12(sp)
	addi	sp, sp, 16
	ret
.Ltmp307:
.Lfunc_end8:
	.size	_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj, .Lfunc_end8-_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj
	.cfi_endproc
                                        # -- End function
	.type	r_barrier,@object       # @r_barrier
	.section	.sbss,"aw",@nobits
	.globl	r_barrier
	.p2align	2
r_barrier:
	.zero	8
	.size	r_barrier, 8

	.type	c_barrier,@object       # @c_barrier
	.globl	c_barrier
	.p2align	2
c_barrier:
	.zero	8
	.size	c_barrier, 8

	.file	5 "/mnt/users/spin0/no_backup/eafurst/llvm-project/build/lib/clang/10.0.0/include/stdint.h"
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"clang version 10.0.0 (git@github.com:bespoke-silicon-group/llvm-project.git 3ee81f3def2c4c2a818f9f939f4421b3f3af313e)" # string offset=0
.Linfo_string1:
	.asciz	"kernel/v3/kernel.cpp"  # string offset=118
.Linfo_string2:
	.asciz	"/mnt/users/spin0/no_backup/eafurst/bsg_bladerunner/llvm-baseline/examples/vec_blocking" # string offset=139
.Linfo_string3:
	.asciz	"int"                   # string offset=226
.Linfo_string4:
	.asciz	"TA"                    # string offset=230
.Linfo_string5:
	.asciz	"TB"                    # string offset=233
.Linfo_string6:
	.asciz	"TC"                    # string offset=236
.Linfo_string7:
	.asciz	"_Z40kernel_vector_add_1D_grid_2D_tile_groupsIiiiEiPT_PT0_PT1_jj" # string offset=239
.Linfo_string8:
	.asciz	"kernel_vector_add_1D_grid_2D_tile_groups<int, int, int>" # string offset=303
.Linfo_string9:
	.asciz	"unsigned int"          # string offset=359
.Linfo_string10:
	.asciz	"short"                 # string offset=372
.Linfo_string11:
	.asciz	"_Z40kernel_vector_add_1D_grid_2D_tile_groupsIsssEiPT_PT0_PT1_jj" # string offset=378
.Linfo_string12:
	.asciz	"kernel_vector_add_1D_grid_2D_tile_groups<short, short, short>" # string offset=442
.Linfo_string13:
	.asciz	"signed char"           # string offset=504
.Linfo_string14:
	.asciz	"_Z40kernel_vector_add_1D_grid_2D_tile_groupsIaaaEiPT_PT0_PT1_jj" # string offset=516
.Linfo_string15:
	.asciz	"kernel_vector_add_1D_grid_2D_tile_groups<signed char, signed char, signed char>" # string offset=580
.Linfo_string16:
	.asciz	"float"                 # string offset=660
.Linfo_string17:
	.asciz	"_Z40kernel_vector_add_1D_grid_2D_tile_groupsIfffEiPT_PT0_PT1_jj" # string offset=666
.Linfo_string18:
	.asciz	"kernel_vector_add_1D_grid_2D_tile_groups<float, float, float>" # string offset=730
.Linfo_string19:
	.asciz	"r_barrier"             # string offset=792
.Linfo_string20:
	.asciz	"_x_cord_start"         # string offset=802
.Linfo_string21:
	.asciz	"unsigned char"         # string offset=816
.Linfo_string22:
	.asciz	"_x_cord_end"           # string offset=830
.Linfo_string23:
	.asciz	"_done_list"            # string offset=842
.Linfo_string24:
	.asciz	"__ARRAY_SIZE_TYPE__"   # string offset=853
.Linfo_string25:
	.asciz	"_local_alert"          # string offset=873
.Linfo_string26:
	.asciz	"_bsg_row_barrier_"     # string offset=886
.Linfo_string27:
	.asciz	"bsg_row_barrier"       # string offset=904
.Linfo_string28:
	.asciz	"c_barrier"             # string offset=920
.Linfo_string29:
	.asciz	"_y_cord_start"         # string offset=930
.Linfo_string30:
	.asciz	"_y_cord_end"           # string offset=944
.Linfo_string31:
	.asciz	"_bsg_col_barrier_"     # string offset=956
.Linfo_string32:
	.asciz	"bsg_col_barrier"       # string offset=974
.Linfo_string33:
	.asciz	"bsg_remote_int_ptr"    # string offset=990
.Linfo_string34:
	.asciz	"_Z20bsg_row_barrier_syncP17_bsg_row_barrier_i" # string offset=1009
.Linfo_string35:
	.asciz	"bsg_row_barrier_sync"  # string offset=1055
.Linfo_string36:
	.asciz	"p_row_b"               # string offset=1076
.Linfo_string37:
	.asciz	"center_x_cord"         # string offset=1084
.Linfo_string38:
	.asciz	"p_remote_barrier"      # string offset=1098
.Linfo_string39:
	.asciz	"i"                     # string offset=1115
.Linfo_string40:
	.asciz	"_Z20bsg_col_barrier_syncP17_bsg_row_barrier_P17_bsg_col_barrier_ii" # string offset=1117
.Linfo_string41:
	.asciz	"bsg_col_barrier_sync"  # string offset=1184
.Linfo_string42:
	.asciz	"p_col_b"               # string offset=1205
.Linfo_string43:
	.asciz	"center_y_cord"         # string offset=1213
.Linfo_string44:
	.asciz	"x_range"               # string offset=1227
.Linfo_string45:
	.asciz	"_Z10poll_rangeiPh"     # string offset=1235
.Linfo_string46:
	.asciz	"poll_range"            # string offset=1253
.Linfo_string47:
	.asciz	"range"                 # string offset=1264
.Linfo_string48:
	.asciz	"p"                     # string offset=1270
.Linfo_string49:
	.asciz	"_Z21bsg_col_barrier_alertP17_bsg_col_barrier_" # string offset=1272
.Linfo_string50:
	.asciz	"bsg_col_barrier_alert" # string offset=1318
.Linfo_string51:
	.asciz	"y_range"               # string offset=1340
.Linfo_string52:
	.asciz	"_Z9alert_colP17_bsg_col_barrier_" # string offset=1348
.Linfo_string53:
	.asciz	"alert_col"             # string offset=1381
.Linfo_string54:
	.asciz	"_Z21bsg_row_barrier_alertP17_bsg_row_barrier_P17_bsg_col_barrier_" # string offset=1391
.Linfo_string55:
	.asciz	"bsg_row_barrier_alert" # string offset=1457
.Linfo_string56:
	.asciz	"_Z6bsg_lrPi"           # string offset=1479
.Linfo_string57:
	.asciz	"bsg_lr"                # string offset=1491
.Linfo_string58:
	.asciz	"tmp"                   # string offset=1498
.Linfo_string59:
	.asciz	"_Z18bsg_wait_local_intPii" # string offset=1502
.Linfo_string60:
	.asciz	"bsg_wait_local_int"    # string offset=1528
.Linfo_string61:
	.asciz	"ptr"                   # string offset=1547
.Linfo_string62:
	.asciz	"cond"                  # string offset=1551
.Linfo_string63:
	.asciz	"_Z9bsg_lr_aqPi"        # string offset=1556
.Linfo_string64:
	.asciz	"bsg_lr_aq"             # string offset=1571
.Linfo_string65:
	.asciz	"_Z9alert_rowP17_bsg_row_barrier_" # string offset=1581
.Linfo_string66:
	.asciz	"alert_row"             # string offset=1614
.Linfo_string67:
	.asciz	"_Z13bsg_tile_waitP17_bsg_row_barrier_" # string offset=1624
.Linfo_string68:
	.asciz	"bsg_tile_wait"         # string offset=1662
.Linfo_string69:
	.asciz	"_Z22bsg_tile_group_barrierP17_bsg_row_barrier_P17_bsg_col_barrier_" # string offset=1676
.Linfo_string70:
	.asciz	"bsg_tile_group_barrier" # string offset=1743
.Linfo_string71:
	.asciz	"kernel_vector_add_int" # string offset=1766
.Linfo_string72:
	.asciz	"kernel_vector_add_int16" # string offset=1788
.Linfo_string73:
	.asciz	"kernel_vector_add_int8" # string offset=1812
.Linfo_string74:
	.asciz	"kernel_vector_add_float" # string offset=1835
.Linfo_string75:
	.asciz	"A"                     # string offset=1859
.Linfo_string76:
	.asciz	"B"                     # string offset=1861
.Linfo_string77:
	.asciz	"C"                     # string offset=1863
.Linfo_string78:
	.asciz	"WIDTH"                 # string offset=1865
.Linfo_string79:
	.asciz	"uint32_t"              # string offset=1871
.Linfo_string80:
	.asciz	"block_size_y"          # string offset=1880
.Linfo_string81:
	.asciz	"block_size_x"          # string offset=1893
.Linfo_string82:
	.asciz	"tag"                   # string offset=1906
.Linfo_string83:
	.asciz	"iter"                  # string offset=1910
.Linfo_string84:
	.asciz	"val"                   # string offset=1915
.Linfo_string85:
	.asciz	"rc"                    # string offset=1919
.Linfo_string86:
	.asciz	"start"                 # string offset=1922
.Linfo_string87:
	.asciz	"end"                   # string offset=1928
.Linfo_string88:
	.asciz	"iter_x"                # string offset=1932
.Linfo_string89:
	.asciz	"int16_t"               # string offset=1939
.Linfo_string90:
	.asciz	"int8_t"                # string offset=1947
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin0-.Lfunc_begin0
	.word	.Ltmp0-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp0-.Lfunc_begin0
	.word	.Ltmp78-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc1:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin0-.Lfunc_begin0
	.word	.Ltmp1-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp1-.Lfunc_begin0
	.word	.Ltmp76-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	99                      # DW_OP_reg19
	.word	0
	.word	0
.Ldebug_loc2:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp3-.Lfunc_begin0
	.word	.Ltmp77-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	98                      # DW_OP_reg18
	.word	0
	.word	0
.Ldebug_loc3:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp7-.Lfunc_begin0
	.word	.Ltmp8-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc4:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp11-.Lfunc_begin0
	.word	.Ltmp12-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	98                      # DW_OP_reg18
	.word	0
	.word	0
.Ldebug_loc5:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp11-.Lfunc_begin0
	.word	.Ltmp12-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc6:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp11-.Lfunc_begin0
	.word	.Ltmp27-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc7:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc8:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	99                      # DW_OP_reg19
	.word	0
	.word	0
.Ldebug_loc9:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	98                      # DW_OP_reg18
	.word	0
	.word	0
.Ldebug_loc10:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp12-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc11:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp13-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc12:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp24-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc13:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp16-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp17-.Lfunc_begin0
	.word	.Ltmp18-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	.Ltmp18-.Lfunc_begin0
	.word	.Ltmp21-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	121                     # DW_OP_breg9
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp21-.Lfunc_begin0
	.word	.Ltmp22-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc14:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp22-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	2                       # 2
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc15:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp14-.Lfunc_begin0
	.word	.Ltmp22-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc16:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp26-.Lfunc_begin0
	.word	.Ltmp49-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	99                      # DW_OP_reg19
	.word	0
	.word	0
.Ldebug_loc17:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp28-.Lfunc_begin0
	.word	.Ltmp30-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp31-.Lfunc_begin0
	.word	.Ltmp32-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	.Ltmp32-.Lfunc_begin0
	.word	.Ltmp35-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	126                     # DW_OP_breg14
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	.Ltmp35-.Lfunc_begin0
	.word	.Ltmp36-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc18:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp28-.Lfunc_begin0
	.word	.Ltmp36-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	131                     # DW_OP_breg19
	.byte	2                       # 2
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc19:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp28-.Lfunc_begin0
	.word	.Ltmp36-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc20:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp28-.Lfunc_begin0
	.word	.Ltmp47-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc21:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp36-.Lfunc_begin0
	.word	.Ltmp44-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	99                      # DW_OP_reg19
	.word	0
	.word	0
.Ldebug_loc22:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp36-.Lfunc_begin0
	.word	.Ltmp39-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc23:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp41-.Lfunc_begin0
	.word	.Ltmp44-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	89                      # DW_OP_reg9
	.word	0
	.word	0
.Ldebug_loc24:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp44-.Lfunc_begin0
	.word	.Ltmp48-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc25:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp50-.Lfunc_begin0
	.word	.Ltmp69-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc26:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp50-.Lfunc_begin0
	.word	.Ltmp69-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	99                      # DW_OP_reg19
	.word	0
	.word	0
.Ldebug_loc27:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp51-.Lfunc_begin0
	.word	.Ltmp56-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc28:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp51-.Lfunc_begin0
	.word	.Ltmp56-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	131                     # DW_OP_breg19
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc29:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp52-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	131                     # DW_OP_breg19
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc30:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp53-.Lfunc_begin0
	.word	.Ltmp56-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc31:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp53-.Lfunc_begin0
	.word	.Ltmp54-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc32:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp54-.Lfunc_begin0
	.word	.Ltmp56-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	131                     # DW_OP_breg19
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc33:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp55-.Lfunc_begin0
	.word	.Ltmp56-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc34:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp56-.Lfunc_begin0
	.word	.Ltmp65-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc35:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp57-.Lfunc_begin0
	.word	.Ltmp61-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc36:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp62-.Lfunc_begin0
	.word	.Ltmp65-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc37:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp65-.Lfunc_begin0
	.word	.Ltmp69-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc38:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp69-.Lfunc_begin0
	.word	.Ltmp78-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	88                      # DW_OP_reg8
	.word	0
	.word	0
.Ldebug_loc39:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp69-.Lfunc_begin0
	.word	.Ltmp74-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc40:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp69-.Lfunc_begin0
	.word	.Ltmp74-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	1                       # 1
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc41:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp70-.Lfunc_begin0
	.word	.Ltmp72-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc42:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp71-.Lfunc_begin0
	.word	.Ltmp74-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc43:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp71-.Lfunc_begin0
	.word	.Ltmp72-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc44:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp72-.Lfunc_begin0
	.word	.Ltmp74-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	120                     # DW_OP_breg8
	.byte	4                       # 4
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc45:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp73-.Lfunc_begin0
	.word	.Ltmp74-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc46:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp90-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp90-.Lfunc_begin0
	.word	.Ltmp111-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	0
	.word	0
.Ldebug_loc47:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp89-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp89-.Lfunc_begin0
	.word	.Ltmp112-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	101                     # DW_OP_reg21
	.word	0
	.word	0
.Ldebug_loc48:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp88-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	.Ltmp88-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	0                       # 0
	.word	0
	.word	0
.Ldebug_loc49:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp87-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	.Ltmp87-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	4                       # 4
	.word	0
	.word	0
.Ldebug_loc50:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp81-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc51:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp86-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	.Ltmp86-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	8                       # 8
	.word	0
	.word	0
.Ldebug_loc52:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp94-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc53:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin1-.Lfunc_begin0
	.word	.Ltmp94-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	97                      # DW_OP_reg17
	.word	0
	.word	0
.Ldebug_loc54:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp82-.Lfunc_begin0
	.word	.Ltmp85-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc55:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp103-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc56:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp91-.Lfunc_begin0
	.word	.Ltmp94-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc57:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp95-.Lfunc_begin0
	.word	.Ltmp97-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc58:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp100-.Lfunc_begin0
	.word	.Ltmp102-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc59:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp108-.Lfunc_begin0
	.word	.Lfunc_end1-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc60:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Lfunc_begin2-.Lfunc_begin2
	.word	.Ltmp131-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc61:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Lfunc_begin2-.Lfunc_begin2
	.word	.Ltmp130-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc62:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Lfunc_begin2-.Lfunc_begin2
	.word	.Ltmp129-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc63:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Lfunc_begin2-.Lfunc_begin2
	.word	.Ltmp115-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc64:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Lfunc_begin2-.Lfunc_begin2
	.word	.Ltmp124-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc65:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Ltmp118-.Lfunc_begin2
	.word	.Ltmp122-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc66:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Ltmp119-.Lfunc_begin2
	.word	.Ltmp131-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc67:
	.word	-1
	.word	.Lfunc_begin2           #   base address
	.word	.Ltmp120-.Lfunc_begin2
	.word	.Ltmp131-.Lfunc_begin2
	.half	1                       # Loc expr size
	.byte	85                      # DW_OP_reg5
	.word	0
	.word	0
.Ldebug_loc68:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp147-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp147-.Lfunc_begin0
	.word	.Ltmp168-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	0
	.word	0
.Ldebug_loc69:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp146-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp146-.Lfunc_begin0
	.word	.Ltmp169-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	101                     # DW_OP_reg21
	.word	0
	.word	0
.Ldebug_loc70:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp145-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	.Ltmp145-.Lfunc_begin0
	.word	.Lfunc_end3-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	0                       # 0
	.word	0
	.word	0
.Ldebug_loc71:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp144-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	.Ltmp144-.Lfunc_begin0
	.word	.Lfunc_end3-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	4                       # 4
	.word	0
	.word	0
.Ldebug_loc72:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp138-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc73:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp143-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	.Ltmp143-.Lfunc_begin0
	.word	.Lfunc_end3-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	8                       # 8
	.word	0
	.word	0
.Ldebug_loc74:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp151-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc75:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin3-.Lfunc_begin0
	.word	.Ltmp151-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	97                      # DW_OP_reg17
	.word	0
	.word	0
.Ldebug_loc76:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp139-.Lfunc_begin0
	.word	.Ltmp142-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc77:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp160-.Lfunc_begin0
	.word	.Lfunc_end3-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc78:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp148-.Lfunc_begin0
	.word	.Ltmp151-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc79:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp152-.Lfunc_begin0
	.word	.Ltmp154-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc80:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp157-.Lfunc_begin0
	.word	.Ltmp159-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc81:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp165-.Lfunc_begin0
	.word	.Lfunc_end3-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc82:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Lfunc_begin4-.Lfunc_begin4
	.word	.Ltmp188-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc83:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Lfunc_begin4-.Lfunc_begin4
	.word	.Ltmp187-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc84:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Lfunc_begin4-.Lfunc_begin4
	.word	.Ltmp186-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc85:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Lfunc_begin4-.Lfunc_begin4
	.word	.Ltmp172-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc86:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Lfunc_begin4-.Lfunc_begin4
	.word	.Ltmp181-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc87:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Ltmp175-.Lfunc_begin4
	.word	.Ltmp179-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc88:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Ltmp176-.Lfunc_begin4
	.word	.Ltmp188-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc89:
	.word	-1
	.word	.Lfunc_begin4           #   base address
	.word	.Ltmp177-.Lfunc_begin4
	.word	.Ltmp188-.Lfunc_begin4
	.half	1                       # Loc expr size
	.byte	85                      # DW_OP_reg5
	.word	0
	.word	0
.Ldebug_loc90:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp204-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp204-.Lfunc_begin0
	.word	.Ltmp225-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	0
	.word	0
.Ldebug_loc91:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp203-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp203-.Lfunc_begin0
	.word	.Ltmp226-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	101                     # DW_OP_reg21
	.word	0
	.word	0
.Ldebug_loc92:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp202-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	.Ltmp202-.Lfunc_begin0
	.word	.Lfunc_end5-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	0                       # 0
	.word	0
	.word	0
.Ldebug_loc93:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp201-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	.Ltmp201-.Lfunc_begin0
	.word	.Lfunc_end5-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	4                       # 4
	.word	0
	.word	0
.Ldebug_loc94:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp195-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc95:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp200-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	.Ltmp200-.Lfunc_begin0
	.word	.Lfunc_end5-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	8                       # 8
	.word	0
	.word	0
.Ldebug_loc96:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp208-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc97:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin5-.Lfunc_begin0
	.word	.Ltmp208-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	97                      # DW_OP_reg17
	.word	0
	.word	0
.Ldebug_loc98:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp196-.Lfunc_begin0
	.word	.Ltmp199-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc99:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp217-.Lfunc_begin0
	.word	.Lfunc_end5-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc100:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp205-.Lfunc_begin0
	.word	.Ltmp208-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc101:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp209-.Lfunc_begin0
	.word	.Ltmp211-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc102:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp214-.Lfunc_begin0
	.word	.Ltmp216-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc103:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp222-.Lfunc_begin0
	.word	.Lfunc_end5-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc104:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Lfunc_begin6-.Lfunc_begin6
	.word	.Ltmp244-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc105:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Lfunc_begin6-.Lfunc_begin6
	.word	.Ltmp243-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc106:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Lfunc_begin6-.Lfunc_begin6
	.word	.Ltmp242-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc107:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Lfunc_begin6-.Lfunc_begin6
	.word	.Ltmp229-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc108:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Lfunc_begin6-.Lfunc_begin6
	.word	.Ltmp236-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc109:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Ltmp232-.Lfunc_begin6
	.word	.Ltmp234-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc110:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Ltmp233-.Lfunc_begin6
	.word	.Ltmp244-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc111:
	.word	-1
	.word	.Lfunc_begin6           #   base address
	.word	.Ltmp234-.Lfunc_begin6
	.word	.Ltmp244-.Lfunc_begin6
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc112:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp260-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	.Ltmp260-.Lfunc_begin0
	.word	.Ltmp281-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	106                     # DW_OP_reg26
	.word	0
	.word	0
.Ldebug_loc113:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp259-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	.Ltmp259-.Lfunc_begin0
	.word	.Ltmp282-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	101                     # DW_OP_reg21
	.word	0
	.word	0
.Ldebug_loc114:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp258-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	.Ltmp258-.Lfunc_begin0
	.word	.Lfunc_end7-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	0                       # 0
	.word	0
	.word	0
.Ldebug_loc115:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp257-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	.Ltmp257-.Lfunc_begin0
	.word	.Lfunc_end7-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	4                       # 4
	.word	0
	.word	0
.Ldebug_loc116:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp251-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc117:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp256-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	.Ltmp256-.Lfunc_begin0
	.word	.Lfunc_end7-.Lfunc_begin0
	.half	2                       # Loc expr size
	.byte	114                     # DW_OP_breg2
	.byte	8                       # 8
	.word	0
	.word	0
.Ldebug_loc118:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp264-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc119:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Lfunc_begin7-.Lfunc_begin0
	.word	.Ltmp264-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	97                      # DW_OP_reg17
	.word	0
	.word	0
.Ldebug_loc120:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp252-.Lfunc_begin0
	.word	.Ltmp255-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc121:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp273-.Lfunc_begin0
	.word	.Lfunc_end7-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc122:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp261-.Lfunc_begin0
	.word	.Ltmp264-.Lfunc_begin0
	.half	3                       # Loc expr size
	.byte	17                      # DW_OP_consts
	.byte	0                       # 0
	.byte	159                     # DW_OP_stack_value
	.word	0
	.word	0
.Ldebug_loc123:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp265-.Lfunc_begin0
	.word	.Ltmp267-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc124:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp270-.Lfunc_begin0
	.word	.Ltmp272-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc125:
	.word	-1
	.word	.Lfunc_begin0           #   base address
	.word	.Ltmp278-.Lfunc_begin0
	.word	.Lfunc_end7-.Lfunc_begin0
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc126:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Lfunc_begin8-.Lfunc_begin8
	.word	.Ltmp302-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	90                      # DW_OP_reg10
	.word	0
	.word	0
.Ldebug_loc127:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Lfunc_begin8-.Lfunc_begin8
	.word	.Ltmp301-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	91                      # DW_OP_reg11
	.word	0
	.word	0
.Ldebug_loc128:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Lfunc_begin8-.Lfunc_begin8
	.word	.Ltmp300-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	92                      # DW_OP_reg12
	.word	0
	.word	0
.Ldebug_loc129:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Lfunc_begin8-.Lfunc_begin8
	.word	.Ltmp285-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	93                      # DW_OP_reg13
	.word	0
	.word	0
.Ldebug_loc130:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Lfunc_begin8-.Lfunc_begin8
	.word	.Ltmp294-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	94                      # DW_OP_reg14
	.word	0
	.word	0
.Ldebug_loc131:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Ltmp288-.Lfunc_begin8
	.word	.Ltmp292-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	95                      # DW_OP_reg15
	.word	0
	.word	0
.Ldebug_loc132:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Ltmp289-.Lfunc_begin8
	.word	.Ltmp306-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	96                      # DW_OP_reg16
	.word	0
	.word	0
.Ldebug_loc133:
	.word	-1
	.word	.Lfunc_begin8           #   base address
	.word	.Ltmp290-.Lfunc_begin8
	.word	.Ltmp302-.Lfunc_begin8
	.half	1                       # Loc expr size
	.byte	85                      # DW_OP_reg5
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
	.byte	85                      # DW_AT_ranges
	.byte	23                      # DW_FORM_sec_offset
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
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
	.byte	3                       # Abbreviation Code
	.byte	47                      # DW_TAG_template_type_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
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
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	2                       # DW_AT_location
	.byte	24                      # DW_FORM_exprloc
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
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
	.byte	9                       # Abbreviation Code
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
	.byte	10                      # Abbreviation Code
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
	.byte	11                      # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	12                      # Abbreviation Code
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
	.byte	13                      # Abbreviation Code
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
	.byte	14                      # Abbreviation Code
	.byte	53                      # DW_TAG_volatile_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	15                      # Abbreviation Code
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
	.byte	16                      # Abbreviation Code
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
	.byte	17                      # Abbreviation Code
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
	.byte	18                      # Abbreviation Code
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
	.byte	19                      # Abbreviation Code
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
	.byte	20                      # Abbreviation Code
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
	.byte	21                      # Abbreviation Code
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
	.byte	22                      # Abbreviation Code
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
	.byte	23                      # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	24                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	2                       # DW_AT_location
	.byte	23                      # DW_FORM_sec_offset
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	25                      # Abbreviation Code
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
	.byte	26                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	27                      # Abbreviation Code
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
	.byte	28                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	85                      # DW_AT_ranges
	.byte	23                      # DW_FORM_sec_offset
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	29                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	30                      # Abbreviation Code
	.ascii	"\211\202\001"          # DW_TAG_GNU_call_site
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	31                      # Abbreviation Code
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
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	32                      # Abbreviation Code
	.byte	55                      # DW_TAG_restrict_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
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
	.byte	1                       # Abbrev [1] 0xb:0x101b DW_TAG_compile_unit
	.word	.Linfo_string0          # DW_AT_producer
	.half	26                      # DW_AT_language
	.word	.Linfo_string1          # DW_AT_name
	.word	.Lline_table_start0     # DW_AT_stmt_list
	.word	.Linfo_string2          # DW_AT_comp_dir
	.word	0                       # DW_AT_low_pc
	.word	.Ldebug_ranges17        # DW_AT_ranges
	.byte	2                       # Abbrev [2] 0x26:0x44 DW_TAG_subprogram
	.word	.Linfo_string7          # DW_AT_linkage_name
	.word	.Linfo_string8          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0x35:0x9 DW_TAG_template_type_parameter
	.word	106                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x3e:0x9 DW_TAG_template_type_parameter
	.word	106                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x47:0x9 DW_TAG_template_type_parameter
	.word	106                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	4                       # Abbrev [4] 0x50:0x5 DW_TAG_formal_parameter
	.word	113                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x55:0x5 DW_TAG_formal_parameter
	.word	113                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x5a:0x5 DW_TAG_formal_parameter
	.word	113                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x5f:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x64:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x6a:0x7 DW_TAG_base_type
	.word	.Linfo_string3          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	6                       # Abbrev [6] 0x71:0x5 DW_TAG_pointer_type
	.word	106                     # DW_AT_type
	.byte	5                       # Abbrev [5] 0x76:0x7 DW_TAG_base_type
	.word	.Linfo_string9          # DW_AT_name
	.byte	7                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	2                       # Abbrev [2] 0x7d:0x44 DW_TAG_subprogram
	.word	.Linfo_string11         # DW_AT_linkage_name
	.word	.Linfo_string12         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0x8c:0x9 DW_TAG_template_type_parameter
	.word	193                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x95:0x9 DW_TAG_template_type_parameter
	.word	193                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x9e:0x9 DW_TAG_template_type_parameter
	.word	193                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	4                       # Abbrev [4] 0xa7:0x5 DW_TAG_formal_parameter
	.word	200                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0xac:0x5 DW_TAG_formal_parameter
	.word	200                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0xb1:0x5 DW_TAG_formal_parameter
	.word	200                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0xb6:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0xbb:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0xc1:0x7 DW_TAG_base_type
	.word	.Linfo_string10         # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	2                       # DW_AT_byte_size
	.byte	6                       # Abbrev [6] 0xc8:0x5 DW_TAG_pointer_type
	.word	193                     # DW_AT_type
	.byte	2                       # Abbrev [2] 0xcd:0x44 DW_TAG_subprogram
	.word	.Linfo_string14         # DW_AT_linkage_name
	.word	.Linfo_string15         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0xdc:0x9 DW_TAG_template_type_parameter
	.word	273                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xe5:0x9 DW_TAG_template_type_parameter
	.word	273                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xee:0x9 DW_TAG_template_type_parameter
	.word	273                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	4                       # Abbrev [4] 0xf7:0x5 DW_TAG_formal_parameter
	.word	280                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0xfc:0x5 DW_TAG_formal_parameter
	.word	280                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x101:0x5 DW_TAG_formal_parameter
	.word	280                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x106:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x10b:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x111:0x7 DW_TAG_base_type
	.word	.Linfo_string13         # DW_AT_name
	.byte	6                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	6                       # Abbrev [6] 0x118:0x5 DW_TAG_pointer_type
	.word	273                     # DW_AT_type
	.byte	2                       # Abbrev [2] 0x11d:0x44 DW_TAG_subprogram
	.word	.Linfo_string17         # DW_AT_linkage_name
	.word	.Linfo_string18         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_declaration
                                        # DW_AT_external
	.byte	3                       # Abbrev [3] 0x12c:0x9 DW_TAG_template_type_parameter
	.word	353                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x135:0x9 DW_TAG_template_type_parameter
	.word	353                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x13e:0x9 DW_TAG_template_type_parameter
	.word	353                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	4                       # Abbrev [4] 0x147:0x5 DW_TAG_formal_parameter
	.word	360                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x14c:0x5 DW_TAG_formal_parameter
	.word	360                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x151:0x5 DW_TAG_formal_parameter
	.word	360                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x156:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	4                       # Abbrev [4] 0x15b:0x5 DW_TAG_formal_parameter
	.word	118                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x161:0x7 DW_TAG_base_type
	.word	.Linfo_string16         # DW_AT_name
	.byte	4                       # DW_AT_encoding
	.byte	4                       # DW_AT_byte_size
	.byte	6                       # Abbrev [6] 0x168:0x5 DW_TAG_pointer_type
	.word	353                     # DW_AT_type
	.byte	7                       # Abbrev [7] 0x16d:0x11 DW_TAG_variable
	.word	.Linfo_string19         # DW_AT_name
	.word	382                     # DW_AT_type
                                        # DW_AT_external
	.byte	3                       # DW_AT_decl_file
	.byte	18                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.word	r_barrier
	.byte	8                       # Abbrev [8] 0x17e:0xb DW_TAG_typedef
	.word	393                     # DW_AT_type
	.word	.Linfo_string27         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x189:0x3a DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.word	.Linfo_string26         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	43                      # DW_AT_decl_line
	.byte	10                      # Abbrev [10] 0x192:0xc DW_TAG_member
	.word	.Linfo_string20         # DW_AT_name
	.word	451                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	44                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	10                      # Abbrev [10] 0x19e:0xc DW_TAG_member
	.word	.Linfo_string22         # DW_AT_name
	.word	451                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	45                      # DW_AT_decl_line
	.byte	1                       # DW_AT_data_member_location
	.byte	10                      # Abbrev [10] 0x1aa:0xc DW_TAG_member
	.word	.Linfo_string23         # DW_AT_name
	.word	458                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	46                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	10                      # Abbrev [10] 0x1b6:0xc DW_TAG_member
	.word	.Linfo_string25         # DW_AT_name
	.word	118                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	5                       # Abbrev [5] 0x1c3:0x7 DW_TAG_base_type
	.word	.Linfo_string21         # DW_AT_name
	.byte	8                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	11                      # Abbrev [11] 0x1ca:0xd DW_TAG_array_type
	.word	451                     # DW_AT_type
	.byte	12                      # Abbrev [12] 0x1cf:0x7 DW_TAG_subrange_type
	.word	471                     # DW_AT_type
	.byte	0                       # DW_AT_lower_bound
	.byte	1                       # DW_AT_count
	.byte	0                       # End Of Children Mark
	.byte	13                      # Abbrev [13] 0x1d7:0x7 DW_TAG_base_type
	.word	.Linfo_string24         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	7                       # DW_AT_encoding
	.byte	7                       # Abbrev [7] 0x1de:0x11 DW_TAG_variable
	.word	.Linfo_string28         # DW_AT_name
	.word	495                     # DW_AT_type
                                        # DW_AT_external
	.byte	3                       # DW_AT_decl_file
	.byte	18                      # DW_AT_decl_line
	.byte	5                       # DW_AT_location
	.byte	3
	.word	c_barrier
	.byte	8                       # Abbrev [8] 0x1ef:0xb DW_TAG_typedef
	.word	506                     # DW_AT_type
	.word	.Linfo_string32         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.byte	9                       # Abbrev [9] 0x1fa:0x3a DW_TAG_structure_type
	.byte	5                       # DW_AT_calling_convention
	.word	.Linfo_string31         # DW_AT_name
	.byte	8                       # DW_AT_byte_size
	.byte	2                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.byte	10                      # Abbrev [10] 0x203:0xc DW_TAG_member
	.word	.Linfo_string29         # DW_AT_name
	.word	451                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.byte	0                       # DW_AT_data_member_location
	.byte	10                      # Abbrev [10] 0x20f:0xc DW_TAG_member
	.word	.Linfo_string30         # DW_AT_name
	.word	451                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.byte	1                       # DW_AT_data_member_location
	.byte	10                      # Abbrev [10] 0x21b:0xc DW_TAG_member
	.word	.Linfo_string23         # DW_AT_name
	.word	458                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.byte	2                       # DW_AT_data_member_location
	.byte	10                      # Abbrev [10] 0x227:0xc DW_TAG_member
	.word	.Linfo_string25         # DW_AT_name
	.word	118                     # DW_AT_type
	.byte	2                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.byte	4                       # DW_AT_data_member_location
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x234:0xb DW_TAG_typedef
	.word	575                     # DW_AT_type
	.word	.Linfo_string33         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	16                      # DW_AT_decl_line
	.byte	6                       # Abbrev [6] 0x23f:0x5 DW_TAG_pointer_type
	.word	580                     # DW_AT_type
	.byte	14                      # Abbrev [14] 0x244:0x5 DW_TAG_volatile_type
	.word	106                     # DW_AT_type
	.byte	6                       # Abbrev [6] 0x249:0x5 DW_TAG_pointer_type
	.word	382                     # DW_AT_type
	.byte	6                       # Abbrev [6] 0x24e:0x5 DW_TAG_pointer_type
	.word	495                     # DW_AT_type
	.byte	15                      # Abbrev [15] 0x253:0x39 DW_TAG_subprogram
	.word	.Linfo_string34         # DW_AT_linkage_name
	.word	.Linfo_string35         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x25f:0xb DW_TAG_formal_parameter
	.word	.Linfo_string36         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x26a:0xb DW_TAG_formal_parameter
	.word	.Linfo_string37         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x275:0xb DW_TAG_variable
	.word	.Linfo_string38         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x280:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	91                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x28c:0x5a DW_TAG_subprogram
	.word	.Linfo_string40         # DW_AT_linkage_name
	.word	.Linfo_string41         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x298:0xb DW_TAG_formal_parameter
	.word	.Linfo_string36         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x2a3:0xb DW_TAG_formal_parameter
	.word	.Linfo_string42         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x2ae:0xb DW_TAG_formal_parameter
	.word	.Linfo_string37         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x2b9:0xb DW_TAG_formal_parameter
	.word	.Linfo_string43         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x2c4:0xb DW_TAG_variable
	.word	.Linfo_string44         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	106                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x2cf:0xb DW_TAG_variable
	.word	.Linfo_string38         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x2da:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	102                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x2e6:0x2e DW_TAG_subprogram
	.word	.Linfo_string45         # DW_AT_linkage_name
	.word	.Linfo_string46         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	205                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x2f2:0xb DW_TAG_formal_parameter
	.word	.Linfo_string47         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	205                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x2fd:0xb DW_TAG_formal_parameter
	.word	.Linfo_string48         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	205                     # DW_AT_decl_line
	.word	788                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x308:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	206                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	6                       # Abbrev [6] 0x314:0x5 DW_TAG_pointer_type
	.word	451                     # DW_AT_type
	.byte	15                      # Abbrev [15] 0x319:0x2e DW_TAG_subprogram
	.word	.Linfo_string49         # DW_AT_linkage_name
	.word	.Linfo_string50         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	119                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x325:0xb DW_TAG_formal_parameter
	.word	.Linfo_string42         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	119                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x330:0xb DW_TAG_variable
	.word	.Linfo_string51         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	122                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x33b:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	121                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x347:0x2e DW_TAG_subprogram
	.word	.Linfo_string52         # DW_AT_linkage_name
	.word	.Linfo_string53         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	214                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x353:0xb DW_TAG_formal_parameter
	.word	.Linfo_string42         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	214                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x35e:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	215                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x369:0xb DW_TAG_variable
	.word	.Linfo_string38         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	216                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x375:0x39 DW_TAG_subprogram
	.word	.Linfo_string54         # DW_AT_linkage_name
	.word	.Linfo_string55         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	140                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x381:0xb DW_TAG_formal_parameter
	.word	.Linfo_string36         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	140                     # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x38c:0xb DW_TAG_formal_parameter
	.word	.Linfo_string42         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	140                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x397:0xb DW_TAG_variable
	.word	.Linfo_string44         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	142                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x3a2:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	141                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	18                      # Abbrev [18] 0x3ae:0x27 DW_TAG_subprogram
	.word	.Linfo_string56         # DW_AT_linkage_name
	.word	.Linfo_string57         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	111                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x3be:0xb DW_TAG_formal_parameter
	.word	.Linfo_string48         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	111                     # DW_AT_decl_line
	.word	113                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x3c9:0xb DW_TAG_variable
	.word	.Linfo_string58         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	111                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	18                      # Abbrev [18] 0x3d5:0x32 DW_TAG_subprogram
	.word	.Linfo_string59         # DW_AT_linkage_name
	.word	.Linfo_string60         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	237                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x3e5:0xb DW_TAG_formal_parameter
	.word	.Linfo_string61         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	237                     # DW_AT_decl_line
	.word	113                     # DW_AT_type
	.byte	16                      # Abbrev [16] 0x3f0:0xb DW_TAG_formal_parameter
	.word	.Linfo_string62         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	237                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x3fb:0xb DW_TAG_variable
	.word	.Linfo_string58         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	238                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	18                      # Abbrev [18] 0x407:0x27 DW_TAG_subprogram
	.word	.Linfo_string63         # DW_AT_linkage_name
	.word	.Linfo_string64         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x417:0xb DW_TAG_formal_parameter
	.word	.Linfo_string48         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.word	113                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x422:0xb DW_TAG_variable
	.word	.Linfo_string58         # DW_AT_name
	.byte	4                       # DW_AT_decl_file
	.byte	112                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x42e:0x2e DW_TAG_subprogram
	.word	.Linfo_string65         # DW_AT_linkage_name
	.word	.Linfo_string66         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	225                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x43a:0xb DW_TAG_formal_parameter
	.word	.Linfo_string36         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	225                     # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x445:0xb DW_TAG_variable
	.word	.Linfo_string39         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	226                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	17                      # Abbrev [17] 0x450:0xb DW_TAG_variable
	.word	.Linfo_string38         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	227                     # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	15                      # Abbrev [15] 0x45c:0x18 DW_TAG_subprogram
	.word	.Linfo_string67         # DW_AT_linkage_name
	.word	.Linfo_string68         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	163                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	1                       # DW_AT_inline
	.byte	16                      # Abbrev [16] 0x468:0xb DW_TAG_formal_parameter
	.word	.Linfo_string36         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	163                     # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	19                      # Abbrev [19] 0x474:0x2cc DW_TAG_subprogram
	.word	.Lfunc_begin0           # DW_AT_low_pc
	.word	.Lfunc_end0-.Lfunc_begin0 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string69         # DW_AT_linkage_name
	.word	.Linfo_string70         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	172                     # DW_AT_decl_line
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0x489:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc0            # DW_AT_location
	.word	.Linfo_string36         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	172                     # DW_AT_decl_line
	.word	585                     # DW_AT_type
	.byte	20                      # Abbrev [20] 0x498:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc1            # DW_AT_location
	.word	.Linfo_string42         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	172                     # DW_AT_decl_line
	.word	590                     # DW_AT_type
	.byte	21                      # Abbrev [21] 0x4a7:0xf DW_TAG_variable
	.word	.Ldebug_loc2            # DW_AT_location
	.word	.Linfo_string37         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	173                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	21                      # Abbrev [21] 0x4b6:0xf DW_TAG_variable
	.word	.Ldebug_loc6            # DW_AT_location
	.word	.Linfo_string43         # DW_AT_name
	.byte	2                       # DW_AT_decl_file
	.byte	175                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	22                      # Abbrev [22] 0x4c5:0x28 DW_TAG_inlined_subroutine
	.word	595                     # DW_AT_abstract_origin
	.word	.Ldebug_ranges0         # DW_AT_ranges
	.byte	2                       # DW_AT_call_file
	.byte	183                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x4d1:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc5            # DW_AT_location
	.word	607                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x4da:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc4            # DW_AT_location
	.word	618                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x4e3:0x9 DW_TAG_variable
	.word	.Ldebug_loc3            # DW_AT_location
	.word	629                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x4ed:0x73 DW_TAG_inlined_subroutine
	.word	652                     # DW_AT_abstract_origin
	.word	.Ltmp12                 # DW_AT_low_pc
	.word	.Ltmp23-.Ltmp12         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	187                     # DW_AT_call_line
	.byte	17                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x4fd:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc7            # DW_AT_location
	.word	664                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x506:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc8            # DW_AT_location
	.word	675                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x50f:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc9            # DW_AT_location
	.word	686                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x518:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc10           # DW_AT_location
	.word	697                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x521:0x9 DW_TAG_variable
	.word	.Ldebug_loc11           # DW_AT_location
	.word	708                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x52a:0x9 DW_TAG_variable
	.word	.Ldebug_loc12           # DW_AT_location
	.word	719                     # DW_AT_abstract_origin
	.byte	25                      # Abbrev [25] 0x533:0x2c DW_TAG_inlined_subroutine
	.word	742                     # DW_AT_abstract_origin
	.word	.Ltmp14                 # DW_AT_low_pc
	.word	.Ltmp22-.Ltmp14         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	107                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x543:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc15           # DW_AT_location
	.word	754                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x54c:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc14           # DW_AT_location
	.word	765                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x555:0x9 DW_TAG_variable
	.word	.Ldebug_loc13           # DW_AT_location
	.word	776                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x560:0x84 DW_TAG_inlined_subroutine
	.word	793                     # DW_AT_abstract_origin
	.word	.Ltmp26                 # DW_AT_low_pc
	.word	.Ltmp48-.Ltmp26         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	190                     # DW_AT_call_line
	.byte	17                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x570:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc16           # DW_AT_location
	.word	805                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x579:0x9 DW_TAG_variable
	.word	.Ldebug_loc20           # DW_AT_location
	.word	816                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x582:0x9 DW_TAG_variable
	.word	.Ldebug_loc24           # DW_AT_location
	.word	827                     # DW_AT_abstract_origin
	.byte	25                      # Abbrev [25] 0x58b:0x2c DW_TAG_inlined_subroutine
	.word	742                     # DW_AT_abstract_origin
	.word	.Ltmp28                 # DW_AT_low_pc
	.word	.Ltmp36-.Ltmp28         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	123                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x59b:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc19           # DW_AT_location
	.word	754                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x5a4:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc18           # DW_AT_location
	.word	765                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x5ad:0x9 DW_TAG_variable
	.word	.Ldebug_loc17           # DW_AT_location
	.word	776                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x5b7:0x2c DW_TAG_inlined_subroutine
	.word	839                     # DW_AT_abstract_origin
	.word	.Ltmp36                 # DW_AT_low_pc
	.word	.Ltmp44-.Ltmp36         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	129                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x5c7:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc21           # DW_AT_location
	.word	851                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x5d0:0x9 DW_TAG_variable
	.word	.Ldebug_loc22           # DW_AT_location
	.word	862                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x5d9:0x9 DW_TAG_variable
	.word	.Ldebug_loc23           # DW_AT_location
	.word	873                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x5e4:0xcf DW_TAG_inlined_subroutine
	.word	885                     # DW_AT_abstract_origin
	.word	.Ltmp50                 # DW_AT_low_pc
	.word	.Ltmp69-.Ltmp50         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	193                     # DW_AT_call_line
	.byte	17                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x5f4:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc25           # DW_AT_location
	.word	897                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x5fd:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc26           # DW_AT_location
	.word	908                     # DW_AT_abstract_origin
	.byte	26                      # Abbrev [26] 0x606:0x5 DW_TAG_variable
	.word	919                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x60b:0x9 DW_TAG_variable
	.word	.Ldebug_loc37           # DW_AT_location
	.word	930                     # DW_AT_abstract_origin
	.byte	25                      # Abbrev [25] 0x614:0x72 DW_TAG_inlined_subroutine
	.word	981                     # DW_AT_abstract_origin
	.word	.Ltmp52                 # DW_AT_low_pc
	.word	.Ltmp56-.Ltmp52         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	144                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x624:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc28           # DW_AT_location
	.word	997                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x62d:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc27           # DW_AT_location
	.word	1008                    # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x636:0x9 DW_TAG_variable
	.word	.Ldebug_loc30           # DW_AT_location
	.word	1019                    # DW_AT_abstract_origin
	.byte	25                      # Abbrev [25] 0x63f:0x23 DW_TAG_inlined_subroutine
	.word	942                     # DW_AT_abstract_origin
	.word	.Ltmp52                 # DW_AT_low_pc
	.word	.Ltmp53-.Ltmp52         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	240                     # DW_AT_call_line
	.byte	15                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x64f:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc29           # DW_AT_location
	.word	958                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x658:0x9 DW_TAG_variable
	.word	.Ldebug_loc31           # DW_AT_location
	.word	969                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x662:0x23 DW_TAG_inlined_subroutine
	.word	1031                    # DW_AT_abstract_origin
	.word	.Ltmp54                 # DW_AT_low_pc
	.word	.Ltmp55-.Ltmp54         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	243                     # DW_AT_call_line
	.byte	19                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x672:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc32           # DW_AT_location
	.word	1047                    # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x67b:0x9 DW_TAG_variable
	.word	.Ldebug_loc33           # DW_AT_location
	.word	1058                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x686:0x2c DW_TAG_inlined_subroutine
	.word	1070                    # DW_AT_abstract_origin
	.word	.Ltmp56                 # DW_AT_low_pc
	.word	.Ltmp65-.Ltmp56         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	151                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x696:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc34           # DW_AT_location
	.word	1082                    # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x69f:0x9 DW_TAG_variable
	.word	.Ldebug_loc35           # DW_AT_location
	.word	1093                    # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x6a8:0x9 DW_TAG_variable
	.word	.Ldebug_loc36           # DW_AT_location
	.word	1104                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x6b3:0x8c DW_TAG_inlined_subroutine
	.word	1116                    # DW_AT_abstract_origin
	.word	.Ltmp70                 # DW_AT_low_pc
	.word	.Ltmp75-.Ltmp70         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	195                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x6c3:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc38           # DW_AT_location
	.word	1128                    # DW_AT_abstract_origin
	.byte	25                      # Abbrev [25] 0x6cc:0x72 DW_TAG_inlined_subroutine
	.word	981                     # DW_AT_abstract_origin
	.word	.Ltmp70                 # DW_AT_low_pc
	.word	.Ltmp74-.Ltmp70         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	164                     # DW_AT_call_line
	.byte	9                       # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x6dc:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc39           # DW_AT_location
	.word	997                     # DW_AT_abstract_origin
	.byte	23                      # Abbrev [23] 0x6e5:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc40           # DW_AT_location
	.word	1008                    # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x6ee:0x9 DW_TAG_variable
	.word	.Ldebug_loc42           # DW_AT_location
	.word	1019                    # DW_AT_abstract_origin
	.byte	25                      # Abbrev [25] 0x6f7:0x23 DW_TAG_inlined_subroutine
	.word	942                     # DW_AT_abstract_origin
	.word	.Ltmp70                 # DW_AT_low_pc
	.word	.Ltmp71-.Ltmp70         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	240                     # DW_AT_call_line
	.byte	15                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x707:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc41           # DW_AT_location
	.word	958                     # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x710:0x9 DW_TAG_variable
	.word	.Ldebug_loc43           # DW_AT_location
	.word	969                     # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	25                      # Abbrev [25] 0x71a:0x23 DW_TAG_inlined_subroutine
	.word	1031                    # DW_AT_abstract_origin
	.word	.Ltmp72                 # DW_AT_low_pc
	.word	.Ltmp73-.Ltmp72         # DW_AT_high_pc
	.byte	2                       # DW_AT_call_file
	.byte	243                     # DW_AT_call_line
	.byte	19                      # DW_AT_call_column
	.byte	23                      # Abbrev [23] 0x72a:0x9 DW_TAG_formal_parameter
	.word	.Ldebug_loc44           # DW_AT_location
	.word	1047                    # DW_AT_abstract_origin
	.byte	24                      # Abbrev [24] 0x733:0x9 DW_TAG_variable
	.word	.Ldebug_loc45           # DW_AT_location
	.word	1058                    # DW_AT_abstract_origin
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	27                      # Abbrev [27] 0x740:0x16b DW_TAG_subprogram
	.word	.Lfunc_begin1           # DW_AT_low_pc
	.word	.Lfunc_end1-.Lfunc_begin1 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string71         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	29                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0x755:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc46           # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.word	4060                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x764:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc47           # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.word	4060                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x773:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc48           # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	30                      # DW_AT_decl_line
	.word	4060                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x782:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc49           # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	31                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x791:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc50           # DW_AT_location
	.word	.Linfo_string80         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x7a0:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc51           # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	32                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x7af:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc52           # DW_AT_location
	.word	.Linfo_string82         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x7be:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc53           # DW_AT_location
	.word	.Linfo_string83         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	33                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0x7cd:0xf DW_TAG_variable
	.word	.Ldebug_loc55           # DW_AT_location
	.word	.Linfo_string85         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	35                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0x7dc:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges1         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0x7e1:0xf DW_TAG_variable
	.word	.Ldebug_loc54           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0x7f0:0x15 DW_TAG_lexical_block
	.word	.Ltmp83                 # DW_AT_low_pc
	.word	.Ltmp84-.Ltmp83         # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0x7f9:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	34                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	28                      # Abbrev [28] 0x806:0x6d DW_TAG_lexical_block
	.word	.Ldebug_ranges3         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0x80b:0xf DW_TAG_variable
	.word	.Ldebug_loc56           # DW_AT_location
	.word	.Linfo_string39         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	36                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0x81a:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges2         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0x81f:0xf DW_TAG_variable
	.word	.Ldebug_loc57           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0x82e:0x15 DW_TAG_lexical_block
	.word	.Ltmp95                 # DW_AT_low_pc
	.word	.Ltmp96-.Ltmp95         # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0x837:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	37                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x844:0x2e DW_TAG_lexical_block
	.word	.Ltmp99                 # DW_AT_low_pc
	.word	.Ltmp101-.Ltmp99        # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0x84d:0xf DW_TAG_variable
	.word	.Ldebug_loc58           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0x85c:0x15 DW_TAG_lexical_block
	.word	.Ltmp100                # DW_AT_low_pc
	.word	.Ltmp101-.Ltmp100       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0x865:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	40                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0x873:0x2e DW_TAG_lexical_block
	.word	.Ltmp107                # DW_AT_low_pc
	.word	.Ltmp110-.Ltmp107       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0x87c:0xf DW_TAG_variable
	.word	.Ldebug_loc59           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0x88b:0x15 DW_TAG_lexical_block
	.word	.Ltmp109                # DW_AT_low_pc
	.word	.Ltmp110-.Ltmp109       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0x894:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	42                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0x8a1:0x9 DW_TAG_GNU_call_site
	.word	2219                    # DW_AT_abstract_origin
	.word	.Ltmp98                 # DW_AT_low_pc
	.byte	0                       # End Of Children Mark
	.byte	31                      # Abbrev [31] 0x8ab:0xbc DW_TAG_subprogram
	.word	.Lfunc_begin2           # DW_AT_low_pc
	.word	.Lfunc_end2-.Lfunc_begin2 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string7          # DW_AT_linkage_name
	.word	.Linfo_string8          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0x8c4:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc60           # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4060                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x8d3:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc61           # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4060                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x8e2:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc62           # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4060                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x8f1:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc63           # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x900:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc64           # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0x90f:0xf DW_TAG_variable
	.word	.Ldebug_loc65           # DW_AT_location
	.word	.Linfo_string86         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0x91e:0xf DW_TAG_variable
	.word	.Ldebug_loc66           # DW_AT_location
	.word	.Linfo_string87         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	28                      # Abbrev [28] 0x92d:0x15 DW_TAG_lexical_block
	.word	.Ldebug_ranges4         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0x932:0xf DW_TAG_variable
	.word	.Ldebug_loc67           # DW_AT_location
	.word	.Linfo_string88         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	100                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0x942:0x9 DW_TAG_GNU_call_site
	.word	1140                    # DW_AT_abstract_origin
	.word	.Ltmp135                # DW_AT_low_pc
	.byte	3                       # Abbrev [3] 0x94b:0x9 DW_TAG_template_type_parameter
	.word	106                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x954:0x9 DW_TAG_template_type_parameter
	.word	106                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0x95d:0x9 DW_TAG_template_type_parameter
	.word	106                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	0                       # End Of Children Mark
	.byte	27                      # Abbrev [27] 0x967:0x16b DW_TAG_subprogram
	.word	.Lfunc_begin3           # DW_AT_low_pc
	.word	.Lfunc_end3-.Lfunc_begin3 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string72         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	47                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0x97c:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc68           # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.word	4076                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x98b:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc69           # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.word	4076                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x99a:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc70           # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	48                      # DW_AT_decl_line
	.word	4076                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x9a9:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc71           # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	49                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x9b8:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc72           # DW_AT_location
	.word	.Linfo_string80         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x9c7:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc73           # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	50                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x9d6:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc74           # DW_AT_location
	.word	.Linfo_string82         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0x9e5:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc75           # DW_AT_location
	.word	.Linfo_string83         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	51                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0x9f4:0xf DW_TAG_variable
	.word	.Ldebug_loc77           # DW_AT_location
	.word	.Linfo_string85         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	53                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0xa03:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges5         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xa08:0xf DW_TAG_variable
	.word	.Ldebug_loc76           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xa17:0x15 DW_TAG_lexical_block
	.word	.Ltmp140                # DW_AT_low_pc
	.word	.Ltmp141-.Ltmp140       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xa20:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	52                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	28                      # Abbrev [28] 0xa2d:0x6d DW_TAG_lexical_block
	.word	.Ldebug_ranges7         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xa32:0xf DW_TAG_variable
	.word	.Ldebug_loc78           # DW_AT_location
	.word	.Linfo_string39         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	54                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0xa41:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges6         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xa46:0xf DW_TAG_variable
	.word	.Ldebug_loc79           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xa55:0x15 DW_TAG_lexical_block
	.word	.Ltmp152                # DW_AT_low_pc
	.word	.Ltmp153-.Ltmp152       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xa5e:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	55                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xa6b:0x2e DW_TAG_lexical_block
	.word	.Ltmp156                # DW_AT_low_pc
	.word	.Ltmp158-.Ltmp156       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0xa74:0xf DW_TAG_variable
	.word	.Ldebug_loc80           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xa83:0x15 DW_TAG_lexical_block
	.word	.Ltmp157                # DW_AT_low_pc
	.word	.Ltmp158-.Ltmp157       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xa8c:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	58                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xa9a:0x2e DW_TAG_lexical_block
	.word	.Ltmp164                # DW_AT_low_pc
	.word	.Ltmp167-.Ltmp164       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0xaa3:0xf DW_TAG_variable
	.word	.Ldebug_loc81           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xab2:0x15 DW_TAG_lexical_block
	.word	.Ltmp166                # DW_AT_low_pc
	.word	.Ltmp167-.Ltmp166       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xabb:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	60                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xac8:0x9 DW_TAG_GNU_call_site
	.word	2770                    # DW_AT_abstract_origin
	.word	.Ltmp155                # DW_AT_low_pc
	.byte	0                       # End Of Children Mark
	.byte	31                      # Abbrev [31] 0xad2:0xbc DW_TAG_subprogram
	.word	.Lfunc_begin4           # DW_AT_low_pc
	.word	.Lfunc_end4-.Lfunc_begin4 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string11         # DW_AT_linkage_name
	.word	.Linfo_string12         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0xaeb:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc82           # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4097                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xafa:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc83           # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4097                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xb09:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc84           # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4097                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xb18:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc85           # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xb27:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc86           # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xb36:0xf DW_TAG_variable
	.word	.Ldebug_loc87           # DW_AT_location
	.word	.Linfo_string86         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xb45:0xf DW_TAG_variable
	.word	.Ldebug_loc88           # DW_AT_location
	.word	.Linfo_string87         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	28                      # Abbrev [28] 0xb54:0x15 DW_TAG_lexical_block
	.word	.Ldebug_ranges8         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xb59:0xf DW_TAG_variable
	.word	.Ldebug_loc89           # DW_AT_location
	.word	.Linfo_string88         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	100                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xb69:0x9 DW_TAG_GNU_call_site
	.word	1140                    # DW_AT_abstract_origin
	.word	.Ltmp192                # DW_AT_low_pc
	.byte	3                       # Abbrev [3] 0xb72:0x9 DW_TAG_template_type_parameter
	.word	193                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xb7b:0x9 DW_TAG_template_type_parameter
	.word	193                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xb84:0x9 DW_TAG_template_type_parameter
	.word	193                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	0                       # End Of Children Mark
	.byte	27                      # Abbrev [27] 0xb8e:0x16b DW_TAG_subprogram
	.word	.Lfunc_begin5           # DW_AT_low_pc
	.word	.Lfunc_end5-.Lfunc_begin5 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string73         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	65                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0xba3:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc90           # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.word	4102                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xbb2:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc91           # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.word	4102                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xbc1:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc92           # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	66                      # DW_AT_decl_line
	.word	4102                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xbd0:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc93           # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	67                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xbdf:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc94           # DW_AT_location
	.word	.Linfo_string80         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	68                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xbee:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc95           # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	68                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xbfd:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc96           # DW_AT_location
	.word	.Linfo_string82         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xc0c:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc97           # DW_AT_location
	.word	.Linfo_string83         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	69                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xc1b:0xf DW_TAG_variable
	.word	.Ldebug_loc99           # DW_AT_location
	.word	.Linfo_string85         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	71                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0xc2a:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges9         # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xc2f:0xf DW_TAG_variable
	.word	.Ldebug_loc98           # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	70                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xc3e:0x15 DW_TAG_lexical_block
	.word	.Ltmp197                # DW_AT_low_pc
	.word	.Ltmp198-.Ltmp197       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xc47:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	70                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	28                      # Abbrev [28] 0xc54:0x6d DW_TAG_lexical_block
	.word	.Ldebug_ranges11        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xc59:0xf DW_TAG_variable
	.word	.Ldebug_loc100          # DW_AT_location
	.word	.Linfo_string39         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	72                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0xc68:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges10        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xc6d:0xf DW_TAG_variable
	.word	.Ldebug_loc101          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xc7c:0x15 DW_TAG_lexical_block
	.word	.Ltmp209                # DW_AT_low_pc
	.word	.Ltmp210-.Ltmp209       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xc85:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	73                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xc92:0x2e DW_TAG_lexical_block
	.word	.Ltmp213                # DW_AT_low_pc
	.word	.Ltmp215-.Ltmp213       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0xc9b:0xf DW_TAG_variable
	.word	.Ldebug_loc102          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	76                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xcaa:0x15 DW_TAG_lexical_block
	.word	.Ltmp214                # DW_AT_low_pc
	.word	.Ltmp215-.Ltmp214       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xcb3:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	76                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xcc1:0x2e DW_TAG_lexical_block
	.word	.Ltmp221                # DW_AT_low_pc
	.word	.Ltmp224-.Ltmp221       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0xcca:0xf DW_TAG_variable
	.word	.Ldebug_loc103          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	78                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xcd9:0x15 DW_TAG_lexical_block
	.word	.Ltmp223                # DW_AT_low_pc
	.word	.Ltmp224-.Ltmp223       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xce2:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	78                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xcef:0x9 DW_TAG_GNU_call_site
	.word	3321                    # DW_AT_abstract_origin
	.word	.Ltmp212                # DW_AT_low_pc
	.byte	0                       # End Of Children Mark
	.byte	31                      # Abbrev [31] 0xcf9:0xbc DW_TAG_subprogram
	.word	.Lfunc_begin6           # DW_AT_low_pc
	.word	.Lfunc_end6-.Lfunc_begin6 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string14         # DW_AT_linkage_name
	.word	.Linfo_string15         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0xd12:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc104          # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4123                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xd21:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc105          # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4123                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xd30:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc106          # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4123                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xd3f:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc107          # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xd4e:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc108          # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xd5d:0xf DW_TAG_variable
	.word	.Ldebug_loc109          # DW_AT_location
	.word	.Linfo_string86         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xd6c:0xf DW_TAG_variable
	.word	.Ldebug_loc110          # DW_AT_location
	.word	.Linfo_string87         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	28                      # Abbrev [28] 0xd7b:0x15 DW_TAG_lexical_block
	.word	.Ldebug_ranges12        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xd80:0xf DW_TAG_variable
	.word	.Ldebug_loc111          # DW_AT_location
	.word	.Linfo_string88         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	100                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xd90:0x9 DW_TAG_GNU_call_site
	.word	1140                    # DW_AT_abstract_origin
	.word	.Ltmp248                # DW_AT_low_pc
	.byte	3                       # Abbrev [3] 0xd99:0x9 DW_TAG_template_type_parameter
	.word	273                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xda2:0x9 DW_TAG_template_type_parameter
	.word	273                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xdab:0x9 DW_TAG_template_type_parameter
	.word	273                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	0                       # End Of Children Mark
	.byte	27                      # Abbrev [27] 0xdb5:0x16b DW_TAG_subprogram
	.word	.Lfunc_begin7           # DW_AT_low_pc
	.word	.Lfunc_end7-.Lfunc_begin7 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string74         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0xdca:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc112          # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	84                      # DW_AT_decl_line
	.word	4128                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xdd9:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc113          # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	84                      # DW_AT_decl_line
	.word	4128                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xde8:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc114          # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	84                      # DW_AT_decl_line
	.word	4128                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xdf7:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc115          # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	85                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xe06:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc116          # DW_AT_location
	.word	.Linfo_string80         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xe15:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc117          # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xe24:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc118          # DW_AT_location
	.word	.Linfo_string82         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xe33:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc119          # DW_AT_location
	.word	.Linfo_string83         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xe42:0xf DW_TAG_variable
	.word	.Ldebug_loc121          # DW_AT_location
	.word	.Linfo_string85         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	89                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0xe51:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges13        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xe56:0xf DW_TAG_variable
	.word	.Ldebug_loc120          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	88                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xe65:0x15 DW_TAG_lexical_block
	.word	.Ltmp253                # DW_AT_low_pc
	.word	.Ltmp254-.Ltmp253       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xe6e:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	88                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	28                      # Abbrev [28] 0xe7b:0x6d DW_TAG_lexical_block
	.word	.Ldebug_ranges15        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xe80:0xf DW_TAG_variable
	.word	.Ldebug_loc122          # DW_AT_location
	.word	.Linfo_string39         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	28                      # Abbrev [28] 0xe8f:0x2a DW_TAG_lexical_block
	.word	.Ldebug_ranges14        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xe94:0xf DW_TAG_variable
	.word	.Ldebug_loc123          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	91                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xea3:0x15 DW_TAG_lexical_block
	.word	.Ltmp265                # DW_AT_low_pc
	.word	.Ltmp266-.Ltmp265       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xeac:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	91                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xeb9:0x2e DW_TAG_lexical_block
	.word	.Ltmp269                # DW_AT_low_pc
	.word	.Ltmp271-.Ltmp269       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0xec2:0xf DW_TAG_variable
	.word	.Ldebug_loc124          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	94                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xed1:0x15 DW_TAG_lexical_block
	.word	.Ltmp270                # DW_AT_low_pc
	.word	.Ltmp271-.Ltmp270       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xeda:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	94                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	29                      # Abbrev [29] 0xee8:0x2e DW_TAG_lexical_block
	.word	.Ltmp277                # DW_AT_low_pc
	.word	.Ltmp280-.Ltmp277       # DW_AT_high_pc
	.byte	21                      # Abbrev [21] 0xef1:0xf DW_TAG_variable
	.word	.Ldebug_loc125          # DW_AT_location
	.word	.Linfo_string84         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	96                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	29                      # Abbrev [29] 0xf00:0x15 DW_TAG_lexical_block
	.word	.Ltmp279                # DW_AT_low_pc
	.word	.Ltmp280-.Ltmp279       # DW_AT_high_pc
	.byte	17                      # Abbrev [17] 0xf09:0xb DW_TAG_variable
	.word	.Linfo_string61         # DW_AT_name
	.byte	3                       # DW_AT_decl_file
	.byte	96                      # DW_AT_decl_line
	.word	564                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xf16:0x9 DW_TAG_GNU_call_site
	.word	3872                    # DW_AT_abstract_origin
	.word	.Ltmp268                # DW_AT_low_pc
	.byte	0                       # End Of Children Mark
	.byte	31                      # Abbrev [31] 0xf20:0xbc DW_TAG_subprogram
	.word	.Lfunc_begin8           # DW_AT_low_pc
	.word	.Lfunc_end8-.Lfunc_begin8 # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	82
                                        # DW_AT_GNU_all_call_sites
	.word	.Linfo_string17         # DW_AT_linkage_name
	.word	.Linfo_string18         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	106                     # DW_AT_type
                                        # DW_AT_external
	.byte	20                      # Abbrev [20] 0xf39:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc126          # DW_AT_location
	.word	.Linfo_string75         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4128                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xf48:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc127          # DW_AT_location
	.word	.Linfo_string76         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4128                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xf57:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc128          # DW_AT_location
	.word	.Linfo_string77         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.word	4128                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xf66:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc129          # DW_AT_location
	.word	.Linfo_string78         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	20                      # Abbrev [20] 0xf75:0xf DW_TAG_formal_parameter
	.word	.Ldebug_loc130          # DW_AT_location
	.word	.Linfo_string81         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xf84:0xf DW_TAG_variable
	.word	.Ldebug_loc131          # DW_AT_location
	.word	.Linfo_string86         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	92                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0xf93:0xf DW_TAG_variable
	.word	.Ldebug_loc132          # DW_AT_location
	.word	.Linfo_string87         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	93                      # DW_AT_decl_line
	.word	4065                    # DW_AT_type
	.byte	28                      # Abbrev [28] 0xfa2:0x15 DW_TAG_lexical_block
	.word	.Ldebug_ranges16        # DW_AT_ranges
	.byte	21                      # Abbrev [21] 0xfa7:0xf DW_TAG_variable
	.word	.Ldebug_loc133          # DW_AT_location
	.word	.Linfo_string88         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	100                     # DW_AT_decl_line
	.word	106                     # DW_AT_type
	.byte	0                       # End Of Children Mark
	.byte	30                      # Abbrev [30] 0xfb7:0x9 DW_TAG_GNU_call_site
	.word	1140                    # DW_AT_abstract_origin
	.word	.Ltmp306                # DW_AT_low_pc
	.byte	3                       # Abbrev [3] 0xfc0:0x9 DW_TAG_template_type_parameter
	.word	353                     # DW_AT_type
	.word	.Linfo_string4          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xfc9:0x9 DW_TAG_template_type_parameter
	.word	353                     # DW_AT_type
	.word	.Linfo_string5          # DW_AT_name
	.byte	3                       # Abbrev [3] 0xfd2:0x9 DW_TAG_template_type_parameter
	.word	353                     # DW_AT_type
	.word	.Linfo_string6          # DW_AT_name
	.byte	0                       # End Of Children Mark
	.byte	32                      # Abbrev [32] 0xfdc:0x5 DW_TAG_restrict_type
	.word	113                     # DW_AT_type
	.byte	8                       # Abbrev [8] 0xfe1:0xb DW_TAG_typedef
	.word	118                     # DW_AT_type
	.word	.Linfo_string79         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	172                     # DW_AT_decl_line
	.byte	32                      # Abbrev [32] 0xfec:0x5 DW_TAG_restrict_type
	.word	4081                    # DW_AT_type
	.byte	6                       # Abbrev [6] 0xff1:0x5 DW_TAG_pointer_type
	.word	4086                    # DW_AT_type
	.byte	8                       # Abbrev [8] 0xff6:0xb DW_TAG_typedef
	.word	193                     # DW_AT_type
	.word	.Linfo_string89         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	205                     # DW_AT_decl_line
	.byte	32                      # Abbrev [32] 0x1001:0x5 DW_TAG_restrict_type
	.word	200                     # DW_AT_type
	.byte	32                      # Abbrev [32] 0x1006:0x5 DW_TAG_restrict_type
	.word	4107                    # DW_AT_type
	.byte	6                       # Abbrev [6] 0x100b:0x5 DW_TAG_pointer_type
	.word	4112                    # DW_AT_type
	.byte	8                       # Abbrev [8] 0x1010:0xb DW_TAG_typedef
	.word	273                     # DW_AT_type
	.word	.Linfo_string90         # DW_AT_name
	.byte	5                       # DW_AT_decl_file
	.byte	224                     # DW_AT_decl_line
	.byte	32                      # Abbrev [32] 0x101b:0x5 DW_TAG_restrict_type
	.word	280                     # DW_AT_type
	.byte	32                      # Abbrev [32] 0x1020:0x5 DW_TAG_restrict_type
	.word	360                     # DW_AT_type
	.byte	0                       # End Of Children Mark
.Ldebug_info_end0:
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.word	.Ltmp1
	.word	.Ltmp2
	.word	.Ltmp4
	.word	.Ltmp5
	.word	.Ltmp6
	.word	.Ltmp9
	.word	0
	.word	0
.Ldebug_ranges1:
	.word	.Ltmp80
	.word	.Ltmp84
	.word	.Ltmp93
	.word	.Ltmp94
	.word	.Ltmp98
	.word	.Ltmp99
	.word	0
	.word	0
.Ldebug_ranges2:
	.word	.Ltmp91
	.word	.Ltmp92
	.word	.Ltmp94
	.word	.Ltmp96
	.word	0
	.word	0
.Ldebug_ranges3:
	.word	.Ltmp91
	.word	.Ltmp93
	.word	.Ltmp94
	.word	.Ltmp98
	.word	.Ltmp99
	.word	.Ltmp101
	.word	.Ltmp104
	.word	.Ltmp105
	.word	.Ltmp106
	.word	.Ltmp107
	.word	0
	.word	0
.Ldebug_ranges4:
	.word	.Ltmp116
	.word	.Ltmp117
	.word	.Ltmp119
	.word	.Ltmp134
	.word	0
	.word	0
.Ldebug_ranges5:
	.word	.Ltmp137
	.word	.Ltmp141
	.word	.Ltmp150
	.word	.Ltmp151
	.word	.Ltmp155
	.word	.Ltmp156
	.word	0
	.word	0
.Ldebug_ranges6:
	.word	.Ltmp148
	.word	.Ltmp149
	.word	.Ltmp151
	.word	.Ltmp153
	.word	0
	.word	0
.Ldebug_ranges7:
	.word	.Ltmp148
	.word	.Ltmp150
	.word	.Ltmp151
	.word	.Ltmp155
	.word	.Ltmp156
	.word	.Ltmp158
	.word	.Ltmp161
	.word	.Ltmp162
	.word	.Ltmp163
	.word	.Ltmp164
	.word	0
	.word	0
.Ldebug_ranges8:
	.word	.Ltmp173
	.word	.Ltmp174
	.word	.Ltmp176
	.word	.Ltmp191
	.word	0
	.word	0
.Ldebug_ranges9:
	.word	.Ltmp194
	.word	.Ltmp198
	.word	.Ltmp207
	.word	.Ltmp208
	.word	.Ltmp212
	.word	.Ltmp213
	.word	0
	.word	0
.Ldebug_ranges10:
	.word	.Ltmp205
	.word	.Ltmp206
	.word	.Ltmp208
	.word	.Ltmp210
	.word	0
	.word	0
.Ldebug_ranges11:
	.word	.Ltmp205
	.word	.Ltmp207
	.word	.Ltmp208
	.word	.Ltmp212
	.word	.Ltmp213
	.word	.Ltmp215
	.word	.Ltmp218
	.word	.Ltmp219
	.word	.Ltmp220
	.word	.Ltmp221
	.word	0
	.word	0
.Ldebug_ranges12:
	.word	.Ltmp230
	.word	.Ltmp231
	.word	.Ltmp233
	.word	.Ltmp247
	.word	0
	.word	0
.Ldebug_ranges13:
	.word	.Ltmp250
	.word	.Ltmp254
	.word	.Ltmp263
	.word	.Ltmp264
	.word	.Ltmp268
	.word	.Ltmp269
	.word	0
	.word	0
.Ldebug_ranges14:
	.word	.Ltmp261
	.word	.Ltmp262
	.word	.Ltmp264
	.word	.Ltmp266
	.word	0
	.word	0
.Ldebug_ranges15:
	.word	.Ltmp261
	.word	.Ltmp263
	.word	.Ltmp264
	.word	.Ltmp268
	.word	.Ltmp269
	.word	.Ltmp271
	.word	.Ltmp274
	.word	.Ltmp275
	.word	.Ltmp276
	.word	.Ltmp277
	.word	0
	.word	0
.Ldebug_ranges16:
	.word	.Ltmp286
	.word	.Ltmp287
	.word	.Ltmp289
	.word	.Ltmp305
	.word	0
	.word	0
.Ldebug_ranges17:
	.word	.Lfunc_begin0
	.word	.Lfunc_end1
	.word	.Lfunc_begin3
	.word	.Lfunc_end3
	.word	.Lfunc_begin5
	.word	.Lfunc_end5
	.word	.Lfunc_begin7
	.word	.Lfunc_end7
	.word	.Lfunc_begin2
	.word	.Lfunc_end2
	.word	.Lfunc_begin4
	.word	.Lfunc_end4
	.word	.Lfunc_begin6
	.word	.Lfunc_end6
	.word	.Lfunc_begin8
	.word	.Lfunc_end8
	.word	0
	.word	0
	.ident	"clang version 10.0.0 (git@github.com:bespoke-silicon-group/llvm-project.git 3ee81f3def2c4c2a818f9f939f4421b3f3af313e)"
	.section	".note.GNU-stack","",@progbits
	.section	.debug_line,"",@progbits
.Lline_table_start0:
