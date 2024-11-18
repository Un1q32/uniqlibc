# uniqlibc

## Platform support:

- **Darwin**
    - i386, x86_64, x86_64h, armv4t, armv5, armv6, armv7, armv7s, armv7k, arm64*, arm64e*, arm64_32*
    - arm64 Darwin requires a patched kernel, as XNU doesn't allow static arm64 binaries by default
- **FreeBSD**
    - i386, x86_64, arm, aarch64
- **Linux**
    - i386, x86_64

## Building:

#### To build for x86_64 Darwin:

```sh
make release
```

#### To build for armv7 Darwin:

```sh
make release ARCH='armv7'
```

#### To build for x86_64 FreeBSD:

```sh
make release OS='freebsd'
```

#### To build the tests for x86_64 Darwin:

```sh
make tests
```

## TODO
- Darwin nanosleep is *really* bad
- make arc4random work in chroot
- make signal functions work on linux
