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
 * Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved
 *
 * 	File:	libc/sys/gettimeofday.c
 */

#include <time.h>
#include <tzfile.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>

int gettimeofday (struct timeval *tp, struct timezone *tzp)
{
        static int validtz = 0;
        static struct timezone cached_tz = {0};
        struct timeval localtv;
#ifdef __ppc__
	extern __ppc_gettimeofday(struct timeval *, struct timezone *);
#endif
  
        if (tzp && (tp == NULL) && (validtz == 0)) {
                tp = &localtv;
        }

#ifdef __ppc__
	if(__ppc_gettimeofday(tp, tzp))
		return(-1);
#else
        if (syscall (SYS_gettimeofday, tp, tzp) < 0) {
                return (-1);
        }
#endif
        if (tzp) {
		if (validtz == 0)  {
			struct tm *localtm = localtime ((time_t *)&tp->tv_sec);
			cached_tz.tz_dsttime = localtm->tm_isdst;
			cached_tz.tz_minuteswest =
				(-localtm->tm_gmtoff / SECSPERMIN) +
				(localtm->tm_isdst * MINSPERHOUR);
			validtz = 1;
		}
		tzp->tz_dsttime = cached_tz.tz_dsttime;
		tzp->tz_minuteswest = cached_tz.tz_minuteswest;
        }
        return (0);
}
