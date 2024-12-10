BUILTINS := extenddftf2 floatsitf addtf3 subtf3 multf3 comparetf2 floatunditf fixunstfdi fixtfsi fp_mode
_BUILTINS := $(addprefix src/builtins/,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(CC) --sysroot sdk -Iinclude -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/extenddftf2.o: compiler-rt/lib/builtins/extenddftf2.c
	$(BCC)

src/builtins/floatsitf.o: compiler-rt/lib/builtins/floatsitf.c
	$(BCC)

src/builtins/addtf3.o: compiler-rt/lib/builtins/addtf3.c
	$(BCC)

src/builtins/subtf3.o: compiler-rt/lib/builtins/subtf3.c
	$(BCC)

src/builtins/multf3.o: compiler-rt/lib/builtins/multf3.c
	$(BCC)

src/builtins/comparetf2.o: compiler-rt/lib/builtins/comparetf2.c
	$(BCC)

src/builtins/floatunditf.o: compiler-rt/lib/builtins/floatunditf.c
	$(BCC)

src/builtins/fixunstfdi.o: compiler-rt/lib/builtins/fixunstfdi.c
	$(BCC)

src/builtins/fixtfsi.o: compiler-rt/lib/builtins/fixtfsi.c
	$(BCC)

src/builtins/fp_mode.o: compiler-rt/lib/builtins/aarch64/fp_mode.c
	$(BCC)
