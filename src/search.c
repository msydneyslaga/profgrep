#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tbs/types.h>

#include <profgrep/profgrep.h>
#include <profgrep/search.h>
#include <profgrep/buffer.h>
#include <profgrep/dictionary.h>


/*
 * https://web.stanford.edu/class/archive/cs/cs166/cs166.1166/lectures/02/Small02.pdf
 */
u32 pg_search(pg_buf *inp, pg_search_callback scb, pg_match_callback mcb)
{
	bool matched = false;
	u32 match_cx = 0;
	init_dictionary();

	u64 i;
	ahocora_pair *w;
	for(i = 0; i < inp->cx; i++)
	{
		/* TOCON: have c be a pointer? */
		char c = inp->buf[i];

		/* iterate through wordlist */
		for(w = wordlist; w->str != NULL; w++)
		{
			if(w->str[w->index] == c)
			{
				w->index++;
				assert(w->index <= w->len);

				if(w->index == w->len)
				{
					match_cx++;
					if(mcb)
						mcb(inp, inp->buf + i - w->len + 1, w->len);
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
