#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <sysexits.h>
#include <argp.h>

#include <tbs/types.h>

#include <profgrep/profgrep.h>
#include <profgrep/search.h>
#include <profgrep/buffer.h>
#include <profgrep/censor.h>
#include <profgrep/dictionary.h>
#include <profgrep/readln.h>

#define isPrintable(c) \
	(c >= 33 && c <= 126)

int pg_file(FILE *fp, ahocora_pair *dictionary, pg_search_callback scb,
		pg_match_callback mcb)
{
	while(!feof(fp))
	{
		pg_buf inp = pgbuf_init();

		assert(readline(&inp, fp) != NULL);

		pg_search(&inp, dictionary, scb, mcb);

		pgbuf_destroy(&inp);
	}

	return 0;
}

static int parse_opt(int key, char *arg, struct argp_state *state)
{
	struct options *opt = state->input;

	switch(key)
	{
		case 'd':
		{
			FILE *fp = fopen(arg, "r");

			if(!fp)
			{
				fprintf(stderr, "profgrep: failed to open file '%s'\n", arg);
				exit(EX_OSFILE);
			}

			opt->dictionary = parse_dictionary(fp);

			if(opt->dictionary == NULL)
			{
				fprintf(stderr,
						"profgrep: error parsing dictionary file '%s'\n",
						arg);
				exit(EX_SOFTWARE);
			}

			break;
		}
		case 'C':
		{
			if(!arg)
				opt->matchcb = censor_stars;
			else if(!strcmp(arg, "stars"))
				opt->matchcb = censor_stars;
			else if(!strcmp(arg, "grawlix"))
			{
				srand(time(NULL));
				opt->matchcb = censor_grawlix;
			}
			else
				argp_error(state, "unknown censor method");
			break;
		}
		case ARGP_KEY_ARG:
		{
			FILE *fp;
			if(arg[0] == '-' && arg[1] == 0)
				fp = stdin;
			else
			{
				fp = fopen(arg, "r");
				if(fp == NULL)
				{
					fprintf(stderr, "error opening file '%s'\n", arg);
					exit(1);
				}
			}

			opt->files[opt->_files_cx++] = fp;
			opt->files[opt->_files_cx] = NULL;

			if(opt->_files_cx >= opt->_files_alloc)
			{
				opt->_files_alloc *= 1.5;
				opt->files = realloc(opt->files, opt->_files_alloc);
			}

			break;
		}
	}

	return 0;
}

void printbuf(pg_buf *buf)
{
	write(STDOUT_FILENO, buf->buf, buf->cx);
}

int main(int argc, char **argv)
{
	struct argp_option options[] =
	{
		{ "invert-match",	'v', 0,			0,						"outputed lines are those which do not match the dictionary" },
		{ "censor",			'C', "METHOD",	OPTION_ARG_OPTIONAL,	"censor matched words"
																	"\nMETHOD may be 'stars' or 'grawlix' (default: 'stars')"},
		{ "print-all",		'p', 0,			0,						"print lines regardless of whether they matched the dictionary" },
		{ "dictionary",		'd', "FILE",	0,						"use file of newline-seperated strings as dictionary" },
		{ 0 },
	};

	struct options opt =
	{
		._files_alloc = 2,
		._files_cx = 0,
		.files = calloc(2, sizeof(FILE*)),
		.searchcb = printbuf,
	};
	opt.files[0] = stdin;
	opt.files[1] = NULL;
	opt.dictionary = default_dictionary;

	uint argcx = 1;
	struct argp argp = {options, parse_opt, "[FILE...]"};

	argp_parse(&argp, argc, argv, 0, 0, &opt);

	/* foreach file */
	for(FILE **fps = opt.files, *fp = *fps; fp != NULL; fp = *(++fps))
	{
		pg_file(fp, opt.dictionary, opt.searchcb, opt.matchcb);
		fclose(fp);
	}

	free(opt.files);
}

