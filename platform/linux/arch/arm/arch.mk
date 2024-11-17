BUILTINS := fixunsdfdi floatundidf udivdi3 umoddi3 umodsi3 modsi3 divsi3 udivsi3 aeabi_div0 aeabi_uldivmod udivmoddi4 aeabi_uidivmod udivmodsi4 floatsidf fixdfsi comparedf2 comparesf2 adddf3 subdf3 muldf3 addsf3 subsf3 mulsf3 divsf3 fp_mode fixsfsi extendsfdf2 truncdfsf2 clzsi2 aeabi_memset
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

src/builtins/floatsidf.o: compiler-rt/lib/builtins/floatsidf.c
	$(BCC)

src/builtins/fixdfsi.o: compiler-rt/lib/builtins/fixdfsi.c
	$(BCC)

src/builtins/comparedf2.o: compiler-rt/lib/builtins/comparedf2.c
	$(BCC)

src/builtins/comparesf2.o: compiler-rt/lib/builtins/comparesf2.c
	$(BCC)

src/builtins/adddf3.o: compiler-rt/lib/builtins/adddf3.c
	$(BCC)

src/builtins/subdf3.o: compiler-rt/lib/builtins/subdf3.c
	$(BCC)

src/builtins/muldf3.o: compiler-rt/lib/builtins/muldf3.c
	$(BCC)

src/builtins/addsf3.o: compiler-rt/lib/builtins/addsf3.c
	$(BCC)

src/builtins/subsf3.o: compiler-rt/lib/builtins/subsf3.c
	$(BCC)

src/builtins/mulsf3.o: compiler-rt/lib/builtins/mulsf3.c
	$(BCC)

src/builtins/divsf3.o: compiler-rt/lib/builtins/divsf3.c
	$(BCC)

src/builtins/fixsfsi.o: compiler-rt/lib/builtins/fixsfsi.c
	$(BCC)

src/builtins/extendsfdf2.o: compiler-rt/lib/builtins/extendsfdf2.c
	$(BCC)

src/builtins/truncdfsf2.o: compiler-rt/lib/builtins/truncdfsf2.c
	$(BCC)

src/builtins/fp_mode.o: compiler-rt/lib/builtins/arm/fp_mode.c
	$(BCC)

src/builtins/aeabi_memset.o: compiler-rt/lib/builtins/arm/aeabi_memset.S
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

src/builtins/clzsi2.o: compiler-rt/lib/builtins/clzsi2.c
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

src/builtins/clzsi2.o: compiler-rt/lib/builtins/arm/clzsi2.S
	$(BCC)

endif
