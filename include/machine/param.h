#ifndef _MACHINE_PARAM_H_
#define _MACHINE_PARAM_H_

#if defined(__arm__) || defined(__aarch64__)
#include <machine/arm/param.h>
#elif defined(__i386__) || defined(__x86_64__)
#include <machine/x86/param.h>
#elif defined(__riscv)
#include <machine/riscv/param.h>
#elif defined(__powerpc__) || defined(__POWERPC__)
#include <machine/powerpc/param.h>
#else
#error architecture not supported
#endif

#endif
