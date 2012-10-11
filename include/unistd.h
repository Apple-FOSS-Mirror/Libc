/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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
/*-
 * Copyright (c) 1998-1999 Apple Computer, Inc. All Rights Reserved
 * Copyright (c) 1991, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)unistd.h	8.12 (Berkeley) 4/27/95
 *
 *  Copyright (c)  1998 Apple Compter, Inc.
 *  All Rights Reserved
 */

/* History:
        7/14/99 EKN at Apple fixed getdirentriesattr from getdirentryattr
        3/26/98 CHW at Apple added real interface to searchfs call
  	3/5/98  CHW at Apple added hfs semantic system calls headers
*/

#ifndef _UNISTD_H_
#define	_UNISTD_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/unistd.h>		/* XXX needs to go away */


#define	 STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */

#ifndef NULL
#ifdef __GNUG__
#define NULL __null
#else /* ! __GNUG__ */
#ifndef __cplusplus
#define NULL ((void *)0)
#else /* __cplusplus */
#define NULL 0
#endif /* ! __cplusplus */
#endif /* __GNUG__ */
#endif /* ! NULL */

#ifdef _POSIX_VERSION		/* XXX <sys/unistd.h> */
#undef _POSIX_VERSION
#endif
#ifdef _POSIX2_VERSION		/* XXX <sys/unistd.h> */
#undef _POSIX2_VERSION
#endif
#ifdef _POSIX_CHOWN_RESTRICTED		/* XXX <sys/unistd.h> */
#undef _POSIX_CHOWN_RESTRICTED
#endif
#ifdef _POSIX_NO_TRUNC		/* XXX <sys/unistd.h> */
#undef _POSIX_NO_TRUNC
#endif

/* Version test macros */
#define	_POSIX_VERSION			200112L
#define	_POSIX2_VERSION			200112L

#define	_XOPEN_VERSION			600		/* [XSI] */
#define _XOPEN_XCU_VERSION		4		/* Older standard */


/* Please keep this list in the same order as the applicable standard */
#define	_POSIX_ADVISORY_INFO		(-1)		/* [ADV] */
#define	_POSIX_ASYNCHRONOUS_IO		200112L		/* [AIO] */
#define	_POSIX_BARRIERS			(-1)		/* [BAR] */
#define	_POSIX_CHOWN_RESTRICTED		200112L
#define	_POSIX_CLOCK_SELECTION		(-1)		/* [CS] */
#define	_POSIX_CPUTIME			(-1)		/* [CPT] */
#define	_POSIX_FSYNC			200112L		/* [FSC] */
#define	_POSIX_IPV6			200112L
#define	_POSIX_JOB_CONTROL		200112L
#define	_POSIX_MAPPED_FILES		200112L		/* [MF] */
#define	_POSIX_MEMLOCK			200112L		/* [ML] */
#define	_POSIX_MEMLOCK_RANGE		200112L		/* [MR] */
#define	_POSIX_MEMORY_PROTECTION	200112L		/* [MPR] */
#define	_POSIX_MESSAGE_PASSING		(-1)		/* [MSG] */
#define	_POSIX_MONOTONIC_CLOCK		(-1)		/* [MON] */
#define	_POSIX_NO_TRUNC			200112L
#define	_POSIX_PRIORITIZED_IO		(-1)		/* [PIO] */
#define	_POSIX_PRIORITY_SCHEDULING	(-1)		/* [PS] */
#define	_POSIX_RAW_SOCKETS		200112L		/* [RS] */
#define	_POSIX_READER_WRITER_LOCKS	200112L		/* [THR] */
#define	_POSIX_REALTIME_SIGNALS		(-1)		/* [RTS] */
#define	_POSIX_REGEXP			200112L
#define	_POSIX_SAVED_IDS		(-1)		/* XXX required */
#define	_POSIX_SEMAPHORES		200112L		/* [SEM] */
#define	_POSIX_SHARED_MEMORY_OBJECTS	200112L		/* [SHM] */
#define	_POSIX_SHELL			200112L
#define	_POSIX_SPAWN			(-1)		/* [SPN] */
#define	_POSIX_SPIN_LOCKS		(-1)		/* [SPI] */
#define	_POSIX_SPORADIC_SERVER		(-1)		/* [SS] */
#define	_POSIX_SYNCHRONIZED_IO		200112L		/* [SIO] */
#define	_POSIX_THREAD_ATTR_STACKADDR	200112L		/* [TSA] */
#define	_POSIX_THREAD_ATTR_STACKSIZE	200112L		/* [TSS] */
#define	_POSIX_THREAD_CPUTIME		(-1)		/* [TCT] */
#define	_POSIX_THREAD_PRIO_INHERIT	(-1)		/* [TPI] */
#define	_POSIX_THREAD_PRIO_PROTECT	(-1)		/* [TPP] */
#define	_POSIX_THREAD_PRIORITY_SCHEDULING	(-1)	/* [TPS] */
#define	_POSIX_THREAD_PROCESS_SHARED	200112L		/* [TSH] */
#define	_POSIX_THREAD_SAFE_FUNCTIONS	200112L		/* [TSF] */
#define	_POSIX_THREAD_SPORADIC_SERVER	(-1)		/* [TSP] */
#define _POSIX_THREADS			200112L		/* [THR] */
#define	_POSIX_TIMEOUTS			(-1)		/* [TMO] */
#define	_POSIX_TIMERS			(-1)		/* [TMR] */
#define	_POSIX_TRACE			(-1)		/* [TRC] */
#define	_POSIX_TRACE_EVENT_FILTER	(-1)		/* [TEF] */
#define	_POSIX_TRACE_INHERIT		(-1)		/* [TRI] */
#define	_POSIX_TRACE_LOG		(-1)		/* [TRL] */
#define	_POSIX_TYPED_MEMORY_OBJECTS	(-1)		/* [TYM] */
#ifndef _POSIX_VDISABLE
#define	_POSIX_VDISABLE			0xff		/* same as sys/termios.h */
#endif /* _POSIX_VDISABLE */

#define	_POSIX2_C_BIND			200112L
#define	_POSIX2_C_DEV			(-1)		/* c99 command */
#define	_POSIX2_CHAR_TERM		200112L
#define	_POSIX2_FORT_DEV		(-1)		/* fort77 command */
#define	_POSIX2_FORT_RUN		200112L
#define	_POSIX2_LOCALEDEF		(-1)		/* localedef command */
#define	_POSIX2_PBS			(-1)
#define	_POSIX2_PBS_ACCOUNTING		(-1)
#define	_POSIX2_PBS_CHECKPOINT		(-1)
#define	_POSIX2_PBS_LOCATE		(-1)
#define	_POSIX2_PBS_MESSAGE		(-1)
#define	_POSIX2_PBS_TRACK		(-1)
#define	_POSIX2_SW_DEV			200112L
#define	_POSIX2_UPE			200112L	/* XXXX no fc, newgrp, tabs */

#define	_V6_ILP32_OFF32			(-1)
#define	_V6_ILP32_OFFBIG		0
#define	_V6_LP64_OFF64			0
#define	_V6_LPBIG_OFFBIG		(-1)

#define	_XBS5_ILP32_OFF32		_V6_ILP32_OFF32		/* legacy */
#define	_XBS5_ILP32_OFFBIG		_V6_ILP32_OFFBIG	/* legacy */
#define	_XBS5_LP64_OFF64		_V6_LP64_OFF64		/* legacy */
#define	_XBS5_LPBIG_OFFBIG		_V6_LPBIG_OFFBIG	/* legacy */

#define	_XOPEN_CRYPT			(1)
#define	_XOPEN_ENH_I18N			(1)		/* XXX required */
#define	_XOPEN_LEGACY			(-1)	/* no ftime gcvt, wcswcs */
#define	_XOPEN_REALTIME			(-1)	/* no q'ed signals, mq_* */
#define	_XOPEN_REALTIME_THREADS		(-1)	/* no posix_spawn, et. al. */
#define	_XOPEN_SHM			(1)
#define	_XOPEN_STREAMS			(-1)
#define	_XOPEN_UNIX			(1)


#ifndef _POSIX_SOURCE
#define F_ULOCK         0      /* unlock locked section */
#define F_LOCK          1      /* lock a section for exclusive use */
#define F_TLOCK         2      /* test and lock a section for exclusive use */
#define F_TEST          3      /* test a section for locks by other procs */
#endif

/* configurable system variables */
#define	_SC_ARG_MAX			 1
#define	_SC_CHILD_MAX			 2
#define	_SC_CLK_TCK			 3
#define	_SC_NGROUPS_MAX			 4
#define	_SC_OPEN_MAX			 5
#define	_SC_JOB_CONTROL			 6
#define	_SC_SAVED_IDS			 7
#define	_SC_VERSION			 8
#define	_SC_BC_BASE_MAX			 9
#define	_SC_BC_DIM_MAX			10
#define	_SC_BC_SCALE_MAX		11
#define	_SC_BC_STRING_MAX		12
#define	_SC_COLL_WEIGHTS_MAX		13
#define	_SC_EXPR_NEST_MAX		14
#define	_SC_LINE_MAX			15
#define	_SC_RE_DUP_MAX			16
#define	_SC_2_VERSION			17
#define	_SC_2_C_BIND			18
#define	_SC_2_C_DEV			19
#define	_SC_2_CHAR_TERM			20
#define	_SC_2_FORT_DEV			21
#define	_SC_2_FORT_RUN			22
#define	_SC_2_LOCALEDEF			23
#define	_SC_2_SW_DEV			24
#define	_SC_2_UPE			25
#define	_SC_STREAM_MAX			26
#define	_SC_TZNAME_MAX			27
#define _SC_ASYNCHRONOUS_IO		28
#define	_SC_PAGESIZE			29
#define	_SC_MEMLOCK			30
#define	_SC_MEMLOCK_RANGE		31
#define	_SC_MEMORY_PROTECTION		32
#define	_SC_MESSAGE_PASSING		33
#define	_SC_PRIORITIZED_IO		34
#define	_SC_PRIORITY_SCHEDULING		35
#define	_SC_REALTIME_SIGNALS		36
#define	_SC_SEMAPHORES			37
#define	_SC_FSYNC			38
#define	_SC_SHARED_MEMORY_OBJECTS 	39
#define	_SC_SYNCHRONIZED_IO		40
#define	_SC_TIMERS			41
#define	_SC_AIO_LISTIO_MAX		42
#define	_SC_AIO_MAX			43
#define	_SC_AIO_PRIO_DELTA_MAX		44
#define	_SC_DELAYTIMER_MAX		45
#define	_SC_MQ_OPEN_MAX			46
#define	_SC_MAPPED_FILES		47	/* swap _SC_PAGESIZE vs. BSD */
#define	_SC_RTSIG_MAX			48
#define	_SC_SEM_NSEMS_MAX		49
#define	_SC_SEM_VALUE_MAX		50
#define	_SC_SIGQUEUE_MAX		51
#define	_SC_TIMER_MAX			52
#define	_SC_2_PBS			59
#define	_SC_2_PBS_ACCOUNTING		60
#define	_SC_2_PBS_CHECKPOINT		61
#define	_SC_2_PBS_LOCATE		62
#define	_SC_2_PBS_MESSAGE		63
#define	_SC_2_PBS_TRACK			64
#define	_SC_ADVISORY_INFO		65
#define	_SC_BARRIERS			66
#define	_SC_CLOCK_SELECTION		67
#define	_SC_CPUTIME			68
#define	_SC_FILE_LOCKING		69
#define	_SC_GETGR_R_SIZE_MAX		70
#define	_SC_GETPW_R_SIZE_MAX		71
#define	_SC_HOST_NAME_MAX		72
#define	_SC_LOGIN_NAME_MAX		73
#define	_SC_MONOTONIC_CLOCK		74
#define	_SC_MQ_PRIO_MAX			75
#define	_SC_READER_WRITER_LOCKS		76
#define	_SC_REGEXP			77
#define	_SC_SHELL			78
#define	_SC_SPAWN			79
#define	_SC_SPIN_LOCKS			80
#define	_SC_SPORADIC_SERVER		81
#define	_SC_THREAD_ATTR_STACKADDR	82
#define	_SC_THREAD_ATTR_STACKSIZE	83
#define	_SC_THREAD_CPUTIME		84
#define	_SC_THREAD_DESTRUCTOR_ITERATIONS 85
#define	_SC_THREAD_KEYS_MAX		86
#define	_SC_THREAD_PRIO_INHERIT		87
#define	_SC_THREAD_PRIO_PROTECT		88
#define	_SC_THREAD_PRIORITY_SCHEDULING	89
#define	_SC_THREAD_PROCESS_SHARED	90
#define	_SC_THREAD_SAFE_FUNCTIONS	91
#define	_SC_THREAD_SPORADIC_SERVER	92
#define	_SC_THREAD_STACK_MIN		93
#define	_SC_THREAD_THREADS_MAX		94
#define	_SC_TIMEOUTS			95
#define	_SC_THREADS			96
#define	_SC_TRACE			97
#define	_SC_TRACE_EVENT_FILTER		98
#define	_SC_TRACE_INHERIT		99
#define	_SC_TRACE_LOG			100
#define	_SC_TTY_NAME_MAX		101
#define	_SC_TYPED_MEMORY_OBJECTS	102
#define	_SC_V6_ILP32_OFF32		103
#define	_SC_V6_ILP32_OFFBIG		104
#define	_SC_V6_LP64_OFF64		105
#define	_SC_V6_LPBIG_OFFBIG		106
#define	_SC_IPV6			118
#define	_SC_RAW_SOCKETS			119
#define	_SC_SYMLOOP_MAX			120
#define	_SC_ATEXIT_MAX			107
#define	_SC_IOV_MAX			56
#define	_SC_PAGE_SIZE			_SC_PAGESIZE
#define	_SC_XOPEN_CRYPT			108
#define	_SC_XOPEN_ENH_I18N		109
#define	_SC_XOPEN_LEGACY		110
#define	_SC_XOPEN_REALTIME		111
#define	_SC_XOPEN_REALTIME_THREADS	112
#define	_SC_XOPEN_SHM			113
#define	_SC_XOPEN_STREAMS		(-1)	/* 114 - Not supported */
#define	_SC_XOPEN_UNIX			115
#define	_SC_XOPEN_VERSION		116
#define	_SC_XOPEN_XCU_VERSION		121
#define _SC_XBS5_ILP32_OFF32		122
#define _SC_XBS5_ILP32_OFFBIG		123
#define _SC_XBS5_LP64_OFF64		124
#define _SC_XBS5_LPBIG_OFFBIG		125

#ifndef _CS_PATH	/* XXX temporary #ifdef'ed for <sys/unistd.h> */
#define	_CS_PATH				1
#endif
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS		2
#define	_CS_POSIX_V6_ILP32_OFF32_LDFLAGS	3
#define	_CS_POSIX_V6_ILP32_OFF32_LIBS		4
#define	_CS_POSIX_V6_ILP32_OFFBIG_CFLAGS	5
#define	_CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS	6
#define	_CS_POSIX_V6_ILP32_OFFBIG_LIBS		7
#define	_CS_POSIX_V6_LP64_OFF64_CFLAGS		8
#define	_CS_POSIX_V6_LP64_OFF64_LDFLAGS		9
#define	_CS_POSIX_V6_LP64_OFF64_LIBS		10
#define	_CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS	11
#define	_CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS	12
#define	_CS_POSIX_V6_LPBIG_OFFBIG_LIBS		13
#define	_CS_POSIX_V6_WIDTH_RESTRICTED_ENVS	14

/* reserved for compatibility with Issue 5 */
#define	_CS_XBS5_ILP32_OFF32_CFLAGS		20
#define	_CS_XBS5_ILP32_OFF32_LDFLAGS		21
#define	_CS_XBS5_ILP32_OFF32_LIBS		22
#define	_CS_XBS5_ILP32_OFF32_LINTFLAGS		23
#define	_CS_XBS5_ILP32_OFFBIG_CFLAGS		24
#define	_CS_XBS5_ILP32_OFFBIG_LDFLAGS		25
#define	_CS_XBS5_ILP32_OFFBIG_LIBS		26
#define	_CS_XBS5_ILP32_OFFBIG_LINTFLAGS		27
#define	_CS_XBS5_LP64_OFF64_CFLAGS		28
#define	_CS_XBS5_LP64_OFF64_LDFLAGS		29
#define	_CS_XBS5_LP64_OFF64_LIBS		30
#define	_CS_XBS5_LP64_OFF64_LINTFLAGS		31
#define	_CS_XBS5_LPBIG_OFFBIG_CFLAGS		32
#define	_CS_XBS5_LPBIG_OFFBIG_LDFLAGS		33
#define	_CS_XBS5_LPBIG_OFFBIG_LIBS		34
#define	_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS		35


__BEGIN_DECLS

void	 _Exit(int) __dead2;
void	 _exit(int) __dead2;
int	 access(const char *, int);
unsigned int alarm(unsigned int);
int	 chdir(const char *);
int	 chown(const char *, uid_t, gid_t);
int	 close(int);
size_t	 confstr(int, char *, size_t);
int	 dup(int);
int	 dup2(int, int);
int	 execl(const char *, const char *, ...);
int	 execle(const char *, const char *, ...);
int	 execlp(const char *, const char *, ...);
int	 execv(const char *, char * const *);
int	 execve(const char *, char * const *, char * const *);
int	 execvp(const char *, char * const *);
pid_t	 fork(void);
long	 fpathconf(int, int);
char	*getcwd(char *, size_t);
int	 getdomainname(char *, int);
gid_t	 getegid(void);
uid_t	 geteuid(void);
gid_t	 getgid(void);
int	 getgroups(int, gid_t []);
char	*getlogin(void);
int	 getlogin_r(char *, int);
pid_t	 getpgrp(void);
pid_t	 getpid(void);
pid_t	 getppid(void);
uid_t	 getuid(void);
int	 isatty(int);
int	 lchown(const char *, uid_t, gid_t);
int	 link(const char *, const char *);
off_t	 lseek(int, off_t, int);
long	 pathconf(const char *, int);
int	 pause(void);
int	 pipe(int *);
ssize_t	 read(int, void *, size_t);
int	 rmdir(const char *);
int	 setdomainname(const char *, int);
int	 setgid(gid_t);
int	 setpgid(pid_t, pid_t);
pid_t	 setsid(void);
int	 setuid(uid_t);
unsigned int	 sleep(unsigned int);
long	 sysconf(int);
pid_t	 tcgetpgrp(int);
int	 tcsetpgrp(int, pid_t);
char	*ttyname(int);
char	*ttyname_r(int, char *, size_t);
int	 unlink(const char *);
ssize_t	 write(int, const void *, size_t);

extern char *optarg;			/* getopt(3) external variables */
extern int optind, opterr, optopt, optreset;
int	 getopt(int, char * const [], const char *);

#ifndef	_POSIX_SOURCE
#ifdef	__STDC__
struct timespec;			/* pselect(3) */
struct timeval;				/* select(2) */
#endif
int	 acct(const char *);
int	 async_daemon(void);
char	*brk(const char *);
int	 chroot(const char *);
char	*crypt(const char *, const char *);
void	 encrypt(char *, int);
void	 endusershell(void);
int	 fchdir(int);
int	 fchown(int, int, int);
char	*fflagstostr(u_long);
int	 fsync(int);
int	 ftruncate(int, off_t);
int	 getdtablesize(void);
int	 getgrouplist(const char *, int, int *, int *);
long	 gethostid(void);
int	 gethostname(char *, int);
mode_t	 getmode(const void *, mode_t);
int	 getpagesize(void) __pure2;
char	*getpass(const char *);
int	 getpeereid(int, uid_t *, gid_t *);
int	 getpgid(pid_t _pid);
int	 getsid(pid_t _pid);
char	*getusershell(void);
char	*getwd(char *);			/* obsoleted by getcwd() */
int	 lockf(int, int, off_t);
int	 initgroups(const char *, int);
int	 iruserok(unsigned long, int, const char *, const char *);
int	 issetugid(void);
char	*mkdtemp(char *);
int	 mknod(const char *, mode_t, dev_t);
int	 mkstemp(char *);
int	 mkstemps(char *, int);
char	*mktemp(char *);
int	 nfssvc(int, void *);
int	 nice(int);
ssize_t	 pread(int, void *, size_t, off_t);
#if 0
void	 psignal(unsigned int, const char *);
extern __const char *__const sys_siglist[];
#else
#include <signal.h>
#endif
int	 profil(char *, int, int, int);
#ifndef __MWERKS__
int	 pselect(int, fd_set *, fd_set *, fd_set *,
	    const struct timespec *, const sigset_t *);
#endif /* ! __MWERKS__ */
ssize_t	 pwrite(int, const void *, size_t, off_t);
int	 rcmd(char **, int, const char *, const char *, const char *, int *);
int	 readlink(const char *, char *, int);
int	 reboot(int);
int	 revoke(const char *);
int	 rresvport(int *);
int	 rresvport_af(int *, int);
int	 ruserok(const char *, int, const char *, const char *);
char	*sbrk(int);
int	 select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
int	 setegid(gid_t);
int	 seteuid(uid_t);
int	 setgroups(int, const gid_t *);
void	 sethostid(long);
int	 sethostname(const char *, int);
void	 setkey(const char *);
int	 setlogin(const char *);
void	*setmode(const char *);
int	 setpgrp(pid_t pid, pid_t pgrp);	/* obsoleted by setpgid() */
int	 setregid(gid_t, gid_t);
int	 setreuid(uid_t, uid_t);
int	 setrgid(gid_t);
int	 setruid(uid_t);
void	 setusershell(void);
int	 strtofflags(char **, u_long *, u_long *);
int	 swapon(const char *);
int	 symlink(const char *, const char *);
void	 sync(void);
int	 syscall(int, ...);
int	 truncate(const char *, off_t);
int	 ttyslot(void);
unsigned int	 ualarm(unsigned int, unsigned int);
int	 undelete(const char *);
int	 unwhiteout(const char *);
int	 usleep(unsigned int);
void	*valloc(size_t);			
pid_t	 vfork(void);

extern char *suboptarg;			/* getsubopt(3) external variable */
int	 getsubopt(char **, char * const *, char **);

/*  HFS & HFS Plus semantics system calls go here */
#ifdef __LP64__
int    getattrlist(const char*,void*,void*,size_t,unsigned int);
int    setattrlist(const char*,void*,void*,size_t,unsigned int);
int exchangedata(const char*,const char*,unsigned int);
int    checkuseraccess(const char*,uid_t,gid_t*,int,int,unsigned int);
int    getdirentriesattr(int,void*,void*,size_t,unsigned int*,unsigned int*,unsigned int*,unsigned int);
int    searchfs(const char*,void*,void*,unsigned int,unsigned int,void*);

int fsctl(const char *,unsigned int,void*,unsigned int);
#else /* __LP64__ */
int	getattrlist(const char*,void*,void*,size_t,unsigned long);
int	setattrlist(const char*,void*,void*,size_t,unsigned long);
int exchangedata(const char*,const char*,unsigned long);
int	checkuseraccess(const char*,uid_t,gid_t*,int,int,unsigned long);
int	getdirentriesattr(int,void*,void*,size_t,unsigned long*,unsigned long*,unsigned long*,unsigned long);
int	searchfs(const char*,void*,void*,unsigned long,unsigned long,void*);

int fsctl(const char *,unsigned long,void*,unsigned long);		
#endif /* __LP64__ */

#endif /* !_POSIX_SOURCE */
__END_DECLS

#endif /* !_UNISTD_H_ */
