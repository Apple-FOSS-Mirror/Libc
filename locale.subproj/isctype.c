/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
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


#define _ANSI_LIBRARY
#include <ctype.h>

#undef isalnum
int
isalnum(c)
	int c;
{
	return(__istype((c), (_A|_D)));
}

#undef isalpha
int
isalpha(c)
	int c;
{
	return (__istype((c), _A));
}

#undef isascii
int
isascii(c)
	int c;
{
	return((c & ~0x7F) == 0);
}

#undef isblank
int
isblank(c)
	int c;
{
	return (__istype((c), _B));
}

#undef iscntrl
int
iscntrl(c)
	int c;
{
	return (__istype((c), _C));
}

#undef isdigit
int
isdigit(c)
	int c;
{
	return (__isctype((c), _D));
}

#undef isgraph
int
isgraph(c)
	int c;
{
	return (__istype((c), _G));
}

#undef islower
int
islower(c)
	int c;
{
	return (__istype((c), _L));
}

#undef isprint
int
isprint(c)
	int c;
{
	return (__istype((c), _R));
}

#undef ispunct
int
ispunct(c)
	int c;
{
	return (__istype((c), _P));
}

#undef isspace
int
isspace(c)
	int c;
{
	return (__istype((c), _S));
}

#undef isupper
int
isupper(c)
	int c;
{
	return (__istype((c), _U));
}

#undef isxdigit
int
isxdigit(c)
	int c;
{
	return (__isctype((c), _X));
}

#undef toascii
int
toascii(c)
	int c;
{
	return (c & 0177);
}

#undef tolower
int
tolower(c)
	int c;
{
        return((c & _CRMASK) ? ___tolower(c) : _CurrentRuneLocale->maplower[c]);
}

#undef toupper
int
toupper(c)
	int c;
{
        return((c & _CRMASK) ? ___toupper(c) : _CurrentRuneLocale->mapupper[c]);
}
