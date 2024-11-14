ARCH := x86_64
OS := darwin
AR := $(shell command -v llvm-ar 2>/dev/null || echo ar)

COMPILER_RT_VERSION := 19.1.3

CFLAGS := -Wall -Wextra -Wpedantic -DDEBUG
OPTFLAGS := -g
LDFLAGS := -static

include platform/$(OS)/platform.mk

ifdef ABI
CC = clang -target $(ARCH)-$(OS)-$(ABI)
else
CC = clang -target $(ARCH)-$(OS)
endif

SRCS := $(wildcard src/*/*.c) $(wildcard platform/$(OS)/src/*.c) $(wildcard platform/$(OS)/arch/$(ARCH)/*.c)
ASMS := $(wildcard src/*/*.S) $(wildcard platform/$(OS)/src/*.S) $(wildcard platform/$(OS)/arch/$(ARCH)/*.S)
OBJS := $(SRCS:.c=.o) $(ASMS:.S=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:tests/%.c=tests/bin/%)

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h) $(wildcard include/*/*/*.h)

ifndef VERBOSE
V := @
endif

.PHONY: all release tests clean clangd

all: sdk/usr/include sdk/usr/lib

release: OPTFLAGS := -O2
release: CFLAGS := -Wall -Wextra -Wpedantic
release: all

tests: $(TESTEXES)

sdk/usr/include: $(HEADERS)
	@printf "Installing headers...\n"
	$(V)rm -rf sdk/usr/include
	$(V)mkdir -p sdk/usr
	$(V)cp -r include sdk/usr

sdk/usr/lib: crt/crt0.o crt/crti.o crt/crtn.o src/libc.a
	@printf "Installing libraries...\n"
	$(V)rm -rf sdk/usr/lib
	$(V)mkdir -p sdk/usr/lib
	$(V)cp src/libc.a sdk/usr/lib
	$(V)cp crt/crt*.o sdk/usr/lib
	$(V)for lib in libSystem.a libgcc.a; do ln -s libc.a sdk/usr/lib/$$lib; done
	$(V)for crt in crt1.o crt1.10.5.o; do ln -s crt0.o sdk/usr/lib/$$crt; done

tests/bin/%: tests/%.c all
	@printf " \033[1;32mCC\033[0m $@\n"
	$(V)$(CC) --sysroot sdk -std=c99 -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) --sysroot sdk $(LDFLAGS) $(OPTFLAGS) -nostdlib sdk/usr/lib/libc.a sdk/usr/lib/crt0.o tests/$*.o -o $@

src/libc.a: builtins $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	$(V)$(AR) rcs $@ $(OBJS) $(wildcard src/builtins/*.o)

crt/crt0.o: crt/cstart.o crt/start.o
	$(V)printf " \033[1;34mLD\033[0m crt0.o\n"
	$(V)$(CC) --sysroot sdk $(LDFLAGS) $(OPTFLAGS) -nostdlib -r $^ -o $@

crt/start.o $(ASMS:.S=.o): %.o: %.S $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) --sysroot sdk -Iinclude -D__UNIQ_LIBC_PRIVATE_API $(CFLAGS) $(OPTFLAGS) -c $< -o $@

%.o: %.c sdk/usr/include $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -std=c99 -fno-builtin --sysroot sdk -Iinclude -D__UNIQ_LIBC_PRIVATE_API $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sdk/* tests/*.o tests/bin/* src/libc.a crt/*.o src/*/*.o platform/*/src/*.o platform/*/arch/*/*.o

distclean: clean
	$(V)rm -rf compiler-rt .clangd

compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)rm -rf compiler-rt
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | xz -d | tar -x
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

builtins: compiler-rt sdk/usr/include $(HEADERS)
	@$(MAKE) -f platform/$(OS)/arch/$(ARCH)/arch.mk NOASM=$(NOASM) CC="$(CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)" ARCH=$(ARCH)

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, -D__UNIQ_LIBC_PRIVATE_API, --target=x86_64-apple-darwin]\n' > .clangd
