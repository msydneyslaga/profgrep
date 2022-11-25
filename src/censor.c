#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <tbs/types.h>

#include <profgrep/buffer.h>
#include <profgrep/censor.h>

void censor_stars(pg_buf *line, char *where, uint len)
{
	memset(where, '*', len);
	write(STDOUT_FILENO, line->buf, line->cx);
}

void grawlix_seed(pg_buf *b)
{
	uint seed = 0x2fab8d97;
	for(u8 i = 0; i < 5 && i < b->cx; i++)
	{
		seed ^= b->buf[i];
		seed *= b->buf[i];
	}

	srand(seed);
}

/* assumes rand() is seeded before being called */
void censor_grawlix(pg_buf *line, char *where, uint len)
{
	assert(line != NULL);

	const char grawlix[] = "*@#$%!&";
	printf("{'%.*s', %d}", len, where, len);

	for(uint b = 0; b < len; b += sizeof(grawlix) - 1)
	{
		char set[len];
		memset(set, 0, len);

		for(u8 i = 0; i <= len; i++)
		{
			/* create a grawlix string with no duplicate characters
			 * (unless len > sizeof(grawlix))*/
			char r;
			do
				r = grawlix[rand() % (sizeof(grawlix) - 1)];
			while(memchr(set, r, i) && i < sizeof(grawlix) - 1);
			set[i] = r;
		}
		printf("[%.*s]", len, set);
	}
}
