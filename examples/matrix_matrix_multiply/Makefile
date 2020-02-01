# Copyright (c) 2019, University of Washington All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
# Redistributions of source code must retain the above copyright notice, this list
# of conditions and the following disclaimer.
# 
# Redistributions in binary form must reproduce the above copyright notice, this
# list of conditions and the following disclaimer in the documentation and/or
# other materials provided with the distribution.
# 
# Neither the name of the copyright holder nor the names of its contributors may
# be used to endorse or promote products derived from this software without
# specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

################################################################################
# Paths / Environment Configuration
################################################################################
_REPO_ROOT ?= $(shell git rev-parse --show-toplevel)

-include $(_REPO_ROOT)/environment.mk

################################################################################
# Define BSG_MACHINE_PATH, the location of the Makefile.machine.include file
# that defines the machine to compile and simulate on
################################################################################

BSG_MACHINE_PATH=$(BSG_F1_DIR)

################################################################################
# Define the tile-group dimensions.
################################################################################

BSG_TILE_GROUP_DIM_X     ?= 1
BSG_TILE_GROUP_DIM_Y     ?= 1

################################################################################
# Define any sources that should be used compiled during kernel compilation,
# including the source file with the kernel itself. $(KERNEL_TARGET).riscv will
# be the name of the compiled RISC-V Binary for the Manycore
################################################################################

KERNEL_SSOURCES = # Assembly Sources
KERNEL_CSOURCES = # C Sources
KERNEL_CXXSOURCES = example.cpp kernel.cpp # C++ Sources
KERNEL_INCLUDES = -I$(_REPO_ROOT)/examples/matrix_matrix_multiply
KERNEL_TARGET = kernel

################################################################################
# Include the kernel build rules (This must be included after KERNEL_SOURCES)
################################################################################

-include $(FRAGMENTS_PATH)/kernel/cudalite.mk

################################################################################
# Define the $(HOST_TARGET), the name of the host executable. The cosimulation
# host executable will be called $(HOST_TARGET).cosim
################################################################################

HOST_TARGET     := test_matrix_matrix_mul_tile
HOST_CSOURCES   := 
HOST_CXXSOURCES := $(HOST_TARGET).cpp
HOST_INCLUDES   := -I$(_REPO_ROOT)/examples/matrix_matrix_multiply

################################################################################
# Include the Cosimulation host build rules (This must be included after
# HOST_SOURCES)
################################################################################

-include $(FRAGMENTS_PATH)/host/cosim.mk

################################################################################
# Define the rule to run the cosimulation test
################################################################################

# Always re-run, if asked.
.PHONY: cosim

cosim: $(HOST_TARGET).cosim.log

vanilla_stats.csv $(HOST_TARGET).vpd $(HOST_TARGET).cosim.log: $(HOST_TARGET).cosim $(KERNEL_TARGET).riscv
	./$(HOST_TARGET).cosim +ntb_random_seed_automatic +vpdfile+$(HOST_TARGET).vpd \
		$(SIM_ARGS) +c_args="./kernel.riscv MM-Test" | tee $(HOST_TARGET).cosim.log

################################################################################
# Include the analysis rules
################################################################################

-include $(FRAGMENTS_PATH)/analysis.mk

################################################################################
# Define the clean rule
################################################################################
clean:
	rm -rf *.rvo *.riscv Y[0-9]*X[0-9]* *.dis
	rm -rf *.o $(HOST_TARGET) $(HOST_OBJECTS) $(HOST_TARGET).cosim
	rm -rf $(HOST_TARGET).cosim.{daidir,tmp} 64 vc_hdrs.h *.vpd ucli.key *.log
	rm -rf vanilla_stats.csv stats

################################################################################
# Define the default goal
################################################################################

.DEFAULT_GOAL = all
all: kernel.riscv $(HOST_TARGET).cosim
