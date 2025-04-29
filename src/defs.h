/**
 * defs.h
 *
 * Store struct and enum definitions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// ========================================
// token
// ========================================

enum {
	T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

struct token {
	int token;
	int intvalue;
};

