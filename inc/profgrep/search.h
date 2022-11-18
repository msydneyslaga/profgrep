#ifndef SEARCH_H
#define SEARCH_H

#include <profgrep/profgrep.h>
#include <profgrep/buffer.h>

typedef void (*pg_search_callback)(u64, u64);

u32 pg_search(pg_buf *inp, pg_search_callback callback);

#endif
