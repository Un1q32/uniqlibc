LDFLAGS += -fuse-ld=lld
ifeq ($(ARCH),arm)
ABI := eabi
endif
