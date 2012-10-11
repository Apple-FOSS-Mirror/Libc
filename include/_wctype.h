/*-
 * Copyright (c)1999 Citrus Project,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/*
 * Common header for wctype.h and wchar.h
 *
 * Contains everything required by wctype.h except:
 *
 *	typedef __darwin_wctrans_t wctrans_t;
 *	int iswblank(wint_t);
 *	wint_t towctrans(wint_t, wctrans_t);
 *	wctrans_t wctrans(const char *);
 */

#ifndef __WCTYPE_H_
#define __WCTYPE_H_

#include <sys/cdefs.h>
#include <_types.h>

#ifndef _WINT_T
#define _WINT_T
typedef __darwin_wint_t		wint_t;
#endif

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef __darwin_wctype_t	wctype_t;
#endif

#ifndef WEOF
#define WEOF			__DARWIN_WEOF
#endif

__BEGIN_DECLS
int	iswalnum(wint_t);
int	iswalpha(wint_t);
int	iswcntrl(wint_t);
int	iswctype(wint_t, wctype_t);
int	iswdigit(wint_t);
int	iswgraph(wint_t);
int	iswlower(wint_t);
int	iswprint(wint_t);
int	iswpunct(wint_t);
int	iswspace(wint_t);
int	iswupper(wint_t);
int	iswxdigit(wint_t);
wint_t	towlower(wint_t);
wint_t	towupper(wint_t);
wctype_t
	wctype(const char *);
__END_DECLS

#include <ctype.h>

#define	iswalnum(wc)		__istype((wc), _CTYPE_A|_CTYPE_D)
#define	iswalpha(wc)		__istype((wc), _CTYPE_A)
#define	iswcntrl(wc)		__istype((wc), _CTYPE_C)
#define	iswctype(wc, charclass)	__istype((wc), (charclass))
#define	iswdigit(wc)		__istype((wc), _CTYPE_D)
#define	iswgraph(wc)		__istype((wc), _CTYPE_G)
#define	iswlower(wc)		__istype((wc), _CTYPE_L)
#define	iswprint(wc)		__istype((wc), _CTYPE_R)
#define	iswpunct(wc)		__istype((wc), _CTYPE_P)
#define	iswspace(wc)		__istype((wc), _CTYPE_S)
#define	iswupper(wc)		__istype((wc), _CTYPE_U)
#define	iswxdigit(wc)		__istype((wc), _CTYPE_X)
#define	towlower(wc)		__tolower(wc)
#define	towupper(wc)		__toupper(wc)

#ifdef _USE_EXTENDED_LOCALES_
#include <xlocale/__wctype.h>
#endif /* _USE_EXTENDED_LOCALES_ */

#endif /* __WCTYPE_H_ */
