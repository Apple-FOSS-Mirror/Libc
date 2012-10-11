/*	$OpenBSD: ecvt.c,v 1.3 2003/06/17 21:56:24 millert Exp $	*/

/*
 * Copyright (c) 2002 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Sponsored in part by the Defense Advanced Research Projects
 * Agency (DARPA) and Air Force Research Laboratory, Air Force
 * Materiel Command, USAF, under agreement number F39502-99-1-0512.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char rcsid[] = "$OpenBSD: ecvt.c,v 1.3 2003/06/17 21:56:24 millert Exp $";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *__dtoa(double, int, int, int *, int *, char **);
static char *__cvt(double, int, int *, int *, int, int);

static char *
__cvt(double value, int ndigit, int *decpt, int *sign, int fmode, int pad)
{
	static char *s;
	char *p, *rve;
	size_t siz;

	if (ndigit == 0) {
		*sign = value < 0.0;
		*decpt = 0;
		return ("");
	}

	if (s) {
		free(s);
		s = NULL;
	}

	if (ndigit < 0)
		siz = -ndigit + 1;
	else
		siz = ndigit + 1;


	/* __dtoa() doesn't allocate space for 0 so we do it by hand */
	if (value == 0.0) {
		*decpt = 1 - fmode;	/* 1 for 'e', 0 for 'f' */
		*sign = 0;
		if ((rve = s = (char *)malloc(siz)) == NULL)
			return(NULL);
		*rve++ = '0';
		*rve = '\0';
	} else {
		p = __dtoa(value, fmode + 2, ndigit, decpt, sign, &rve);
		if (*decpt == 9999) {
			/* Nan or Infinity */
			*decpt = 0;
			return(p);
		}
		/* make a local copy and adjust rve to be in terms of s */
		if (pad && fmode)
			siz += *decpt;
		if ((s = (char *)malloc(siz)) == NULL)
			return(NULL);
		(void) strlcpy(s, p, siz);
		rve = s + (rve - p);
	}

	/* Add trailing zeros (unless we got NaN or Inf) */
	if (pad && *decpt != 9999) {
		siz -= rve - s;
		while (--siz)
			*rve++ = '0';
		*rve = '\0';
	}

	return(s);
}

char *
ecvt(double value, int ndigit, int *decpt, int *sign)
{
	return(__cvt(value, ndigit, decpt, sign, 0, 1));
}

char *
fcvt(double value, int ndigit, int *decpt, int *sign)
{
	return(__cvt(value, ndigit, decpt, sign, 1, 1));
}
