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
CURRENT_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

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
# Define the range of versions
################################################################################
VERSIONS = v1 v2 v3 v4 v5 v6 v7
# Default kernel version. This can be any string
# NOTE: V1 and V2 do not expect B to be transposed
DEFAULT_VERSION = v3

################################################################################
# Define any sources that should be used compiled during kernel compilation,
# including the source file with the kernel itself. kernel.riscv will
# be the name of the compiled RISC-V Binary for the Manycore
#
# You can list sources that should be included with ALL kernel
# compilations here, if you have multiple kernels. Or you can list the
# kernel source file, if you only have one kernel. However, if you
# have rule-specific sources, you must append to those in the rules.
################################################################################

# Assembly Libraries
KERNEL_SLIBRARIES =
# C Libraries
KERNEL_CLIBRARIES =
# C++ Libraries
KERNEL_CXXLIBRARIES =
KERNEL_INCLUDES  = -I$(CURRENT_PATH)
KERNEL_INCLUDES += -I$(CURRENT_PATH)/kernel/include

# Define the default kernel.cpp file. If this is not defined
# KERNEL_DEFAULT will be set to kernel.cpp
KERNEL_DEFAULT = kernel/$(DEFAULT_VERSION)/kernel.cpp

################################################################################
# Include the kernel build rules (This must be included after KERNEL_LIBRARIES)
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

# This rule runs specific kernel versions and puts the results in the
# kernel/$(_VERSION) directory. You can run `make v2` (etc) as
# shorthand
$(VERSIONS): %: kernel/%/$(HOST_TARGET).cosim.log

# This rule runs the default kernel defined by KERNEL_DEFAULT. Most of
# the rules are just defining aliases
ALIASES = vanilla_stats.csv $(HOST_TARGET).vpd

$(ALIASES): $(HOST_TARGET).cosim.log
vanilla_operation_trace.csv: SIM_ARGS += +trace
vanilla_operation_trace.csv $(HOST_TARGET).cosim.log: kernel.riscv $(HOST_TARGET).cosim 
	./$(HOST_TARGET).cosim +ntb_random_seed_automatic +vpdfile+$(HOST_TARGET).vpd \
		$(SIM_ARGS) +c_args="kernel.riscv MM-Test-$(VERSION)" | tee $(HOST_TARGET).cosim.log

kernel/%/vanilla_operation_trace.csv: SIM_ARGS += +trace
kernel/%/vanilla_operation_trace.csv kernel/%/vanilla_stats.csv kernel/%/$(HOST_TARGET).vpd kernel/%/$(HOST_TARGET).cosim.log: kernel/%/kernel.riscv $(HOST_TARGET).cosim 
	$(eval EXEC_PATH := $(patsubst %/,%,$(dir $@)))
	$(eval _VERSION  := $(notdir $(EXEC_PATH)))
	cd $(EXEC_PATH) && \
	$(CURRENT_PATH)/$(HOST_TARGET).cosim +ntb_random_seed_automatic +vpdfile+$(HOST_TARGET).vpd \
		+trace +c_args="kernel.riscv $(_VERSION)" | tee $(HOST_TARGET).cosim.log

################################################################################
# Include the analysis rules
################################################################################

-include $(FRAGMENTS_PATH)/analysis.mk

################################################################################
# Define the clean rule
################################################################################
custom.clean:
	rm -rf kernel/*/*{.csv,.log,.rvo,.riscv}
	rm -rf kernel/*/stats

clean: cosim.clean analysis.clean cudalite.clean custom.clean
	rm -rf $(HOST_TARGET)

################################################################################
# Define the default goal
################################################################################

.DEFAULT_GOAL = all
all: kernel.riscv $(HOST_TARGET).cosim

# Always re-run, if asked.
.PHONY: cosim versions

cosim: $(HOST_TARGET).cosim.log
versions: $(VERSIONS)
analysis: $(foreach v,$(VERSIONS),kernel/$v/stats)
