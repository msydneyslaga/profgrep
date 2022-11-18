#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
	const char *str;
	u16 len;
	u16 index;
} ahocora_pair;

static const char *dictionary[] =
{
	"fuck",
	"shit",
	"cunt",
	"bitch",
	"whore",
	"cum",
	NULL,
};

ahocora_pair wordlist[sizeof(dictionary)];

ahocora_pair *init_dictionary()
{
	memset(wordlist, 0, sizeof(wordlist));
	u32 i = 0;
	for(const char **w = dictionary; *w != NULL; w += 1)
	{
		u16 l;
		for(l = 0; (*w)[l] != 0; l++)
			;

		wordlist[i].str = *w;
		wordlist[i].len = l;

		/* printf("{'%s', %d}\n", wordlist[i].str, wordlist[i].len); */
		i++;
	}

	assert(wordlist[0].index == 0);

	return wordlist;
}
