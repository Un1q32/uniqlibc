BUILTINS := extenddftf2 addtf3 subtf3 multf3 divtf3 comparetf2 floatunditf floatunsitf floatsitf fixunstfdi fixtfsi fixtfdi fp_mode
ifdef RISCV_SOFTFLOAT
ifeq ($(RISCV_SOFTFLOAT),1)
BUILTINS += fixsfsi addsf3 subsf3 mulsf3 divsf3
endif
BUILTINS += adddf3 muldf3 extendsfdf2 truncdfsf2 comparesf2
endif
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -Iinclude -std=c99 -fno-stack-protector $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/extenddftf2.o: compiler-rt/lib/builtins/extenddftf2.c
	$(BCC)

src/builtins/addtf3.o: compiler-rt/lib/builtins/addtf3.c
	$(BCC)

src/builtins/subtf3.o: compiler-rt/lib/builtins/subtf3.c
	$(BCC)

src/builtins/multf3.o: compiler-rt/lib/builtins/multf3.c
	$(BCC)

src/builtins/divtf3.o: compiler-rt/lib/builtins/divtf3.c
	$(BCC)

src/builtins/comparetf2.o: compiler-rt/lib/builtins/comparetf2.c
	$(BCC)

src/builtins/floatunditf.o: compiler-rt/lib/builtins/floatunditf.c
	$(BCC)

src/builtins/floatunsitf.o: compiler-rt/lib/builtins/floatunsitf.c
	$(BCC)

src/builtins/floatsitf.o: compiler-rt/lib/builtins/floatsitf.c
	$(BCC)

src/builtins/fixunstfdi.o: compiler-rt/lib/builtins/fixunstfdi.c
	$(BCC)

src/builtins/fixtfsi.o: compiler-rt/lib/builtins/fixtfsi.c
	$(BCC)

src/builtins/fixtfdi.o: compiler-rt/lib/builtins/fixtfdi.c
	$(BCC)

src/builtins/fp_mode.o: compiler-rt/lib/builtins/riscv/fp_mode.c
	$(BCC)

ifdef RISCV_SOFTFLOAT

ifeq ($(RISCV_SOFTFLOAT),1)

src/builtins/fixsfsi.o: compiler-rt/lib/builtins/fixsfsi.c
	$(BCC)

src/builtins/addsf3.o: compiler-rt/lib/builtins/addsf3.c
	$(BCC)

src/builtins/subsf3.o: compiler-rt/lib/builtins/subsf3.c
	$(BCC)

src/builtins/mulsf3.o: compiler-rt/lib/builtins/mulsf3.c
	$(BCC)

src/builtins/divsf3.o: compiler-rt/lib/builtins/divsf3.c
	$(BCC)

endif

src/builtins/adddf3.o: compiler-rt/lib/builtins/adddf3.c
	$(BCC)

src/builtins/muldf3.o: compiler-rt/lib/builtins/muldf3.c
	$(BCC)

src/builtins/extendsfdf2.o: compiler-rt/lib/builtins/extendsfdf2.c
	$(BCC)

src/builtins/truncdfsf2.o: compiler-rt/lib/builtins/truncdfsf2.c
	$(BCC)

src/builtins/comparesf2.o: compiler-rt/lib/builtins/comparesf2.c
	$(BCC)

endif
