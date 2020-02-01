RISCV_CCPPFLAGS += -mno-fdiv

%.rvo: %.c
	$(RISCV_GCC) $(RISCV_CFLAGS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -c $< -o $@ |& tee $*.gcc.log

%.rvo: %.cpp
	$(RISCV_GXX) $(RISCV_CXXFLAGS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -c $< -o $@ |& tee $*.gcc.log

%.rvo: %.S
	$(RISCV_GCC) $(RISCV_GCC_OPTS) $(RISCV_DEFINES) $(RISCV_INCLUDES) -D__ASSEMBLY__=1 -c $< -o $@ |& tee $*.gcc.log
