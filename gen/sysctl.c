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
#include <limits.h>
#include <paths.h>
#include <stdio.h>
#include <unistd.h>

int
sysctl(name, namelen, oldp, oldlenp, newp, newlen)
	int *name;
	u_int namelen;
	void *oldp, *newp;
	size_t *oldlenp, newlen;
{
	if (name[0] != CTL_USER)
		return (__sysctl(name, namelen, oldp, oldlenp, newp, newlen));

	if (newp != NULL) {
		errno = EPERM;
		return (-1);
	}
	if (namelen != 2) {
		errno = EINVAL;
		return (-1);
	}

	switch (name[1]) {
	case USER_CS_PATH:
		if (oldp && *oldlenp < sizeof(_PATH_STDPATH))
			return (ENOMEM);
		*oldlenp = sizeof(_PATH_STDPATH);
		if (oldp != NULL)
			memmove(oldp, _PATH_STDPATH, sizeof(_PATH_STDPATH));
		return (0);
	}

	if (oldp && *oldlenp < sizeof(int))
		return (ENOMEM);
	*oldlenp = sizeof(int);
	if (oldp == NULL)
		return (0);

	switch (name[1]) {
	case USER_BC_BASE_MAX:
		*(int *)oldp = BC_BASE_MAX;
		return (0);
	case USER_BC_DIM_MAX:
		*(int *)oldp = BC_DIM_MAX;
		return (0);
	case USER_BC_SCALE_MAX:
		*(int *)oldp = BC_SCALE_MAX;
		return (0);
	case USER_BC_STRING_MAX:
		*(int *)oldp = BC_STRING_MAX;
		return (0);
	case USER_COLL_WEIGHTS_MAX:
		*(int *)oldp = COLL_WEIGHTS_MAX;
		return (0);
	case USER_EXPR_NEST_MAX:
		*(int *)oldp = EXPR_NEST_MAX;
		return (0);
	case USER_LINE_MAX:
		*(int *)oldp = LINE_MAX;
		return (0);
	case USER_RE_DUP_MAX:
		*(int *)oldp = RE_DUP_MAX;
		return (0);
	case USER_POSIX2_VERSION:
		*(int *)oldp = _POSIX2_VERSION;
		return (0);
	case USER_POSIX2_C_BIND:
#ifdef POSIX2_C_BIND
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_C_DEV:
#ifdef	POSIX2_C_DEV
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_CHAR_TERM:
#ifdef	POSIX2_CHAR_TERM
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_FORT_DEV:
#ifdef	POSIX2_FORT_DEV
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_FORT_RUN:
#ifdef	POSIX2_FORT_RUN
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_LOCALEDEF:
#ifdef	POSIX2_LOCALEDEF
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_SW_DEV:
#ifdef	POSIX2_SW_DEV
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_POSIX2_UPE:
#ifdef	POSIX2_UPE
		*(int *)oldp = 1;
#else
		*(int *)oldp = 0;
#endif
		return (0);
	case USER_STREAM_MAX:
		*(int *)oldp = FOPEN_MAX;
		return (0);
	case USER_TZNAME_MAX:
		*(int *)oldp = NAME_MAX;
		return (0);
	default:
		errno = EINVAL;
		return (-1);
	}
	/* NOTREACHED */
}
