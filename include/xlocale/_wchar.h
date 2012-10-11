/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
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

#ifndef _XLOCALE__WCHAR_H_
#define _XLOCALE__WCHAR_H_

__BEGIN_DECLS
wint_t	btowc_l(int, locale_t);
wint_t	fgetwc_l(FILE *, locale_t);
wchar_t	*fgetws_l(wchar_t * __restrict, int, FILE * __restrict, locale_t);
wint_t	fputwc_l(wchar_t, FILE *, locale_t);
int	fputws_l(const wchar_t * __restrict, FILE * __restrict, locale_t);
int	fwprintf_l(FILE * __restrict, locale_t, const wchar_t * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(fwprintf_l);
int	fwscanf_l(FILE * __restrict, locale_t, const wchar_t * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(fwscanf_l);
wint_t	getwc_l(FILE *, locale_t);
wint_t	getwchar_l(locale_t);
size_t	mbrlen_l(const char * __restrict, size_t, mbstate_t * __restrict,
	    locale_t);
size_t	mbrtowc_l(wchar_t * __restrict, const char * __restrict, size_t,
	    mbstate_t * __restrict, locale_t);
int	mbsinit_l(const mbstate_t *, locale_t);
size_t	mbsnrtowcs_l(wchar_t * __restrict, const char ** __restrict, size_t,
	    size_t, mbstate_t * __restrict, locale_t);
size_t	mbsrtowcs_l(wchar_t * __restrict, const char ** __restrict, size_t,
	    mbstate_t * __restrict, locale_t);
wint_t	putwc_l(wchar_t, FILE *, locale_t);
wint_t	putwchar_l(wchar_t, locale_t);
int	swprintf_l(wchar_t * __restrict, size_t n, locale_t,
		const wchar_t * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(swprintf_l);
int	swscanf_l(const wchar_t * __restrict, locale_t,
		const wchar_t * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(swscanf_l);
wint_t	ungetwc_l(wint_t, FILE *, locale_t);
int	vfwprintf_l(FILE * __restrict, locale_t, const wchar_t * __restrict,
		__darwin_va_list) __DARWIN_LDBL_COMPAT2(vfwprintf_l);
int	vfwscanf_l(FILE * __restrict, locale_t, const wchar_t * __restrict,
		__darwin_va_list) __DARWIN_LDBL_COMPAT2(vfwscanf_l);
int	vswprintf_l(wchar_t * __restrict, size_t n, locale_t,
		const wchar_t * __restrict, __darwin_va_list)
		__DARWIN_LDBL_COMPAT2(vswprintf_l);
int	vswscanf_l(const wchar_t * __restrict, locale_t,
		const wchar_t * __restrict, __darwin_va_list)
		__DARWIN_LDBL_COMPAT2(vswscanf_l);
int	vwprintf_l(locale_t, const wchar_t * __restrict, __darwin_va_list)
		__DARWIN_LDBL_COMPAT2(vwprintf_l);
int	vwscanf_l(locale_t, const wchar_t * __restrict, __darwin_va_list)
		__DARWIN_LDBL_COMPAT2(vwscanf_l);
size_t	wcrtomb_l(char * __restrict, wchar_t, mbstate_t * __restrict,
	    locale_t);
int	wcscoll_l(const wchar_t *, const wchar_t *, locale_t);
//Begin-Libc
#ifndef LIBC_ALIAS_WCSFTIME_L
//End-Libc
size_t	wcsftime_l(wchar_t * __restrict, size_t, const wchar_t * __restrict,
		const struct tm * __restrict, locale_t)
		__DARWIN_ALIAS(wcsftime_l);
//Begin-Libc
#else /* LIBC_ALIAS_WCSFTIME_L */
size_t	wcsftime_l(wchar_t * __restrict, size_t, const wchar_t * __restrict,
		const struct tm * __restrict, locale_t)
		LIBC_ALIAS(wcsftime_l);
#endif /* !LIBC_ALIAS_WCSFTIME_L */
//End-Libc
size_t	wcsnrtombs_l(char * __restrict, const wchar_t ** __restrict, size_t,
	    size_t, mbstate_t * __restrict, locale_t);
size_t	wcsrtombs_l(char * __restrict, const wchar_t ** __restrict, size_t,
	    mbstate_t * __restrict, locale_t);
double	wcstod_l(const wchar_t * __restrict, wchar_t ** __restrict, locale_t);
float	wcstof_l(const wchar_t * __restrict, wchar_t ** __restrict, locale_t);
long	wcstol_l(const wchar_t * __restrict, wchar_t ** __restrict, int,
	    locale_t);
long double
	wcstold_l(const wchar_t * __restrict, wchar_t ** __restrict, locale_t)
	    __DARWIN_LDBL_COMPAT2(wcstold_l);
long long
	wcstoll_l(const wchar_t * __restrict, wchar_t ** __restrict, int,
	    locale_t);
unsigned long
	wcstoul_l(const wchar_t * __restrict, wchar_t ** __restrict, int,
	    locale_t);
unsigned long long
	wcstoull_l(const wchar_t * __restrict, wchar_t ** __restrict, int,
	    locale_t);
int	wcswidth_l(const wchar_t *, size_t, locale_t);
size_t	wcsxfrm_l(wchar_t * __restrict, const wchar_t * __restrict, size_t,
	    locale_t);
int	wctob_l(wint_t, locale_t);
int	wcwidth_l(wchar_t, locale_t);
int	wprintf_l(locale_t, const wchar_t * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(wprintf_l);
int	wscanf_l(locale_t, const wchar_t * __restrict, ...)
		__DARWIN_LDBL_COMPAT2(wscanf_l);

/* Poison the following routines if -fshort-wchar is set */
#if !defined(__cplusplus) && defined(__WCHAR_MAX__) && __WCHAR_MAX__ <= 0xffffU
#pragma GCC poison fgetws_l fputwc_l fputws_l fwprintf_l fwscanf_l mbrtowc_l mbsnrtowcs_l mbsrtowcs_l putwc_l putwchar_l swprintf_l swscanf_l vfwprintf_l vfwscanf_l vswprintf_l vswscanf_l vwprintf_l vwscanf_l wcrtomb_l wcscoll_l wcsftime_l wcsftime_l wcsnrtombs_l wcsrtombs_l wcstod_l wcstof_l wcstol_l wcstold_l wcstoll_l wcstoul_l wcstoull_l wcswidth_l wcsxfrm_l wcwidth_l wprintf_l wscanf_l
#endif
__END_DECLS

#endif /* _XLOCALE__WCHAR_H_ */
