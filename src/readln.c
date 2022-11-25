#include <stdio.h>
#include <profgrep/readln.h>

char *readline(pg_buf *inp, FILE *fp)
{
	while(!feof(fp))
	{
		utf8o c = fgetc(fp);
		if(c == EOF)
			break;

		inp->buf[inp->cx++] = c;

		pgbuf_resize(inp);

		if(c == '\n')
			break;
	}

	return inp->buf;
}

