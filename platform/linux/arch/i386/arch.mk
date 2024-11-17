BUILTINS := udivdi3 umoddi3 fixunsxfdi
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/fixunsxfdi.o: compiler-rt/lib/builtins/fixunsxfdi.c
	$(BCC)

ifdef NOASM

src/builtins/udivdi3.o: compiler-rt/lib/builtins/udivdi3.c
	$(BCC)

src/builtins/umoddi3.o: compiler-rt/lib/builtins/umoddi3.c
	$(BCC)

else

src/builtins/udivdi3.o: compiler-rt/lib/builtins/i386/udivdi3.S
	$(BCC)

src/builtins/umoddi3.o: compiler-rt/lib/builtins/i386/umoddi3.S
	$(BCC)

endif
