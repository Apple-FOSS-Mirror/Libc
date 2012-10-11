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
#include <sys/unistd.h>

#define	 STDIN_FILENO	0	/* standard input file descriptor */
#define	STDOUT_FILENO	1	/* standard output file descriptor */
#define	STDERR_FILENO	2	/* standard error file descriptor */

#ifndef NULL
#define	NULL		0	/* null pointer constant */
#endif

#define _POSIX_THREADS		/* We support pthreads */

#ifndef _POSIX_SOURCE
#define F_ULOCK         0      /* unlock locked section */
#define F_LOCK          1      /* lock a section for exclusive use */
#define F_TLOCK         2      /* test and lock a section for exclusive use */
#define F_TEST          3      /* test a section for locks by other procs */
#endif

/* configurable system variables */
#define	_SC_ARG_MAX		 1
#define	_SC_CHILD_MAX		 2
#define	_SC_CLK_TCK		 3
#define	_SC_NGROUPS_MAX		 4
#define	_SC_OPEN_MAX		 5
#define	_SC_JOB_CONTROL		 6
#define	_SC_SAVED_IDS		 7
#define	_SC_VERSION		 8
#define	_SC_BC_BASE_MAX		 9
#define	_SC_BC_DIM_MAX		10
#define	_SC_BC_SCALE_MAX	11
#define	_SC_BC_STRING_MAX	12
#define	_SC_COLL_WEIGHTS_MAX	13
#define	_SC_EXPR_NEST_MAX	14
#define	_SC_LINE_MAX		15
#define	_SC_RE_DUP_MAX		16
#define	_SC_2_VERSION		17
#define	_SC_2_C_BIND		18
#define	_SC_2_C_DEV		19
#define	_SC_2_CHAR_TERM		20
#define	_SC_2_FORT_DEV		21
#define	_SC_2_FORT_RUN		22
#define	_SC_2_LOCALEDEF		23
#define	_SC_2_SW_DEV		24
#define	_SC_2_UPE		25
#define	_SC_STREAM_MAX		26
#define	_SC_TZNAME_MAX		27
/* POSIX.1B sysconf options for async IO*/
#define _SC_ASYNCHRONOUS_IO	28
#define _SC_PAGESIZE		29
#define _SC_AIO_LISTIO_MAX	42
#define _SC_AIO_MAX		43
#define _SC_AIO_PRIO_DELTA_MAX	44

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
int	 des_cipher(const char *, char *, long, int);
int	 des_setkey(const char *key);
int	 encrypt(char *, int);
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
int	 setkey(const char *);
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
int	getattrlist(const char*,void*,void*,size_t,unsigned long);
int	setattrlist(const char*,void*,void*,size_t,unsigned long);
int exchangedata(const char*,const char*,unsigned long);
int	checkuseraccess(const char*,uid_t,gid_t*,int,int,unsigned long);
int	getdirentriesattr(int,void*,void*,size_t,unsigned long*,unsigned long*,unsigned long*,unsigned long);
int	searchfs(const char*,void*,void*,unsigned long,unsigned long,void*);

int fsctl(const char *,unsigned long,void*,unsigned long);		


#endif /* !_POSIX_SOURCE */
__END_DECLS

#endif /* !_UNISTD_H_ */
