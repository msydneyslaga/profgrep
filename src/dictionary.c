#include <stdio.h>

#include <profgrep/profgrep.h>
#include <profgrep/dictionary.h>

#define isIgnorableWhitespace(c) \
	(c == '\n' || c == '\t' || c == '\r')

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

static char escape(FILE *fp)
{
	assert(!feof(fp));
	
	char c = fgetc(fp);
	switch(c)
	{
		case EOF:	return '\\';
		case '\\':	return '\\';
		case 'n':	return '\n';
		case ',':	return ',';
		default:	return '\\';
	}
}

static ahocora_pair read_word(FILE *fp)
{
	char c;

	u16 alloc = 16;
	u16 cx = 0;
	char *b = malloc(alloc);

	if(feof(fp))
	{
		ahocora_pair r = { .str = NULL };
		return r;
	}

	while(!feof(fp) && (c = fgetc(fp)) != ',' && c != -1)
	{
		if(isIgnorableWhitespace(c))
			continue;
		
		if(c == '\\')
			b[cx++] = escape(fp);
		else
			b[cx++] = c;

		if(cx >= alloc)
		{
			alloc *= 1.5;
			b = realloc(b, alloc);
		}
	}

	ahocora_pair r =
	{
		.str = b,
		.len = cx,
		.index = 0,
	};

	if(cx == 0)
	{
		free(b);
		r.str = NULL;
		r.len = 0;
	}

	return r;
}

ahocora_pair *parse_dictionary(FILE *fp)
{
	u32 alloc = 32;
	u32 cx = 0;
	ahocora_pair *dict = malloc(alloc * sizeof(ahocora_pair));
	ahocora_pair w;

	do {
		/* relies on read_word() to add a
		 * terminating element (w.str == NULL) */
		dict[cx++] = w = read_word(fp);
		if(cx >= alloc)
		{
			alloc *= 1.5;
			dict = realloc(dict, alloc * sizeof(ahocora_pair));
		}
	} while(w.str != NULL);


	return dict;
}

void destroy_dictionary(ahocora_pair *dict)
{

}
