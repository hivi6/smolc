/**
 * definition of function related to lexical scanning
 */

/**
 * arguments:
 *		char *s		string used to find the character c
 *		char c		character that is being find the in string s
 *
 * returns:
 *		int			returns the position of character c in s
 *					returns -1 if character c not found in s
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

static int chrpos(char *s, int c)
{
	char *p;
	p = strchr(s, c);
	return (p ? p - s : -1);
}

/**
 * returns:
 *		int			The next character in the file Infile
 *
 * side-effects:
 *		Infile		The FILE in data.h is read by one character
 *		Putback		The int in data.sh is set to 0 if Putback is non-zero
 *					and this value is returned
 *		Line		The int in data.sh is increased by 1, if a newline
 *					character is reached
 */
static int next()
{
	int c;
	
	// Check if Putback exists
	if (Putback)
	{
		c = Putback;
		Putback = 0;
		return c;
	}

	// Read the input file
	c = fgetc(Infile);
	if (c == '\n')
		Line++;
	return c;
}

/**
 * arguments:
 *		char c		This character is used to store in Putback variable
 *
 * side-effects:
 *		Putback		The int value in data.h is set to the character c
 */
static void putback(int c)
{
	Putback = c;
}

/**
 * returns:
 *		int		Returns the first non-whitespace character in FILE InFile
 */
static int skip()
{
	int c;
	c = next();
	// Skip all non-whitespace characters
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f')
	{
		c = next();
	}
	return c;
}

/**
 * arguments:
 *		int c		This is the first character that came into the scanner
 *					based on which it made the decision to call scanint
 *
 * returns:
 *		int			Return the final int literal
 */
static int scanint(int c)
{
	int k, val = 0;

	// Convert each character to an int value
	while ((k = chrpos("0123456789", c)) >= 0)
	{
		val = val * 10 + k;
		c = next();
	}
	
	// We hit a non-int character, so put it back
	putback(c);
	return val;
}

/**
 * arguments:
 *		struct token *t		Stores the token information in the t variable
 *
 * returns:
 *		int					Returns 0 if no new token is found
 *							Returns 1 if token is found
 */
int scan(struct token *t)
{
	int c;
	
	// Skip any whitespaces
	c = skip();

	// Make a decision on what token it is based on the input
	// character
	switch (c)
	{
	case EOF:
		return 0;
	case '+':
		t->token = T_PLUS;
		break;
	case '-':
		t->token = T_MINUS;
		break;
	case '*':
		t->token = T_STAR;
		break;
	case '/':
		t->token = T_SLASH;
		break;
	default:
		// If it is a digit, scan the whole int literal
		if (isdigit(c))
		{
			t->intvalue = scanint(c);
			t->token = T_INTLIT;
			break;
		}

		printf("Unrecognized character %c on line %d\n", c, Line);
		exit(1);
	}

	// We got a token
	return 1;
}
