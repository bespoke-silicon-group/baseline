################################################################################
# Tools
################################################################################

RISCV_GCC     ?= $(RISCV_BIN_DIR)/riscv32-unknown-elf-dramfs-gcc
RISCV_GXX     ?= $(RISCV_BIN_DIR)/riscv32-unknown-elf-dramfs-g++
RISCV_ELF2HEX ?= LD_LIBRARY_PATH=$(RISCV_BIN_DIR)/../lib $(RISCV_BIN_DIR)/elf2hex
RISCV_OBJCOPY ?= $(RISCV_BIN_DIR)/riscv32-unknown-elf-dramfs-objcopy
RISCV_AR      ?= $(RISCV_BIN_DIR)/riscv32-unknown-elf-dramfs-ar
RISCV_LD      ?= $(RISCV_GCC)
RISCV_LINK    ?= $(RISCV_GCC) -t -T $(LINK_SCRIPT) $(RISCV_LDFLAGS)
RISCV_OBJDUMP ?= $(RISCV_BIN_DIR)/riscv32-unknown-elf-dramfs-objdump
