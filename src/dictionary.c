#include <profgrep/profgrep.h>
#include <profgrep/dictionary.h>

#define WORDS(o) \
	o("fuck") \
	o("shit") \
	o("cunt") \
	o("bitch") \
	o("whore") \
	o("cum")

#define STRING_LEN_PAIR(word) \
	{word, sizeof(word) - 1},

ahocora_pair default_dictionary[] =
{
	WORDS(STRING_LEN_PAIR)
	{NULL, 0}
};

ahocora_pair *parse_dictionary(FILE *fp)
{
	/* pg_buf buf = pgbuf_init(); */

	return NULL;
}

