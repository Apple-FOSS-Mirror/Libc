/*
 * Copyright (c) 1999-2005 Apple Computer, Inc. All rights reserved.
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
/* Copyright 1998 Apple Computer, Inc. */

#include <SYS.h>

#define	__APPLE_API_PRIVATE
#include <machine/cpu_capabilities.h>
#undef	__APPLE_API_PRIVATE

LABEL(___commpage_gettimeofday)
	movq	$(_COMM_PAGE_GETTIMEOFDAY),%rax
	jmp		*%rax

/*
 *	This syscall is special cased: the timeval is returned in rax:rdx.
 */
LABEL(___gettimeofday)
    UNIX_SYSCALL_NONAME(gettimeofday,0)
    movq	%rax, (%rdi)
    movl	%edx, 8(%rdi)
    xorl	%eax, %eax
	ret
