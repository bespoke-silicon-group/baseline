################################################################################
# BSG Manycore Machine Configuration
################################################################################

# Import configuration from BSG_MACHINE_PATH.
include $(BSG_MACHINE_PATH)/Makefile.machine.include

# Set architecture variables (if not already set)
bsg_global_X ?= $(BSG_MACHINE_GLOBAL_X)
bsg_global_Y ?= $(BSG_MACHINE_GLOBAL_Y)

MACHINE_CRT_OBJ = $(BSG_MANYCORE_MACHINE_NAME)_crt.o
