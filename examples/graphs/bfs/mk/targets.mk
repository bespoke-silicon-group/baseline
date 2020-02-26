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


# expect current path to be set
ifeq ($(CURRENT_PATH),)
$(error "CURRENT_PATH not set - please set in main Makefile")
endif

# expect current path to be set
ifeq ($(_REPO_ROOT),)
$(error "_REPO_ROOT not set - please set in main Makefile")
endif

# expect current path to be set
ifeq ($(HBGRAPHS_DIR),)
$(error "HBGRAPHS_DIR not set - please set in main Makefile")
endif

# expect current path to be set
ifeq ($(GRAPH500_DIR),)
$(error "GRAPH500_DIR not set - please set in main Makefile")
endif

# expect current path to be set
ifeq ($(BFS_MK_PATH),)
$(error "BFS_MK_PATH not set - please set in main Makefile")
endif

# expect current path to be set
ifeq ($(HOST_TARGET),)
$(error "HOST_TARGET not set - please set in main Makefile")
endif

################################################################################
# Define the clean rules. clean calls the makefile-specific cleans, whereas
# users can add commands and dependencies to custom.clean.
################################################################################
version.clean:
	rm -f $(KERNEL_CXXLIBRARIES:.cpp=.rvo)
	rm -rf kernel/*/*{.csv,.log,.rvo,.riscv,.vpd,.key,.png,.dis}
	rm -rf kernel/*/{stats,pc_stats}

custom.clean: version.clean

clean: cosim.clean analysis.clean cudalite.clean custom.clean

################################################################################
# Define overall-goals. The all rule runs all kernel versions, and the default
# kernel.
################################################################################

_HELP_STRING := "Makefile Rules\n"

_HELP_STRING += "    default: \n"
_HELP_STRING += "        - Run the default kernel ($KERNEL_DEFAULT) and generate all of the\n"
_HELP_STRING += "          analysis products\n"
default: default-dbg-correct

_HELP_STRING += "    default-dbg-perf: \n"
_HELP_STRING += "        - Run the default kernel ($KERNEL_DEFAULT) and generate all of the\n"
_HELP_STRING += "          analysis products - for debugging performance\n"
default-dbg-perf: RISCV_DEFINES += -Dbsg_tiles_X=8
default-dbg-perf: RISCV_DEFINES += -Dbsg_tiles_Y=4
default-dbg-perf: CXXFLAGS += -DDEBUG_PERFORMANCE
default-dbg-perf: stats graphs pc_stats

_HELP_STRING += "    default-dbg-correct: \n"
_HELP_STRING += "        - Run the default kernel ($KERNEL_DEFAULT) and generate all of the\n"
_HELP_STRING += "          analysis products - for debugging correctness\n"
default-dbg-correct: RISCV_DEFINES += -Dbsg_tiles_X=2
default-dbg-correct: RISCV_DEFINES += -Dbsg_tiles_Y=2
default-dbg-correct: CXXFLAGS += -DDEBUG_CORRECTNESS
default-dbg-correct: stats graphs pc_stats

_HELP_STRING += "    default-benchmark: \n"
_HELP_STRING += "        - Run the default kernel ($KERNEL_DEFAULT) and generate all of the\n"
_HELP_STRING += "          analysis products - for benchmarking\n"
default-benchmark: RISCV_DEFINES += -Dbsg_tiles_X=8
default-benchmark: RISCV_DEFINES += -Dbsg_tiles_Y=4
default-benchmark: CXXFLAGS += -DDEBUG_CORRECTNESS
default-benchmark: stats graphs pc_stats

_HELP_STRING += "    analysis: \n"
_HELP_STRING += "        - Launch indpendent cosimulation executions of each kernel version.\n"
_HELP_STRING += "          When execution finishes, it generates the analysis products for \n"
_HELP_STRING += "          each kernel in each respective kernel/version_name/ directory\n"
analysis: $(foreach v,$(VERSIONS),kernel/$v/stats kernel/$v/graphs kernel/$v/pc_stats)

_HELP_STRING += "    all: \n"
_HELP_STRING += "        - Launch both the default and analysis target\n"
all: analysis default

.DEFAULT_GOAL = help
_HELP_STRING += "    help: \n"
_HELP_STRING += "        - Output a friendly help message.\n"
help:
	@echo -e $(HELP_STRING)

# Always re-run, if asked.
.PHONY: default analysis help

# These last three lines ensure that _HELP_STRING is appended to the top of
# whatever else comes before it.
_HELP_STRING += "\n"
_HELP_STRING += $(HELP_STRING)
HELP_STRING := $(_HELP_STRING)
