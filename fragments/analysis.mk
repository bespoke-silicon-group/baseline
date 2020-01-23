%.dis: %.riscv
	$(RISCV_OBJDUMP) -M numeric --disassemble-all -S $<

%.S: %.c $(BSG_MACHINE_PATH)/Makefile.machine.include
	$(RISCV_GCC) $(RISCV_GCC_OPTS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -S -fverbose-asm $< -o $@ |& tee $*.comp.log

%.S: %.cpp $(BSG_MACHINE_PATH)/Makefile.machine.include
	$(RISCV_GXX) $(RISCV_GXX_OPTS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -S -fverbose-asm $< -o $@ |& tee $*.comp.log
