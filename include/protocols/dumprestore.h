/*
 * Copyright (c) 2000, 2006 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)dumprestore.h	8.2 (Berkeley) 1/21/94
 */

#ifndef _DUMPRESTORE_H_
#define _DUMPRESTORE_H_

/*
 * TP_BSIZE is the size of file blocks on the dump tapes.
 * Note that TP_BSIZE must be a multiple of DEV_BSIZE.
 *
 * NTREC is the number of TP_BSIZE blocks that are written
 * in each tape record. HIGHDENSITYTREC is the number of
 * TP_BSIZE blocks that are written in each tape record on
 * 6250 BPI or higher density tapes.
 *
 * TP_NINDIR is the number of indirect pointers in a TS_INODE
 * or TS_ADDR record. Note that it must be a power of two.
 */
#define TP_BSIZE	1024
#define NTREC   	10
#define HIGHDENSITYTREC	32
#define TP_NINDIR	(TP_BSIZE/2)
#define LBLSIZE		16
#define NAMELEN		64

#define OFS_MAGIC   	(int)60011
#define NFS_MAGIC   	(int)60012
#define CHECKSUM	(int)84446

union u_spcl {
	char dummy[TP_BSIZE];
	struct	s_spcl {
#ifdef __LP64__
		int	c_type;		    /* record type (see below) */
		int	c_date;		    /* date of this dump */
		int	c_ddate;	    /* date of previous dump */
		int	c_volume;	    /* dump volume number */
#else /* !__LP64__ */
		long	c_type;		    /* record type (see below) */
		time_t	c_date;		    /* date of this dump */
		time_t	c_ddate;	    /* date of previous dump */
		long	c_volume;	    /* dump volume number */
#endif /* __LP64__ */
		daddr_t	c_tapea;	    /* logical block of this record */
		ino_t	c_inumber;	    /* number of inode */
#ifdef __LP64__
		int	c_magic;	    /* magic number (see above) */
		int	c_checksum;	    /* record checksum */
#else /* !__LP64__ */
		long	c_magic;	    /* magic number (see above) */
		long	c_checksum;	    /* record checksum */
#endif /* __LP64__ */
		struct	dinode	c_dinode;   /* ownership and mode of inode */
#ifdef __LP64__
		int	c_count;	    /* number of valid c_addr entries */
#else /* !__LP64__ */
		long	c_count;	    /* number of valid c_addr entries */
#endif /* __LP64__ */
		char	c_addr[TP_NINDIR];  /* 1 => data; 0 => hole in inode */
		char	c_label[LBLSIZE];   /* dump label */
#ifdef __LP64__
		int	c_level;	    /* level of this dump */
#else /* !__LP64__ */
		long	c_level;	    /* level of this dump */
#endif /* __LP64__ */
		char	c_filesys[NAMELEN]; /* name of dumpped file system */
		char	c_dev[NAMELEN];	    /* name of dumpped device */
		char	c_host[NAMELEN];    /* name of dumpped host */
#ifdef __LP64__
		int	c_flags;	    /* additional information */
		int	c_firstrec;	    /* first record on volume */
		int	c_spare[32];	    /* reserved for future uses */
#else /* !__LP64__ */
		long	c_flags;	    /* additional information */
		long	c_firstrec;	    /* first record on volume */
		long	c_spare[32];	    /* reserved for future uses */
#endif /* __LP64__ */
	} s_spcl;
};

/*
 * special record types
 */
#define TS_TAPE 	1	/* dump tape header */
#define TS_INODE	2	/* beginning of file record */
#define TS_ADDR 	4	/* continuation of file record */
#define TS_BITS 	3	/* map of inodes on tape */
#define TS_CLRI 	6	/* map of inodes deleted since last dump */
#define TS_END  	5	/* end of volume marker */

/*
 * flag values
 */
#define DR_NEWHEADER	0x0001	/* new format tape header */
#define DR_NEWINODEFMT	0x0002	/* new format inodes on tape */

#define	DUMPOUTFMT	"%-16s %c %s"		/* for printf */
						/* name, level, ctime(date) */
#define	DUMPINFMT	"%16s %c %[^\n]\n"	/* inverse for scanf */

#endif /* !_DUMPRESTORE_H_ */
