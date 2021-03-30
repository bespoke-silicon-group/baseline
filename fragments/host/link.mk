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

# These variables are used by simlibs.mk
LIBRARIES_PATH := $(BSG_F1_DIR)/libraries
HARDWARE_PATH  := $(BSG_F1_DIR)/hardware
EXAMPLES_PATH  := $(BSG_F1_DIR)/examples
# CL_DIR Means "Custom Logic" Directory, and is an AWS-FPGA holdover. cadenv.mk
# checks that it is set
CL_DIR         := $(BSG_F1_DIR)

# The following makefile fragment verifies that the tools and CAD environment is
# configured correctly.
-include $(BSG_F1_DIR)/cadenv.mk

-include $(BSG_F1_DIR)/machine.mk

-include $(BSG_F1_DIR)/platform.mk

################################################################################
# Simulation Libraries (C/C++ AND Verilog)
################################################################################
# PROJECT defines the Verilog Simulation Library Target
PROJECT        := baseline

# simlibs.mk defines build rules for hardware and software simulation libraries
# that are necessary for running cosimulation. These are dependencies for
# regression since running $(MAKE) recursively does not prevent parallel builds
# of identical rules -- which causes errors.
TEST_CXXSOURCES := $(HOST_CXXSOURCES)
TEST_CSOURCES   := $(HOST_CSOURCES)
-include $(EXAMPLES_PATH)/link.mk

################################################################################
# Cosimulation Linker Rules
################################################################################
_HELP_STRING := "Rules from host/link.mk\n"

_HELP_STRING += "    $(HOST_TARGET).profile $(HOST_TARGET).debug :\n"
_HELP_STRING += "        - Build the default host executable for RTL Cosimulation using VCS\n"
_HELP_STRING += "          The same executable is reused to run every kernel version \n"

host.link.clean:
	rm -rf $(HOST_TARGET){.profile,.debug}
	rm -rf *.cosim{.daidir,.tmp,.log,} 64
	rm -rf vc_hdrs.h ucli.key

_HELP_STRING += "\n"
_HELP_STRING += $(HELP_STRING)

HELP_STRING := $(_HELP_STRING)
