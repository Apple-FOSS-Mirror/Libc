/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#include <sys/param.h>
#include <sys/sysctl.h>

#include <errno.h>
#include <paths.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t
confstr(name, buf, len)
	int name;
	char *buf;
	size_t len;
{
	size_t tlen;
	int mib[2], sverrno;
	char *p;

	switch (name) {
	case _CS_PATH:
		mib[0] = CTL_USER;
		mib[1] = USER_CS_PATH;
		if (sysctl(mib, 2, NULL, &tlen, NULL, 0) == -1)
			return (-1);
		if (len != 0 && buf != NULL) {
			if ((p = malloc(tlen)) == NULL)
				return (-1);
			if (sysctl(mib, 2, p, &tlen, NULL, 0) == -1) {
				sverrno = errno;
				free(p);
				errno = sverrno;
				return (-1);
			}
			/*
			 * POSIX 1003.2 requires partial return of
			 * the string -- that should be *real* useful.
			 */
			(void)strncpy(buf, p, len - 1);
			buf[len - 1] = '\0';
			free(p);
		}
		return (tlen + 1);

	case _CS_POSIX_V6_ILP32_OFF32_CFLAGS:
	case _CS_XBS5_ILP32_OFF32_CFLAGS:		/* legacy */

	case _CS_POSIX_V6_ILP32_OFF32_LDFLAGS:
	case _CS_XBS5_ILP32_OFF32_LDFLAGS:		/* legacy */

	case _CS_POSIX_V6_ILP32_OFF32_LIBS:
	case _CS_XBS5_ILP32_OFF32_LIBS:			/* legacy */

	case _CS_XBS5_ILP32_OFF32_LINTFLAGS:		/* legacy */

	case _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_CFLAGS:		/* legacy */

	case _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS:
	case _CS_XBS5_ILP32_OFFBIG_LDFLAGS:		/* legacy */

	case _CS_POSIX_V6_ILP32_OFFBIG_LIBS:
	case _CS_XBS5_ILP32_OFFBIG_LIBS:		/* legacy */

	case _CS_XBS5_ILP32_OFFBIG_LINTFLAGS:		/* legacy */

	case _CS_POSIX_V6_LP64_OFF64_CFLAGS:
	case _CS_XBS5_LP64_OFF64_CFLAGS:		/* legacy */

	case _CS_POSIX_V6_LP64_OFF64_LDFLAGS:
	case _CS_XBS5_LP64_OFF64_LDFLAGS:		/* legacy */

	case _CS_POSIX_V6_LP64_OFF64_LIBS:
	case _CS_XBS5_LP64_OFF64_LIBS:			/* legacy */

	case _CS_XBS5_LP64_OFF64_LINTFLAGS:		/* legacy */

	case _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_CFLAGS:		/* legacy */

	case _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS:
	case _CS_XBS5_LPBIG_OFFBIG_LDFLAGS:		/* legacy */

	case _CS_POSIX_V6_LPBIG_OFFBIG_LIBS:
	case _CS_XBS5_LPBIG_OFFBIG_LIBS:		/* legacy */

	case _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS:		/* legacy */
		/* No special flags... yet */
		p = "";
		goto docopy;

	case _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS:
		if (sizeof(long) >= 8)
			p = "_POSIX_V6_LP64_OFF64";
		else
			p = "_POSIX_V6_ILP32_OFFBIG";

docopy:
		if (len != 0 && buf != NULL)
			strlcpy(buf, p, len);
		return (strlen(p) + 1);

	default:
		errno = EINVAL;
		return (0);
	}
	/* NOTREACHED */
}
