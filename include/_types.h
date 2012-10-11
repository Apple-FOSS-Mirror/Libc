/*
 * Copyright (c) 1999-2000 Apple Computer, Inc. All rights reserved.
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

#ifndef __TYPES_H_
#define __TYPES_H_

#include <sys/_types.h>
#include <machine/ansi.h>

/*
 * XXX - This block will eventually be relocated into sys/_types.h (or
 * into a header it calls.  It is here temporarily to work can proceed
 * on the Libc part
 */
#ifndef __OSX_NULL
#ifdef __GNUG__
#define __OSX_NULL __null
#else /* ! __GNUG__ */
#ifndef __cplusplus
#define __OSX_NULL ((void *)0)
#else /* __cplusplus */
#define __OSX_NULL 0
#endif /* ! __cplusplus */
#endif /* __GNUG__ */

// XXX - renaming from sys/_types.h
typedef	__mode_t	__osx_mode_t;
typedef	__off_t		__osx_off_t;
typedef	__size_t	__osx_size_t;
typedef	__pid_t		__osx_pid_t;
typedef	__gid_t		__osx_gid_t;
#endif /* XXX - ! __OSX_NULL */

typedef	_BSD_CT_RUNE_T_	__osx_ct_rune_t;
typedef	_BSD_MBSTATE_T_	__osx_mbstate_t;
typedef	int		__osx_nl_item;
#ifdef _BSD_PTRDIFF_T_
typedef	_BSD_PTRDIFF_T_	__osx_ptrdiff_t;
#endif /* _BSD_PTRDIFF_T_ */
typedef	_BSD_RUNE_T_	__osx_rune_t;
#ifdef	__WCHAR_TYPE__
typedef	__WCHAR_TYPE__	__osx_wchar_t;
#else	/* ! __WCHAR_TYPE__ */
typedef	_BSD_WCHAR_T_	__osx_wchar_t;
#endif	/* __WCHAR_TYPE__ */
typedef	int		__osx_wctrans_t;
typedef	unsigned long	__osx_wctype_t;
typedef	_BSD_WINT_T_	__osx_wint_t;

#ifdef __WCHAR_MAX__
#define __OSX_WCHAR_MAX	__WCHAR_MAX__
#else /* ! __WCHAR_MAX__ */
#define __OSX_WCHAR_MAX	(sizeof(__osx_wchar_t) == 2 ? 0xffff : 0x7fffffff)
#endif /* __WCHAR_MAX__ */

#define __OSX_WCHAR_MIN	(sizeof(__osx_wchar_t) == 2 ? 0 : 0x80000000)
#define	__OSX_WEOF 	((__osx_wint_t)-1)

#endif /* __TYPES_H_ */
