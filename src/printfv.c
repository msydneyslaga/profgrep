#include <profgrep/profgrep.h>
#include <profgrep/printfv.h>

int printfv(u8 verbosity, const char *f, ...)
{
	if(opt.verbosity < verbosity)
		return 0;


	va_list args;
	va_start(args, f);

	int r = vfprintf(stderr, f, args);

	va_end(args);

	return r;
}

