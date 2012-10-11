/*
 * Copyright 1996 1995 by Open Software Foundation, Inc. 1997 1996 1995 1994 1993 1992 1991  
 *              All Rights Reserved 
 *  
 * Permission to use, copy, modify, and distribute this software and 
 * its documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation. 
 *  
 * OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE. 
 *  
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR 
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT, 
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 * 
 */
/*
 * MkLinux
 */

#if defined(__ppc__)

#import	<architecture/ppc/asm_help.h>
#import	<architecture/ppc/pseudo_inst.h>

/* void spin_lock(int *p);
 *
 * Lock the lock pointed to by `p'.  Spin (possibly forever) until
 * the lock is available.  Test and test and set logic used.
 */

.text

LEAF(__spin_lock_try)
1:
	lwarx   r5,0,r3		// Read the lock
	addi    r4,0,0x1	// Lock value
	cmpwi   r5,0x0		// Is it busy?
	bne-    2f		// Yes, return 0
	stwcx.  r4,0,r3		// Try to lock the lock
	bne-    1b		// Lost reservation, try again
        addi	r3,0,1		// Got the lock
	isync			// Sync instruction stream 
	blr			// Return 1
2:	addi	r3,0,0		// Could not get the lock
	blr			// Return 0
END(__spin_lock_try)

.globl _spin_lock
LEAF(__spin_lock)
_spin_lock:
	addi    r4,0,0x1	// Lock value
1:
	lwarx   r5,0,r3		// Read the lock
	cmpwi   r5,0x0		// Is it busy?
	bne-    1b		// Yes, spin
	stwcx.  r4,0,r3		// Try to lock the lock
	bne-    1b		// Lost reservation, try again
	isync			// Sync instruction stream 
	blr			// Got it, return
END(__spin_lock)

/* void spin_unlock(int *p);
 *
 *	Unlock the lock pointed to by p.
 */
.globl _spin_unlock
LEAF(__spin_unlock)
_spin_unlock:
	sync
	li32	r4,0
	stw	r4,0(r3)
	blr
END(__spin_unlock)

#elif defined(__i386__)

#include <architecture/i386/asm_help.h>  

/*    
 * void
 * _spin_lock(p)
 *      int *p;
 *
 * Lock the lock pointed to by p.  Spin (possibly forever) until the next
 * lock is available.
 */
        TEXT

.globl _spin_lock_try
LEAF(__spin_lock_try, 0)
_spin_lock_try:
        movl    4(%esp),%ecx
        movl    $1,%eax
        xchgl   (%ecx),%eax
        xorl    $1,%eax
END(__spin_lock_try)

.globl _spin_lock
LEAF(__spin_lock, 0)
_spin_lock:
        movl    4(%esp), %ecx
1:
        movl    (%ecx), %eax
        orl     %eax, %eax
        jnz     1b
        movl    $0xFFFFFFFF, %eax
        xchgl   %eax, (%ecx)
        orl     %eax, %eax
        jnz     1b
END(__spin_lock)


/*
 * void
 * _spin_unlock(p)
 *      int *p;
 *
 * Unlock the lock pointed to by p.
 */
.globl _spin_unlock
LEAF(__spin_unlock, 0)
_spin_unlock:
        movl    $0, %eax
        movl    4(%esp), %ecx
        xchgl   %eax, (%ecx)
END(__spin_unlock)

#else
#error spin_locks not defined for this architecture
#endif
