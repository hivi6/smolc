#include <stdio.h>

#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"

/**
 * side-effects:
 *		Line		Sets the value of the int as 1
 *		Putback		Sets the value of Putback as newline character
 */
static void init()
{
	Line = 1;
	Putback = '\n';
}

/**
 * arguments:
 *		char *prog  This is the program name
 *
 * side-effects:
 *					Prints how to use the program
 */
static void usage(char *prog)
{
	fprintf(stderr, "Usage: %s infile\n", prog);
	exit(1);
}

// List of printable tokens
char *tokstr[] = { "+", "-", "*", "/", "intlit" };

/**
 * side-effects:
 *					Reads the tokens in the file and prints that
 */
static void scanfile()
{
	struct token t;

	while (scan(&t))
	{
		printf("Token %s", tokstr[t.token]);
		if (t.token == T_INTLIT)
			printf(", value %d", t.intvalue);
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		usage(argv[0]);

	init();

	if ((Infile = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	scanfile();
	return 0;
}
