/* $FreeBSD: src/include/nl_types.h,v 1.7 1999/08/27 23:44:51 peter Exp $ */

/***********************************************************
Copyright 1990, by Alfalfa Software Incorporated, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that Alfalfa's name not be used in
advertising or publicity pertaining to distribution of the software
without specific, written prior permission.

ALPHALPHA DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
ALPHALPHA BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

If you make any modifications, bugfixes or other changes to this software
we'd appreciate it if you could send a copy to us so we can keep things
up-to-date.  Many thanks.
				Kee Hinckley
				Alfalfa Software, Inc.
				267 Allston St., #3
				Cambridge, MA 02139  USA
				nazgul@alfalfa.com

******************************************************************/

#ifndef _NL_TYPES_H_
#define _NL_TYPES_H_
#include <sys/cdefs.h>
#include <_types.h>

#define	NL_SETD		0
#define	NL_CAT_LOCALE	1

#ifndef _NL_ITEM_DECLARED
typedef	__osx_nl_item	nl_item;
#define _NL_ITEM_DECLARED
#endif

typedef	void	*nl_catd;

__BEGIN_DECLS
extern nl_catd 	catopen(const char *, int);
extern char    *catgets(nl_catd, int, int, const char *);
extern int	catclose(nl_catd);
__END_DECLS

#endif	/* _NL_TYPES_H_ */
