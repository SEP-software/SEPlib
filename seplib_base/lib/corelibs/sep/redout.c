/*
 *	redin() returns a 1 if the input is redirected and a 0 if it is not
 *	redout() returns a 1 if the output is redirected and a 0 if it is not.
 *
 * By redirected, it means that the standard input is coming from
 * a pipe ("|"), or from a file ("<").
 * %
 *
 * modified  1/26/83  S. Levin   rewrite
 * modified  3/2/83   S. Levin   converted to generic fileno(xxx) rather than 0,1...
 */
#include <stdio.h>
#include "sep_main_internal.h"

#if NeedFunctionPrototypes
_XFUNCPROTOBEGIN
int redout(void)
_XFUNCPROTOEND
#else
int redout()
#endif
{
	return (!isatty(fileno(stdout)));
}
