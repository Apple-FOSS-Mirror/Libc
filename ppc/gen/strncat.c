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
/* Copyright (c) 1991, 1997 NeXT Software, Inc.  All rights reserved.
 * 
 *	File:	libc/gen/ppc/strncat.c
 *	Author: Mike DeMoney, NeXT Software, Inc.
 *
 *	This file contains machine dependent code for string copy
 *
 * HISTORY
 *  24-Jan-1997 Umesh Vaishampayan (umeshv@NeXT.com)
 *	Ported to PPC.
 * 23-Nov-92  Derek B Clegg (dclegg@next.com)
 *	Ported to m98k.
 *  4-Jun-91  Mike DeMoney (mike@next.com)
 *	Created.
 */
#import	<string.h>

char *
strncat(char *s1, const char *s2, size_t n)
{
    unsigned len1 = strlen(s1);
    unsigned len2 = strlen(s2);
    
    if (len2 < n) {
	strcpy(&s1[len1], s2);
    } else {
	strncpy(&s1[len1], s2, n);
	s1[len1 + n] = '\0';
    }
    return s1;
}
