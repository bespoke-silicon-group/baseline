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
# that defines the machine to compile and simulate on. Using BSG_F1_DIR (which
# is set in environment.mk) uses the same machine as in bsg_replicant.
################################################################################

BSG_MACHINE_PATH=$(BSG_F1_DIR)

################################################################################
# Define the range of versions
################################################################################
# Kernel versions. See kernel/README.md for more information.  Version names do
# not need to use v* and can be any string
VERSIONS = v0

################################################################################
# Define any sources that should be used compiled during kernel compilation,
# including the source file with the kernel itself. kernel.riscv will
# be the name of the compiled RISC-V Binary for the Manycore
#
# Use KERNEL_*LIBRARIES list sources that should be compiled and linked with all
# kernel.cpp versions. However, if you have version-specific sources you must
# come up with your own solution.
# 
# Use KERNEL_INCLUDES to specify the path to directories that contain headers.
################################################################################

# C Libraries
KERNEL_CLIBRARIES   +=
# C++ Libraries
KERNEL_CXXLIBRARIES +=

KERNEL_INCLUDES     += -I$(CURRENT_PATH)/kernel/include -I$(CURRENT_PATH)

# Define the default kernel.cpp file. If KERNEL_DEFAULT is not defined it will
# be set to kernel.cpp in the same directory as this Makefile.
DEFAULT_VERSION     := v0
KERNEL_DEFAULT      := kernel/$(DEFAULT_VERSION)/kernel.cpp

################################################################################
# Include the kernel build rules (This must be included after KERNEL_*LIBRARIES,
# KERNEL_DEFAULT, KERNEL_INCLUDES, etc)
################################################################################

-include $(FRAGMENTS_PATH)/kernel/cudalite.mk
RISCV_LDFLAGS:=$(filter-out -nostdlib,$(RISCV_LDFLAGS))
################################################################################
# END OF KERNEL-SPECIFIC RULES / START OF HOST-SPECIFIC RULES
################################################################################


################################################################################
# Define the $(HOST_TARGET), the name of the host executable to generate. The
# cosimulation host executable will be called
# $(HOST_TARGET).cosim. HOST_*SOURCES list the host files that should be
# compiled and linked into the executable.
################################################################################

HOST_TARGET         := raytracer
HOST_CSOURCES       := 
HOST_CXXSOURCES     := $(HOST_TARGET).cpp
HOST_INCLUDES       := -I$(CURRENT_PATH)

################################################################################
# Include the Cosimulation host build rules (This must be included after
# HOST_*SOURCES, HOST_TARGET, HOST_INCLUDES, etc)
################################################################################

-include $(FRAGMENTS_PATH)/host/cosim.mk

################################################################################
# Include the analysis rules. These define how to generate analysis products
# like vanilla_operation_trace, etc.
################################################################################

-include $(FRAGMENTS_PATH)/analysis.mk

################################################################################
# The following rules define how to RUN cosimulation tests:
################################################################################

# This rule defines the `make <version name>` rule (e.g. `make v2`). For all
# kernel versions defined in $(VERSIONS) you can run `make <version name` and
# the cosimulation results ($(HOST_TARGET).cosim.log, $(HOST_TARGET).vpd,
# vanilla_operation_trace.csv, vanila_stats.csv, etc) will be put in the
# kernel/<version name>/ directory.
$(VERSIONS): %: kernel/%/$(HOST_TARGET).cosim.log

################################################################################
# Define rules for the default cosimulation execution.
################################################################################

# ALIASES defines the outputs that are also generated when cosimulation is
# run. They are aliases for running $(HOST_TARGET).cosim.log. We use empty an
# make recipe for aliases for reasons described here:
# https://www.gnu.org/software/make/manual/html_node/Empty-Recipes.html
ALIASES = vanilla_stats.csv $(HOST_TARGET).vpd vanilla_operation_trace.csv
$(ALIASES): $(HOST_TARGET).cosim.log ;
$(HOST_TARGET).cosim.log: kernel.riscv $(HOST_TARGET).cosim 
	./$(HOST_TARGET).cosim +ntb_random_seed_automatic +trace  \
		+c_args="kernel.riscv $(DEFAULT_VERSION)" \
		+vpdfile+$(HOST_TARGET).vpd | tee $@

################################################################################
# Define rules for version-specific cosimulation execution. EXEC_PATH and
# _VERSION are defined inside of the rule so that the executable can be run from
# inside of the kernel/<version name> directory and produce outputs
# there. KERNEL_PATH is the path to the version-specific kernel.riscv binary
#
# (NB, since `cd $(EXEC_PATH)` is called before running the executable it is
# possible to specify kernel.riscv as the path to the kernel file to +c_args
# since it is resident in $(EXEC_PATH), but I provided the full path to be more
# explicit and clear)
################################################################################

# KERNEL_ALIASES defines the outputs that are also generated when cosimulation
# is run. They are aliases for kernel/<version name>/$(HOST_TARGET).cosim.log
# (This is simliar to ALIASES above). We use empty an make recipe for aliases
# for reasons described here:
# https://www.gnu.org/software/make/manual/html_node/Empty-Recipes.html
KERNEL_ALIASES = $(foreach a,$(ALIASES),kernel/%/$a)
$(KERNEL_ALIASES): kernel/%/$(HOST_TARGET).cosim.log ;
kernel/%/$(HOST_TARGET).cosim.log: kernel/%/kernel.riscv $(HOST_TARGET).cosim 
	$(eval EXEC_PATH   := $(patsubst %/,%,$(dir $@)))
	$(eval KERNEL_PATH := $(CURRENT_PATH)/$(EXEC_PATH))
	$(eval _VERSION    := $(notdir $(EXEC_PATH)))
	cd $(EXEC_PATH) && \
	$(CURRENT_PATH)/$(HOST_TARGET).cosim +ntb_random_seed_automatic +trace \
		+vpdfile+$(HOST_TARGET).vpd \
		+c_args="$(KERNEL_PATH)/kernel.riscv $(_VERSION)" | tee $(notdir $@)

################################################################################
# Define the clean rules. clean calls the makefile-specific cleans, whereas
# users can add commands and dependencies to custom.clean.
################################################################################
version.clean:
	rm -rf kernel/*/*{.csv,.log,.rvo,.riscv,.vpd,.key,.png}
	rm -rf kernel/*/stats

host.clean:
	rm -rf $(HOST_TARGET)

custom.clean: version.clean host.clean

clean: cosim.clean analysis.clean cudalite.clean custom.clean

################################################################################
# Define overall-goals. The all rule runs all kernel versions, and the default
# kernel.
################################################################################

.DEFAULT_GOAL = all
all: analysis default

default: stats graphs pc_stats

# analysis launches independent cosimulation executions for each of kernel
# versions in $(VERSIONS). When each execution finishes, it generates the
# statistics for each kernel. All output products are in respective
# kernel/<version name>/ directories
analysis: $(foreach v,$(VERSIONS),kernel/$v/stats kernel/$v/graphs kernel/$v/pc_stats)

# Always re-run, if asked.
.PHONY: default analysis
.PRECIOUS: $(KERNEL_ALIASES)
