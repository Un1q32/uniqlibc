#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef NDEBUG

#define assert(ignore) ((void)0)

#else

#include <stdio.h>
#include <stdlib.h>

#define assert(expr)                                                           \
  ((expr) ? (void)0                                                            \
          : ((void)fprintf(stderr, "%s:%d: failed assertion `%s'\n", __FILE__, \
                           __LINE__, #expr),                                   \
             abort()))

#endif

#ifndef __cplusplus
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define static_assert _Static_assert
#endif
#endif

#endif
