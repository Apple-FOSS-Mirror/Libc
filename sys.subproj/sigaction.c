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
 * Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved
 *
 *	@(#)sigaction.c	1.0
 */

#include <sys/syscall.h>
#include <signal.h>
#include <sys/signal.h>
#include <errno.h>

/*
 *	Intercept the sigaction syscall and use our signal trampoline
 *	as the signal handler instead.  The code here is derived
 *	from sigvec in sys/kern_sig.c.
 */

extern void	(*sigcatch[NSIG])();
#if defined(__DYNAMIC__)
extern int __in_sigtramp;
#endif

static int
sigaction__ (sig, nsv, osv, bind)
        int sig;
	register struct sigaction *nsv, *osv;
        int bind;
{
	struct sigaction vec;
	void (*prevsig)();
	extern void _sigtramp();

	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP) {
	        errno = EINVAL;
	        return (-1);
	}
	prevsig = sigcatch[sig];
	if (nsv) {
	        sigcatch[sig] = nsv->sa_handler;
	        vec = *nsv;  nsv = &vec;
	        if (nsv->sa_handler != (void (*)())SIG_DFL && nsv->sa_handler != (void (*)())SIG_IGN) {
	                nsv->sa_handler = _sigtramp;
#ifdef __DYNAMIC__
                    if (bind && (__in_sigtramp == 0))				// XXX
                          _dyld_bind_fully_image_containing_address(sigcatch[sig]);
#endif
	        }
	}
	if (syscall (SYS_sigaction, sig, nsv, osv) < 0) {
	        sigcatch[sig] = prevsig;
	        return (-1);
	}
	if (osv && prevsig)
	        osv->sa_handler = prevsig;
	return (0);
}


int
sigaction (sig, nsv, osv)
        int sig;
	register const struct sigaction *nsv;
        register struct sigaction *osv;
{
    return sigaction__(sig, nsv, osv, 1);
}

// XXX
#ifdef __DYNAMIC__

int
_sigaction_nobind (sig, nsv, osv)
        int sig;
	register const struct sigaction *nsv;
        register struct sigaction *osv;
{
    return sigaction__(sig, nsv, osv, 0);
}
#endif

