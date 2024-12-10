BUILTINS := fixunsdfdi floatundidf udivdi3 umoddi3 umodsi3 modsi3 divsi3 udivsi3 clzdi2
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -Iinclude -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/fixunsdfdi.o: compiler-rt/lib/builtins/fixunsdfdi.c
	$(BCC)

src/builtins/floatundidf.o: compiler-rt/lib/builtins/floatundidf.c
	$(BCC)

src/builtins/udivdi3.o: compiler-rt/lib/builtins/udivdi3.c
	$(BCC)

src/builtins/umoddi3.o: compiler-rt/lib/builtins/umoddi3.c
	$(BCC)

ifdef NOASM

src/builtins/umodsi3.o: compiler-rt/lib/builtins/umodsi3.c
	$(BCC)

src/builtins/modsi3.o: compiler-rt/lib/builtins/modsi3.c
	$(BCC)

src/builtins/divsi3.o: compiler-rt/lib/builtins/divsi3.c
	$(BCC)

src/builtins/udivsi3.o: compiler-rt/lib/builtins/udivsi3.c
	$(BCC)

src/builtins/clzdi2.o: compiler-rt/lib/builtins/clzdi2.c
	$(BCC)

else

src/builtins/umodsi3.o: compiler-rt/lib/builtins/arm/umodsi3.S
	$(BCC)

src/builtins/modsi3.o: compiler-rt/lib/builtins/arm/modsi3.S
	$(BCC)

src/builtins/divsi3.o: compiler-rt/lib/builtins/arm/divsi3.S
	$(BCC)

src/builtins/udivsi3.o: compiler-rt/lib/builtins/arm/udivsi3.S
	$(BCC)

src/builtins/clzdi2.o: compiler-rt/lib/builtins/arm/clzdi2.S
	$(BCC)

endif
