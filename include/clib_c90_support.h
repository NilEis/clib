#ifndef CLIB_C90_SUPPORT_H
#define CLIB_C90_SUPPORT_H

#if __STDC_VERSION__ >= 199901L
/* "inline" is a keyword */
/* "restrict" is a keyword */
#else
#define inline static
#define restrict
#endif

#endif /* CLIB_C90_SUPPORT_H */