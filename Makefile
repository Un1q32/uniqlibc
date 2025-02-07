ARCH := x86_64
OS := linux
AR := $(shell command -v llvm-ar 2>/dev/null || echo ar)

COMPILER_RT_VERSION := 19.1.7

CFLAGS := -Wall -Wextra -pedantic -DDEBUG
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

all: sysroot/usr/include sysroot/usr/lib

release: OPTFLAGS := -O2
release: CFLAGS := -Wall -Wextra -pedantic
release: all

tests: $(TESTEXES)

sysroot/usr/include: $(HEADERS)
	@printf "Installing headers...\n"
	$(V)rm -rf $@
	$(V)mkdir -p sysroot/usr
	$(V)cp -r include sysroot/usr

sysroot/usr/lib: crt/crt0.o crt/crti.o crt/crtn.o src/libc.a
	@printf "Installing libraries...\n"
	$(V)rm -rf $@
	$(V)mkdir -p $@
	$(V)cp src/libc.a $@
	$(V)cp crt/crt*.o $@
	$(V)for lib in libSystem.a libgcc.a; do ln -s libc.a $@/$$lib; done
	$(V)for crt in crt1.o crt1.10.5.o; do ln -s crt0.o $@/$$crt; done

tests/bin/%: tests/%.c all
	@printf " \033[1;32mCC\033[0m $@\n"
	$(V)$(CC) --sysroot sysroot -std=c99 -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) --sysroot sysroot $(LDFLAGS) $(OPTFLAGS) -nostdlib tests/$*.o sysroot/usr/lib/crt0.o sysroot/usr/lib/libc.a -o $@

src/libc.a: builtins $(OBJS)
	@printf " \033[1;34mAR\033[0m libc.a\n"
	$(V)$(AR) rcs $@ src/*/*.o platform/$(OS)/src/*.o

crt/crt0.o: crt/start.o crt/cstart.o
	@printf " \033[1;34mLD\033[0m crt0.o\n"
	$(V)$(CC) --sysroot sysroot $(LDFLAGS) $(OPTFLAGS) -nostdlib -r $^ -o $@

crt/start.o $(ASMS:.S=.o): %.o: %.S $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) --sysroot sysroot -Iinclude -D__UNIQLIBC_PRIVATE_API $(CFLAGS) $(OPTFLAGS) -c $< -o $@

%.o: %.c sysroot/usr/include $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -std=c99 -fno-builtin --sysroot sysroot -Iinclude -D__UNIQLIBC_PRIVATE_API $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sysroot/* tests/*.o tests/bin/* src/libc.a crt/*.o src/*/*.o platform/*/src/*.o platform/*/arch/*/*.o

distclean: clean
	$(V)rm -rf compiler-rt .clangd

compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)rm -rf compiler-rt
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | xz -d | tar -x
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

builtins: compiler-rt sysroot/usr/include $(HEADERS)
	@$(MAKE) -f platform/$(OS)/arch/$(ARCH)/arch.mk NOASM=$(NOASM) CC="$(CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)" ABI="$(ABI)"

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, -D__UNIQLIBC_PRIVATE_API]\n' > .clangd
