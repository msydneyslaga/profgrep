#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tbs/types.h>

#include <profgrep/profgrep.h>
#include <profgrep/search.h>
#include <profgrep/buffer.h>
#include <profgrep/dictionary.h>
#include <profgrep/printfv.h>


static bool comparechar_nocase(char a, char b)
{
	/* convert a and b to lowercase before comparison,
	 * if they are uppercase
	 * ('a' - 'A' == 32 == 0x20)*/

	a = (a >= 'A' && a <= 'Z') ? a + 0x20 : a;
	b = (b >= 'A' && b <= 'Z') ? b + 0x20 : b;

	return (a == b);
}

static bool comparechar_case(char a, char b)
{
	return (a == b);
}

/*
 * https://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/02/Small02.pdf
 */
u32 pg_search(pg_buf *inp, ahocora_pair *dictionary, pg_search_callback scb,
		pg_match_callback mcb)
{
	bool (*comparechar)(char, char);

	if(opt.caseSensitive)
		comparechar = comparechar_case;
	else
		comparechar = comparechar_nocase;


	ahocora_pair *w;
	for(u64 i = 0; i < inp->cx; i++)
	{
		/* TOCON: have c be a pointer? */
		char c = inp->buf[i];

		/* iterate through wordlist */
		for(w = dictionary; w->str != NULL; w++)
		{
			printfv(3, "comparechar(): %d: ",
					comparechar(w->str[w->index], c));
			printfv(3, "(%s){%c == %c} %d\n", w->str, w->str[w->index], c,
					w->index);
			if(comparechar(w->str[w->index], c))
			{
				w->index++;
				assert(w->index <= w->len);

				if(w->index == w->len)
				{
					match_cx++;
					if(mcb)
						mcb(inp, inp->buf + i - w->len + 1, w->len);
					w->index = 0;
				}
			}
			else
				w->index = 0;
		}
	}

	if(scb)
		scb(inp);

	return 0;
}
