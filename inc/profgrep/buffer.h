#ifndef BUFFER_H
#define BUFFER_H

#include <tbs/types.h>

typedef struct
{
	char *buf;
	u64 alloc;
	u64 cx;
} pg_buf;

pg_buf pgbuf_init();

void pgbuf_destroy(pg_buf *inp);

void pgbuf_resize(pg_buf *inp);

void pgbuf_clear(pg_buf *inp);

#endif
