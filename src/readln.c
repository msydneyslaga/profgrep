#include <stdio.h>
#include <unistd.h>
#include <profgrep/readln.h>

char *readln(pg_buf *inp, FILE *fp)
{
	while(!feof(fp))
	{
		utf8o c = fgetc(fp);
		if(c == EOF)
			break;

		inp->buf[inp->cx++] = c;

		pgbuf_resize(inp);
		bytesRead++;

		if(c == '\n')
			break;
	}

	return inp->buf;
}

