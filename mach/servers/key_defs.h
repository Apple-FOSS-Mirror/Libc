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
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 * Definitions of encryption keys etc..
 */

/*
 * HISTORY:
 *  5-Jun-87  Robert Sansom (rds) at Carnegie Mellon University
 *	Added macros to convert keys between network and host order.
 *
 * 12-Apr-87  Robert Sansom (rds) at Carnegie Mellon University
 *	Added KEY_IS_NULL.
 *
 *  2-Feb-87  Robert Sansom (rds) at Carnegie Mellon University
 *	Added KEY_EQUAL.
 *
 *  5-Nov-86  Robert Sansom (rds) at Carnegie-Mellon University
 *	Started.
 *
 */

#ifndef	_KEY_DEFS_
#define	_KEY_DEFS_

/*
 * An encrytion key.
 */
typedef union {
    unsigned char	key_bytes[16];
    unsigned long	key_longs[4];
} key_t, *key_ptr_t;

#define KEY_EQUAL(key1, key2) 					\
    ((key1.key_longs[0] == key2.key_longs[0])			\
	&& (key1.key_longs[1] == key2.key_longs[1])		\
	&& (key1.key_longs[2] == key2.key_longs[2])		\
	&& (key1.key_longs[3] == key2.key_longs[3]))

#define KEY_IS_NULL(key)					\
    (((key).key_longs[0] == 0) && ((key).key_longs[1] == 0)	\
	&& ((key).key_longs[2] == 0) && ((key).key_longs[3] == 0))


/*
 * Macros to convert keys between network and host byte order.
 */
#define NTOH_KEY(key) {							\
    (key).key_longs[0] = ntohl((key).key_longs[0]);			\
    (key).key_longs[1] = ntohl((key).key_longs[1]);			\
    (key).key_longs[2] = ntohl((key).key_longs[2]);			\
    (key).key_longs[3] = ntohl((key).key_longs[3]);			\
}

#define HTON_KEY(key) {							\
    (key).key_longs[0] = htonl((key).key_longs[0]);			\
    (key).key_longs[1] = htonl((key).key_longs[1]);			\
    (key).key_longs[2] = htonl((key).key_longs[2]);			\
    (key).key_longs[3] = htonl((key).key_longs[3]);			\
}

/*
 * Structure used to transmit or store a token or a key.
 */
typedef union {
    key_t	si_key;
    key_t	si_token;
} secure_info_t, *secure_info_ptr_t;

/*
 * Security Level of ports and messages.
 */
#define PORT_NOT_SECURE		0
#define MESSAGE_NOT_SECURE	0

#endif	/* _KEY_DEFS_ */
