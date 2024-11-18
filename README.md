# uniqlibc

A portable implementation of the POSIX C standard library.

## Platform support:

- **Linux**
    - i386, x86_64, arm, aarch64, riscv64
- **FreeBSD**
    - i386, x86_64, arm, aarch64, riscv64
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

#### To build the tests for x86_64 Linux:

```sh
make tests
```

## TODO
- Darwin nanosleep is *really* bad
- make arc4random work in chroot
- make signal functions work on linux
