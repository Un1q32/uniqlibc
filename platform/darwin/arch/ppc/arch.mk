BUILTINS := udivdi3 umoddi3 fixunstfdi floatditf gcc_qadd gcc_qsub gcc_qmul gcc_qdiv
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -Iinclude -std=c99 -fno-stack-protector $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/udivdi3.o: compiler-rt/lib/builtins/udivdi3.c
	$(BCC)

src/builtins/umoddi3.o: compiler-rt/lib/builtins/umoddi3.c
	$(BCC)

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

src/builtins/gcc_qdiv.o: compiler-rt/lib/builtins/ppc/gcc_qdiv.c
	$(BCC)
