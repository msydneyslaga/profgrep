#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <profgrep/profgrep.h>

typedef struct
{
	const char *str;
	u16 len;
	u16 index;
} ahocora_pair;

extern ahocora_pair default_dictionary[];

ahocora_pair *parse_dictionary(FILE *fp);

void destroy_dictionary(ahocora_pair *dict);

#endif
