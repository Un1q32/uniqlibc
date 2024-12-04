BUILTINS := fixunstfdi floatditf gcc_qadd gcc_qsub gcc_qmul
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/fixunstfdi.o: compiler-rt/lib/builtins/ppc/fixunstfdi.c
	$(BCC)

src/builtins/floatditf.o: compiler-rt/lib/builtins/ppc/floatditf.c
	$(BCC)

src/builtins/gcc_qadd.o: compiler-rt/lib/builtins/ppc/gcc_qadd.c
	$(BCC)

src/builtins/gcc_qsub.o: compiler-rt/lib/builtins/ppc/gcc_qsub.c
	$(BCC)

src/builtins/gcc_qmul.o: compiler-rt/lib/builtins/ppc/gcc_qmul.c
	$(BCC)
