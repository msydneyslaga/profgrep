#include <stdio.h>
#include <stdlib.h>

#include <tbs/types.h>

#include <profgrep/profgrep.h>
#include <profgrep/search.h>
#include <profgrep/buffer.h>
#include <profgrep/dictionary.h>


/*
 * https://www.tutorialspoint.com/Aho-Corasick-Algorithm
 * https://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/02/Small02.pdf
 */
u32 pg_search(pg_buf *inp, pg_search_callback callback)
{
	/* temp */
	static int lineno = 0;
	lineno++;

	u32 match_cx = 0;
	init_dictionary();
	dbgprintf("line %d: '%.*s'\n", lineno, (int)inp->cx, inp->buf);

	for(u64 i = 0; i < inp->cx; i++)
	{
		char c = inp->buf[i];
		dbgprintf("\tcharacter '%c' at %lu:\n", c, i);

		/* iterate through wordlist */
		for(ahocora_pair *w = wordlist; w->str != NULL; w++)
		{
			if(w->str[w->index] == c)
			{
				w->index++;
				dbgprintf("\t\tindexed '%c' of '%s' at pos %lu\n",
						c,
						w->str,
						i + 1);

				assert(w->index <= w->len);

				if(w->index == w->len)
				{
					match_cx++;
					dbgprintf("\t\tmatch! '%s' found at pos %lu\n",
							w->str,
							i + 1 - w->len);
				}
			}
			else
				w->index = 0;
		}
	}

	return 0;
}
