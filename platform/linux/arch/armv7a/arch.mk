BUILTINS := fixunsdfdi floatundidf udivdi3 umoddi3 umodsi3 modsi3 divsi3 udivsi3 aeabi_div0 aeabi_uldivmod udivmoddi4 aeabi_uidivmod udivmodsi4
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

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

src/builtins/aeabi_div0.o: compiler-rt/lib/builtins/arm/aeabi_div0.c
	$(BCC)

src/builtins/aeabi_uldivmod.o: compiler-rt/lib/builtins/arm/aeabi_uldivmod.S
	$(BCC)

src/builtins/udivmoddi4.o: compiler-rt/lib/builtins/udivmoddi4.c
	$(BCC)

src/builtins/aeabi_uidivmod.o: compiler-rt/lib/builtins/arm/aeabi_uidivmod.S
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

src/builtins/udivmodsi4.o: compiler-rt/lib/builtins/udivmodsi4.c
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

src/builtins/udivmodsi4.o: compiler-rt/lib/builtins/arm/udivmodsi4.S
	$(BCC)

endif
