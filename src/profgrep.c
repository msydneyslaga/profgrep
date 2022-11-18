#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <wchar.h>

#include <tbs/types.h>

#include <profgrep/profgrep.h>
#include <profgrep/search.h>
#include <profgrep/buffer.h>

#define isPrintable(c) \
	(c >= 33 && c <= 126)

char *readline(pg_buf *inp)
{
	utf8c c;
	while((c = fgetc(stdin)) != '\n' && !feof(stdin))
	{
		pgbuf_resize(inp);

		inp->buf[inp->cx++] = c;

		dbgprintf("[%c]\t(%3u)\n",
				isPrintable(c) ? c : 0,
				c);
	}

	return inp->buf;

	fprintf(stderr, "input buffer: %lu/%lu bytes\n", inp->cx, inp->alloc);
}

int main(int argc, char **argv)
{
	while(!feof(stdin))
	{
		pg_buf inp = pgbuf_init();

		readline(&inp);

		if(pg_search(&inp, NULL) > 0)

		pgbuf_destroy(&inp);
	}
}

