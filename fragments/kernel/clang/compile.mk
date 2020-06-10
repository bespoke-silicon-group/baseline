ARCH_OP=rv32imaf
ABI=ilp32f
CPU_OP = hb-rv32

%.rvo: RISCV_INCLUDES += $(KERNEL_INCLUDES)

LLVM_DIR         ?= $(BSG_MANYCORE_DIR)/software/riscv-tools/llvm/llvm-install
LLVM_CLANG       ?= $(LLVM_DIR)/bin/clang
LLVM_CLANGXX     ?= $(LLVM_DIR)/bin/clang++
LLVM_OPT         ?= $(LLVM_DIR)/bin/opt
LLVM_LLC         ?= $(LLVM_DIR)/bin/llc
LLVM_LIB         ?= $(LLVM_DIR)/lib
LLVM_INCL        ?= $(LLVM_DIR)/include/c++/v1
RUNTIME_FNS      ?= $(BSG_MANYCORE_DIR)/software/bsg_manycore_lib/bsg_tilegroup.h

CLANG_TARGET_OPTS ?= --target=riscv32 -march=$(ARCH_OP) -mabi=$(ABI)
LLC_TARGET_OPTS ?= -march=riscv32 -mcpu=$(CPU_OP)

#some flags are not supported by clang, so redefine the cxx flags here
CLANG_RISCV_CFLAGS := $(OPT_LEVEL) $(DEBUG_FLAGS) -static -ffast-math -fno-common -ffp-contract=off 
CLANG_RISCV_CXXFLAGS := --sysroot=$(RISCV_BIN_DIR)/../riscv32-unknown-elf-dramfs \
    -I$(RISCV_BIN_DIR)/../riscv32-unknown-elf-dramfs/include/c++/9.2.0 \
		-I$(RISCV_BIN_DIR)/../riscv32-unknown-elf-dramfs/include/c++/9.2.0/riscv32-unknown-elf-dramfs  
CLANG_RISCV_CXXFLAGS += -v -std=c++11 -stdlib=libstdc++ $(OPT_LEVEL) $(DEBUG_FLAGS) -static -ffast-math -fno-common -ffp-contract=off 

$(LLVM_DIR):
	$(error $(shell echo -e "$(RED)BSG MAKE ERROR: LLVM Has not been built! Please run the Setup instructions in README.md $(_REPO_ROOT)$(NC)")

# Emit -O0 so that loads to consecutive memory locations aren't combined
# Opt can run optimizations in any order, so it doesn't matter
%.ll: %.c $(LLVM_DIR) $(RUNTIME_FNS)
	$(LLVM_CLANG) $(CLANG_RISCV_CFLAGS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -emit-llvm -c -S $< -o $@ |& tee $*.clang.log

# do the same for C++ sources
%.ll: %.cpp $(LLVM_DIR) $(RUNTIME_FNS)
	$(LLVM_CLANGXX) $(CLANG_TARGET_OPTS) $(CLANG_RISCV_CXXFLAGS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -c -emit-llvm  $< -o $@ |& tee $*.clang.log

%.ll.s: %.ll
	$(LLVM_LLC) $(LLC_TARGET_OPTS) $< -o $@

%.rvo: %.ll.s
	$(RISCV_GCC) $(RISCV_GCC_OPTS) $(OPT_LEVEL) -c $< -o $@

.PRECIOUS: %.ll %.ll.s

kernel.compile.clean:
	rm -rf *.rvo *.clang.log *.rva *.a *.ll *.ll.s
