%.dis: %.riscv
	$(RISCV_OBJDUMP) -M numeric --disassemble-all -S $< > $@

%.S: %.c
	$(RISCV_GCC) $(RISCV_GCC_OPTS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -S -fverbose-asm $< -o $@ 

%.S: %.cpp $(BSG_MACHINE_PATH)/Makefile.machine.include
	$(RISCV_GXX) $(RISCV_GXX_OPTS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -S -fverbose-asm $< -o $@
