#include <stdio.h>
#include <profgrep/readln.h>

char *readline(pg_buf *inp, FILE *fp)
{
	while(!feof(fp))
	{
		utf8o c = fgetc(fp);

		pgbuf_resize(inp);
		inp->buf[inp->cx++] = c;

		if(c == '\n')
			break;
	}

	return inp->buf;
}

