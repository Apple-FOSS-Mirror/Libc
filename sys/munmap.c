/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/syscall.h>

/*
 * Stub function to account for the differences in standard compliance
 * while maintaining binary backward compatibility.
 */
int
munmap(void *addr, size_t len)
{
#if __DARWIN_UNIX03
	return syscall(SYS_munmap, addr, len);
#else	/* !__DARWIN_UNIX03 */
	int	page_mask;
	size_t	offset;
	int	rv;

	if (len == 0) {
		/*
		 * Standard compliance now requires the system to return EINVAL
		 * for munmap(addr, 0).  Return success now to maintain
		 * backwards compatibility.
		 */
		return 0;
	}
	/*
	 * Page-align "addr" since the system now requires it
	 * for standards compliance.
	 * Update "len" to reflect the adjustment and still cover the same area.
	 */
	page_mask = getpagesize() - 1;
	offset = ((uintptr_t) addr) & page_mask;
	addr = (void *) (((uintptr_t) addr) & ~page_mask);
	len += offset;
	rv = syscall(SYS_munmap, addr, len);
	return rv;
#endif	/* !__DARWIN_UNIX03 */
}
