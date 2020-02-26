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

HOST_CSOURCES       :=
HOST_CXXSOURCES     += $(HBGRAPHS_DIR)/src/host/breadth_first_search_host.cpp
HOST_INCLUDES       += -I$(HBGRAPHS_DIR)/include/host
HOST_INCLUDES       += -I$(HBGRAPHS_DIR)/include/common
HOST_INCLUDES       += -I$(GRAPH500_DIR)/generator

$(HOST_TARGET).cosim: $(GRAPH500_DIR)/generator/libgraph500_generator.so
$(HOST_TARGET).cosim: LDFLAGS += -L$(GRAPH500_DIR)/generator
$(HOST_TARGET).cosim: LDFLAGS += -Wl,-rpath=$(GRAPH500_DIR)/generator
$(HOST_TARGET).cosim: LDFLAGS += -lgraph500_generator

$(GRAPH500_DIR)/generator/libgraph500_generator.so:
	$(MAKE) -C $(GRAPH500_DIR)/generator

-include $(FRAGMENTS_PATH)/host/cosim.mk
