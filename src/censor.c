#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <profgrep/buffer.h>
#include <profgrep/censor.h>

void censor_stars(pg_buf *line, char *where, uint len)
{
	memset(where, '*', len);
	write(STDOUT_FILENO, line->buf, line->cx);
}

void censor_grawlix(pg_buf *line, char *where, uint len)
{

}
