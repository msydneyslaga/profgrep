#ifndef PROFGREP_H
#define PROFGREP_H

#include <stdio.h>

#include <tbs/types.h>

#include <profgrep/search.h>
#include <profgrep/dictionary.h>

/* used as a reminder we're working in UTF-8 octets, and NOT ASCII chars */
typedef char utf8o;

#ifndef NDEBUG
#	define dbgprintf(...) \
		fprintf(stderr, __VA_ARGS__)
#else
#	define dbgprintf(...) \
		((void*)0)
#endif

struct options
{
	FILE **files;
	uint _files_cx;
	uint _files_alloc;
	pg_search_callback searchcb;
	pg_match_callback matchcb;

	ahocora_pair *dictionary;

	bool caseSensitive;
};

extern struct options opt;

#endif
