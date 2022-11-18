#ifndef PROFGREP_H
#define PROFGREP_H

#include <stdio.h>

#include <tbs/types.h>

/* used as a reminder we're working in UTF-8 octets, and NOT ASCII chars */
typedef unsigned char utf8c;

#ifndef NDEBUG
#	define dbgprintf(...) \
		fprintf(stderr, __VA_ARGS__)
#else
#	define dbgprintf(...) \
		((void*)0)
#endif

#endif
