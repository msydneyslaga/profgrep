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

/* static ahocora_pair *init_dictionary() */
/* { */
/* 	memset(wordlist, 0, sizeof(wordlist)); */
/* 	u32 i = 0; */
/* 	for(const char **w = dictionary; *w != NULL; w += 1) */
/* 	{ */
/* 		u16 l; */
/* 		for(l = 0; (*w)[l] != 0; l++) */
/* 			; */

/* 		wordlist[i].str = *w; */
/* 		wordlist[i].len = l; */

/* 		i++; */
/* 	} */

/* 	assert(wordlist[0].index == 0); */

/* 	return wordlist; */
/* } */

#endif
