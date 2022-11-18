#include <stdlib.h>
#include <assert.h>
#include <profgrep/buffer.h>

pg_buf pgbuf_init()
{
	pg_buf buf;
	buf.buf		= malloc(1024);
	buf.alloc	= 256;
	buf.cx		= 0;

	assert(buf.buf != NULL);

	return buf;
}

void pgbuf_resize(pg_buf *buf)
{
	if(buf->cx >= buf->alloc)
	{
		buf->alloc *= 1.5;
		buf->buf = realloc(buf->buf, buf->alloc);
	}
	assert(buf->buf != NULL);
}

void pgbuf_destroy(pg_buf *buf)
{
	assert(buf->buf != NULL);
	free(buf->buf);

	buf->buf	= NULL;
	buf->alloc	= 0;
	buf->cx		= 0;
}

uint pgbuf_available(pg_buf *buf)
{
	assert(buf->buf != NULL);

	return (buf->alloc - buf->cx);
}

