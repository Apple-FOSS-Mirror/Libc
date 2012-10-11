/*
 * Copyright (c) 2011 Apple Inc. All rights reserved.
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

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

/* This extended version of mkpath_np is provided to help NSFileManager
 * maintain  binary compatibility.  If firstdir is not NULL, *firstdir will be
 * set to the path of the first created directory, and it is the caller's
 * responsibility to free the returned string.  This SPI is subject to removal
 * once NSFileManager no longer has a need for it, and use in new code is
 * highly discouraged.
 *
 * See: <rdar://problem/9888987>
 */

int
_mkpath_np(const char *path, mode_t omode, const char ** firstdir)
{
	char *apath = NULL;
	unsigned int depth = 0;
	mode_t chmod_mode = 0;
	int retval = 0;
	int old_errno = errno;
	struct stat sbuf;

	/* Try the trivial case first. */
	if (0 == mkdir(path, omode)) {
		if (firstdir) {
			*firstdir = strdup(path);
		}
		goto mkpath_exit;
	}

	/* Anything other than an ENOENT, EEXIST, or EISDIR indicates an
	 * error that we need to send back to the caller.  ENOENT indicates
	 * that we need to try a lower level.
	 */
	switch (errno) {
		case ENOENT:
			break;
		case EEXIST:
			if (stat(path, &sbuf) == 0) {
			    if (S_ISDIR(sbuf.st_mode)) {
					retval = EEXIST;
				} else {
					retval = ENOTDIR;
				}
			} else {
				retval = EIO;
			}
			goto mkpath_exit;
		case EISDIR: /* <rdar://problem/10288022> */
			retval = EEXIST;
			goto mkpath_exit;
		default:
			retval = errno;
			goto mkpath_exit;
	}

	apath = strdup(path);
	if (apath == NULL) {
		retval = ENOMEM;
		goto mkpath_exit;
	}

	while (1) {
		/* Increase our depth and try making that directory */
		char *s = strrchr(apath, '/');
		if (!s) {
			/* We should never hit this under normal circumstances,
			 * but it can occur due to really unfortunate timing
			 */
			retval = ENOENT;
			goto mkpath_exit;
		}
		*s = '\0';
		depth++;

		if (0 == mkdir(apath, S_IRWXU | S_IRWXG | S_IRWXO)) {
			/* Found our starting point */

			/* POSIX 1003.2:
			 * For each dir operand that does not name an existing
			 * directory, effects equivalent to those cased by the
			 * following command shall occcur:
			 *
			 * mkdir -p -m $(umask -S),u+wx $(dirname dir) &&
			 *    mkdir [-m mode] dir
			 */

			struct stat dirstat;
			if (-1 == stat(apath, &dirstat)) {
				/* Really unfortunate timing ... */
				retval = ENOENT;
				goto mkpath_exit;
			}

			if ((dirstat.st_mode & (S_IWUSR | S_IXUSR)) != (S_IWUSR | S_IXUSR)) {
			        chmod_mode = dirstat.st_mode | S_IWUSR | S_IXUSR;
				if (-1 == chmod(apath, chmod_mode)) {
					/* Really unfortunate timing ... */
					retval = ENOENT;
					goto mkpath_exit;
				}
			}

			if (firstdir) {
				*firstdir = strdup(apath);
			}
			break;
		} else if (errno == EEXIST) {
			/* Some other process won the race in creating this directory
			 * before we did.  We will use this as our starting point.
			 * See: <rdar://problem/10279893>
			 */
			if (stat(apath, &sbuf) == 0 &&
			    S_ISDIR(sbuf.st_mode)) {

				if (firstdir) {
					*firstdir = strdup(apath);
				}
				break;
			}

			retval = ENOTDIR;
			goto mkpath_exit;
		} else if (errno != ENOENT) {
			retval = errno;
			goto mkpath_exit;
		}
	}

	while (depth > 1) {
		/* Decrease our depth and make that directory */
		char *s = strrchr(apath, '\0');
		*s = '/';
		depth--;

		if (-1 == mkdir(apath, S_IRWXU | S_IRWXG | S_IRWXO)) {
			/* This handles "." and ".." added to the new section of path */
			if (errno == EEXIST)
				continue;
			retval = errno;
			goto mkpath_exit;
		}

		if (chmod_mode) {
			if (-1 == chmod(apath, chmod_mode)) {
				/* Really unfortunate timing ... */
				retval = ENOENT;
				goto mkpath_exit;
			}
		}
	}

	if (-1 == mkdir(path, omode)) {
		retval = errno;
		if (errno == EEXIST &&
		    stat(path, &sbuf) == 0 &&
		    !S_ISDIR(sbuf.st_mode)) {
			retval = ENOTDIR;
		}
	}

mkpath_exit:
	free(apath);

	errno = old_errno;
	return retval;
}

int mkpath_np(const char *path, mode_t omode) {
	return _mkpath_np(path, omode, NULL);
}
