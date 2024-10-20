#ifndef _MACHINE_PARAM_H_
#define _MACHINE_PARAM_H_

#if defined(__arm__) || defined(__aarch64__)
#include <machine/arm/param.h>
#elif defined(__i386__) || defined(__x86_64__)
#include <machine/x86/param.h>
#elif defined(__ppc__)
#include <machine/ppc/param.h>
#else
#error architecture not supported
#endif

#endif
