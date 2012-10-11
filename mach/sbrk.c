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
 *	File:	sbrk.c
 *
 *	Unix compatibility for sbrk system call.
 *
 * HISTORY
 * 09-Mar-90  Gregg Kellogg (gk) at NeXT.
 *	include <kern/mach_interface.h> instead of <kern/mach.h>
 *
 * 14-Feb-89  Avadis Tevanian (avie) at NeXT.
 *	Total rewrite using a fixed area of VM from break region.
 */

#include <mach/mach.h>		/* for vm_allocate, vm_offset_t */
#include <mach/vm_statistics.h>
#include <sys/types.h>		/* for caddr_t */

static int sbrk_needs_init = TRUE;
static vm_size_t sbrk_region_size = 4*1024*1024; /* Well, what should it be? */
static vm_address_t sbrk_curbrk;

caddr_t sbrk(size)
	int	size;
{
	kern_return_t	ret;

	if (sbrk_needs_init) {
		sbrk_needs_init = FALSE;
		/*
		 *	Allocate a big region to simulate break region.
		 */
		ret =  vm_allocate(mach_task_self(), &sbrk_curbrk, sbrk_region_size,
				  VM_MAKE_TAG(VM_MEMORY_SBRK)|TRUE);
		if (ret != KERN_SUCCESS)
			return((caddr_t)-1);
	}
	
	if (size <= 0)
		return((caddr_t)sbrk_curbrk);
	else if (size > sbrk_region_size)
		return((caddr_t)-1);
	sbrk_curbrk += size;
	sbrk_region_size -= size;
	return((caddr_t)(sbrk_curbrk - size));
}

caddr_t brk(x)
	caddr_t x;
{
	return((caddr_t)-1);
}

