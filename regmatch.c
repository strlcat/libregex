#include <stdio.h>
#include <stdlib.h>
#include "regex.h"

static int regmatch(const char *pattern, const char *string, char **errstr)
{
	regex_t r;
	int status;

	status = regcomp(&r, pattern, REG_EXTENDED | REG_NOSUB);
	if (status) {
		if (errstr) {
			char *es;

			es = malloc(128);
			if (!es) goto _err;
			regerror(status, &r, es, 128);
			*errstr = es;
			goto _err;
		}
		goto _err;
	}
	status = regexec(&r, string, 0, NULL, 0);
	regfree(&r);

	return status == 0 ? 1 : 0;

_err:
	regfree(&r);
	return -1;
}

int main(int argc, char **argv)
{
	int status;
	char *es;

	if (argc < 3) {
		printf("usage: regmatch \"pattern\" \"string\"\n");
		return 1;
	}
	status = regmatch(argv[1], argv[2], &es);
	if (status > 0) printf("matches\n");
	else if (!status) printf("nomatch\n");
	else {
		printf("regcomp error: %s\n", es);
		free(es);
	}
	return 0;
}
