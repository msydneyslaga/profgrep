#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>

#include <profgrep/profgrep.h>
#include <profgrep/dictionary.h>
#include <profgrep/buffer.h>

typedef void (*pg_search_callback)(pg_buf *line);
typedef void (*pg_match_callback)(pg_buf *line, char *where, uint len);

u32 pg_search(pg_buf *inp, ahocora_pair *dictionary,
		pg_search_callback scb, pg_match_callback mcb);

#endif
