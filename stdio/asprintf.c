/*	$OpenBSD: asprintf.c,v 1.4 1998/06/21 22:13:46 millert Exp $	*/

/*
 * Copyright (c) 1997 Todd C. Miller <Todd.Miller@courtesan.com>
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
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if defined(LIBC_RCS) && !defined(lint)
static char rcsid[] = "$FreeBSD: src/lib/libc/stdio/asprintf.c,v 1.6 1999/08/28 00:00:55 peter Exp $";
#endif /* LIBC_RCS and not lint */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

int
#if __STDC__
asprintf(char **str, char const *fmt, ...)
#else
asprintf(str, fmt, va_alist)
	char **str;
	const char *fmt;
	va_dcl
#endif
{
	int ret;
	va_list ap;
	FILE f;

#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	f._file = -1;
	f._flags = __SWR | __SSTR | __SALC;
	f._bf._base = f._p = (unsigned char *)malloc(128);
	if (f._bf._base == NULL) {
		*str = NULL;
		errno = ENOMEM;
		return (-1);
	}
	f._bf._size = f._w = 127;		/* Leave room for the NULL */
	ret = vfprintf(&f, fmt, ap);
	*f._p = '\0';
	va_end(ap);
	f._bf._base = reallocf(f._bf._base, f._bf._size + 1);
	if (f._bf._base == NULL) {
		errno = ENOMEM;
		ret = -1;
	}
	*str = (char *)f._bf._base;
	return (ret);
}
