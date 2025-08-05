# uniqlibc

## Platform support:

- **Linux**
    - i386, x86_64, arm, aarch64, riscv64, powerpc
- **Darwin**
    - i386, x86_64, x86_64h, armv4t, armv5, armv6, armv7, armv7s, armv7k, arm64*, arm64e*, arm64_32*
    - arm64 Darwin requires a patched kernel, as XNU doesn't allow static arm64 binaries by default

## Building:

#### To build for x86_64 Linux:

```sh
make release
```

#### To build for x86_64 Darwin:

```sh
make release OS=darwin
```

#### To build for arm Linux:

```sh
make release ARCH=arm
```

#### To build a debug library for x86_64 Linux:

```sh
make
```

#### To build the tests for x86_64 Linux:

```sh
make tests
```

## Porting:

### To a new architecture:

- Add some headers for your architecture to `include/machine`
- Add a folder and an arch.mk to `platform/<os>/arch/<arch>`
- Add your architecture's code to assembly files, currently just `crt/start.S` and `platform/<os>/src/syscall.S`
- (Linux only) add your architecture's syscall definitions to `include/sys/linux/syscall.h`

### To a new kernel:

- Add some headers for your kernel to `include/sys/<os>`
- Add syscalls in `platform/<os>/src/`, this should provide functions like `read()`, `write()`, `open()`, etc
  Try to use as little assembly as possible, the only assembly should be your `syscall()` function, which all other functions will use
- Add a platform.mk file to `platform/<os>/platform.mk` (this can add to variables like CFLAGS or be empty)
- Add a folder and an arch.mk to `platform/<os>/arch/<arch>`

## TODO:
- Add support for %a and %g formats in printf.
- Update the whole codebase with comments, especially the stdio parts.
- Optimize malloc, it gets slower when there are a lot of allocations
