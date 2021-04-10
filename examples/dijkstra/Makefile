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

BSG_MACHINE_PATH=$(BSG_F1_DIR)/machines/pod_X1Y1_ruche_X16Y8_hbm

################################################################################
# Define the range of versions
################################################################################
# Kernel versions. See kernel/README.md for more information.  Version names do
# not need to use v* and can be any string
VERSIONS = dijkstra small_dijkstra
VERSIONS = dijkstra-v1


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
graphtools-dir := $(_REPO_ROOT)/examples/dijkstra/graph-tools
hammerblade-helpers-dir := $(_REPO_ROOT)/examples/dijkstra/hammerblade-helpers

include $(hammerblade-helpers-dir)/libhammerblade-helpers-host.mk
include $(graphtools-dir)/libgraphtools.mk

$(libgraphtools-interface-libraries):
	$(MAKE) -C $(dir $@)

# C Libraries
KERNEL_CLIBRARIES   +=
# C++ Libraries
KERNEL_CXXLIBRARIES += 

KERNEL_INCLUDES     += -I$(CURRENT_PATH)/kernel/include

# Define the default kernel.cpp file. If KERNEL_DEFAULT is not defined it will
# be set to kernel.cpp in the same directory as this Makefile.
DEFAULT_VERSION     := small_dijkstra
KERNEL_DEFAULT      := kernel/$(DEFAULT_VERSION)/kernel.cpp

################################################################################
# Include the kernel build rules (This must be included after KERNEL_*LIBRARIES,
# KERNEL_DEFAULT, KERNEL_INCLUDES, etc)
################################################################################
_KERNEL_COMPILER := CLANG

-include $(FRAGMENTS_PATH)/kernel/cudalite.mk

################################################################################
# END OF KERNEL-SPECIFIC RULES / START OF HOST-SPECIFIC RULES
################################################################################

################################################################################
# Define the $(HOST_TARGET), the name of the host executable to generate. The
# cosimulation host executable will be called
# $(HOST_TARGET).cosim. HOST_*SOURCES list the host files that should be
# compiled and linked into the executable.
################################################################################

HOST_TARGET         := dijkstra
HOST_TARGET_EXE     := $(HOST_TARGET).profile
HOST_CSOURCES       := 
HOST_CXXSOURCES     := $(HOST_TARGET).cpp
HOST_INCLUDES       := -I$(CURRENT_PATH)

CXXFLAGS += $(libhammerblade-helpers-host-interface-cxxflags)
CXXFLAGS += $(libgraphtools-interface-cxxflags)

LDFLAGS  += $(libgraphtools-interface-ldflags)
LDFLAGS  += $(libhammerblade-interface-ldflags)

################################################################################
# Include the Cosimulation host build rules (This must be included after
# HOST_*SOURCES, HOST_TARGET, HOST_INCLUDES, etc)
################################################################################
-include $(FRAGMENTS_PATH)/host/cosim.mk
$(HOST_TARGET_EXE): $(libgraphtools-interface-libraries)
$(HOST_TARGET_EXE): $(libhammerblade-helpers-host-interface-libraries)
$(HOST_TARGET).o: $(libgraphtools-interface-headers)
$(HOST_TARGET).o: $(libhammerblade-helpers-host-interface-headers)

# $1 = base-version
# $2 = type
# $3 = scale
# $4 = edges
# $5 = root
# $6 = goal
GENERATED		:=
VERSIONS-graph500	:=
VERSIONS-linear		:=
VERSIONS-dijkstra	:=
VERSIONS-small_dijkstra :=

define generate-dijkstra-for-input
# add to version lists
VERSIONS           += $(1)-$(2)-scale$(3)-$(4)edges
VERSIONS-$(1)      += $(1)-$(2)-scale$(3)-$(4)edges
VERSIONS-$(2)      += $(1)-$(2)-scale$(3)-$(4)edges
VERSIONS-generated += $(1)-$(2)-scale$(3)-$(4)edges
# rule for generating the kernel directory
kernel/$(1)-$(2)-scale$(3)-$(4)edges: kernel/$1
	cp -r $$< $$@
# add command line arguments
kernel/$(1)-$(2)-scale$(3)-$(4)edges/$(HOST_TARGET).log: C_ARGS += $(2)
kernel/$(1)-$(2)-scale$(3)-$(4)edges/$(HOST_TARGET).log: C_ARGS += $(3)
kernel/$(1)-$(2)-scale$(3)-$(4)edges/$(HOST_TARGET).log: C_ARGS += $(4)

# add to generated versions
GENERATED      += kernel/$(1)-$(2)-scale$(3)-$(4)edges
GENERATED-$(1) += kernel/$(1)-$(2)-scale$(3)-$(4)edges
GENERATED-$(2) += kernel/$(1)-$(2)-scale$(3)-$(4)edges
endef

# tiny tree graph
$(eval $(call generate-dijkstra-for-input,dijkstra,tree,7,128))
$(eval $(call generate-dijkstra-for-input,small_dijkstra,tree,7,128))
$(eval $(call generate-dijkstra-for-input,tree_dijkstra,tree,7,128))
$(eval $(call generate-dijkstra-for-input,small_tree_dijkstra,tree,7,128))
# tiny list graph
$(eval $(call generate-dijkstra-for-input,dijkstra,list,7,128))
$(eval $(call generate-dijkstra-for-input,small_dijkstra,list,7,128))
$(eval $(call generate-dijkstra-for-input,list_dijkstra,list,7,128))
$(eval $(call generate-dijkstra-for-input,small_list_dijkstra,list,7,128))
# tiny graph
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,7,128))
$(eval $(call generate-dijkstra-for-input,small_dijkstra,graph500,7,128))
# small graph
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,10,$(shell echo 4*1024|bc)))
$(eval $(call generate-dijkstra-for-input,dijkstra-v1,graph500,10,$(shell echo 4*1024|bc)))
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,10,512))
$(eval $(call generate-dijkstra-for-input,tree_dijkstra,tree,10,512))
$(eval $(call generate-dijkstra-for-input,list_dijkstra,list,10,512))
# medium graph
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,16,$(shell echo  64*1024|bc)))
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,16,$(shell echo  32*1024|bc)))
$(eval $(call generate-dijkstra-for-input,tree_dijkstra,tree,16,$(shell echo 32*1024|bc)))
$(eval $(call generate-dijkstra-for-input,list_dijkstra,list,16,$(shell echo 32*1024|bc)))
# medium-large graph
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,20,$(shell  echo 16*1024*1024|bc)))
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,20,$(shell  echo 512*1024|bc)))
$(eval $(call generate-dijkstra-for-input,list_dijkstra,list,20,$(shell echo 512*1024|bc)))
$(eval $(call generate-dijkstra-for-input,tree_dijkstra,tree,20,$(shell echo 512*1024|bc)))
# large graph
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,24,$(shell  echo 256*1024*1024|bc)))
$(eval $(call generate-dijkstra-for-input,dijkstra,graph500,24,$(shell  echo 8*1024*1024|bc)))
$(eval $(call generate-dijkstra-for-input,list_dijkstra,list,24,$(shell echo 8*1024*1024|bc)))
$(eval $(call generate-dijkstra-for-input,tree_dijkstra,tree,24,$(shell echo 8*1024*1024|bc)))

.PHONY: graph500-stats

graph500-stats: generate
graph500-stats: $(foreach v,$(VERSIONS-graph500),kernel/$v/stats)

small_dijkstra-stats: generate
small_dijkstra-stats: $(foreach v,$(VERSIONS-small_dijkstra),kernel/$v/stats)

list-stats: generate
list-stats: $(foreach v,$(VERSIONS-list),kernel/$v/stats)

all-stats: generate
all-stats: $(foreach v,$(VERSIONS-generated),kernel/$v/stats)

dijkstra-v1-stats: generate
dijkstra-v1-stats: $(foreach v,$(VERSIONS-dijkstra-v1),kernel/$v/stats)

.PHONY: generate purge-generated

generate: $(GENERATED)
purge-generated:
	rm -rf $(GENERATED)


################################################################################
# Define the clean rules. clean calls the makefile-specific cleans, whereas
# users can add commands and dependencies to custom.clean.
################################################################################
version.clean:
	rm -rf kernel/*/*{.csv,.log,.rvo,.riscv,.vpd,.key,.png,.dis}
	rm -rf kernel/*/{stats,pc_stats}
	rm -rf kernel/*/*{.ll,.ll.s}
	rm -rf kernel/*/dramsim3*

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
default: pc_stats graphs stats

_HELP_STRING += "    analysis: \n"
_HELP_STRING += "        - Launch indpendent cosimulation executions of each kernel version.\n"
_HELP_STRING += "          When execution finishes, it generates all the analysis products \n"
_HELP_STRING += "          for each kernel in each respective kernel/<version_name>/ \n"
_HELP_STRING += "          directory\n"
analysis: $(foreach v,$(VERSIONS),kernel/$v/pc_stats kernel/$v/graphs kernel/$v/stats)

_HELP_STRING += "    statistics: \n"
_HELP_STRING += "        - Launch indpendent cosimulation executions of each kernel version.\n"
_HELP_STRING += "          When execution finishes, it generates ONLY the parsed operation \n"
_HELP_STRING += "          stats for each kernel in each respective kernel/<version_name>/ \n"
_HELP_STRING += "          directory\n"
statistics: $(foreach v,$(VERSIONS),kernel/$v/stats)

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
