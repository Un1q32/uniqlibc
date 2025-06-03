ifneq ($(shell uname -s),Darwin)
LD64_VERSION := 762
LDFLAGS += -fuse-ld=ld64 -mlinker-version=$(LD64_VERSION)
endif
