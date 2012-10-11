/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
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
/*	$OpenBSD: opendev.c,v 1.7 2002/06/09 22:18:43 fgsch Exp $	*/

/*
 * Copyright (c) 2000, Todd C. Miller.  All rights reserved.
 * Copyright (c) 1996, Jason Downs.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <paths.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

int
opendev(path, oflags, dflags, realpath)
	char *path;
	int oflags;
	int dflags;
	char **realpath;
{
	int fd;
	char *slash, *prefix;
	static char namebuf[PATH_MAX];

	/* Initial state */
	if (realpath)
		*realpath = path;
	fd = -1;
	errno = ENOENT;

	if (dflags & OPENDEV_BLCK)
		prefix = "";			/* block device */
	else
		prefix = "r";			/* character device */

	if ((slash = strchr(path, '/')))
		fd = open(path, oflags);
	else if (dflags & OPENDEV_PART) {
		if (snprintf(namebuf, sizeof(namebuf), "%s%s%s",
		    _PATH_DEV, prefix, path) < sizeof(namebuf)) {
			char *slice;
			while ((slice = strrchr(namebuf, 's')) &&
			    isdigit(*(slice-1))) *slice = '\0';
			fd = open(namebuf, oflags);
			if (realpath)
				*realpath = namebuf;
		} else
			errno = ENAMETOOLONG;
	}
	if (!slash && fd == -1 && errno == ENOENT) {
		if (snprintf(namebuf, sizeof(namebuf), "%s%s%s",
		    _PATH_DEV, prefix, path) < sizeof(namebuf)) {
			fd = open(namebuf, oflags);
			if (realpath)
				*realpath = namebuf;
		} else
			errno = ENAMETOOLONG;
	}
	return (fd);
}
