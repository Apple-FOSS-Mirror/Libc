/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
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

#ifndef _OSATOMIC_H_
#define _OSATOMIC_H_

#include    <stddef.h>
#include    <sys/cdefs.h>
#include    <stdint.h>
#include    <stdbool.h>

/* These are the preferred versions of the atomic and synchronization operations.
 * Their implementation is customized at boot time for the platform, including
 * late-breaking errata fixes as necessary.   They are thread safe.
 *
 * WARNING: all addresses passed to these functions must be "naturally aligned", ie
 * int32_t's must be 32-bit aligned (low 2 bits of address zero), and int64_t's
 * must be 64-bit aligned (low 3 bits of address zero.)
 */ 
__BEGIN_DECLS

/* Arithmetic functions.  They do not incorporate memory barriers and thus cannot
 * be used by themselves to synchronize shared memory.  They return the new value.
 * The "or", "and", and "xor" operations are layered on top of compare-and-swap.
 */
int32_t	OSAtomicAdd32( int32_t theAmount, int32_t *theValue );
inline static
int32_t	OSAtomicIncrement32( int32_t *theValue ) { return OSAtomicAdd32(  1, theValue); }
inline static
int32_t	OSAtomicDecrement32( int32_t *theValue ) { return OSAtomicAdd32( -1, theValue); }
int32_t	OSAtomicOr32( uint32_t theMask, uint32_t *theValue );
int32_t	OSAtomicAnd32( uint32_t theMask, uint32_t *theValue ); 
int32_t	OSAtomicXor32( uint32_t theMask, uint32_t *theValue );
#if defined(__ppc64__) || defined(__i386__)
int64_t	OSAtomicAdd64( int64_t theAmount, int64_t *theValue );
inline static
int64_t	OSAtomicIncrement64( int64_t *theValue ) { return OSAtomicAdd64(  1, theValue); }
inline static
int64_t	OSAtomicDecrement64( int64_t *theValue ) { return OSAtomicAdd64( -1, theValue); }
#endif  /* defined(__ppc64__) || defined(__i386__) */

/* Compare and swap.  They do not incorporate memory barriers and thus cannot be used
 * by themselved to synchronize shared memory.  They return true if the swap occured.
 */
bool    OSAtomicCompareAndSwap32( int32_t oldValue, int32_t newValue, int32_t *theValue );
#if defined(__ppc64__) || defined(__i386__)
bool    OSAtomicCompareAndSwap64( int64_t oldValue, int64_t newValue, int64_t *theValue );
#endif  /* defined(__ppc64__) || defined(__i386__) */

/* Test and set.  They do not incorporate memory barriers and thus cannot be used by
 * themselves to synchronize shared memory.  They return the original value of the bit.
 * They operate on bit (0x80>>(n&7)) in byte ((char*)theAddress + (n>>3)).  They are 
 * layered on top of the compare-and-swap operation.
 */
bool    OSAtomicTestAndSet( uint32_t n, void *theAddress );
bool    OSAtomicTestAndClear( uint32_t n, void *theAddress );

/* FILO queue and dequeue.  These use memory barriers as required to synchronize access to
 * the queued/dequeued structure.  The "inOffset" field is the offset within the structure
 * of the link field. "inList" is the list head; it is not a struct.  The queue is a singly
 * linked list with a zero terminator.
 */
void *	OSAtomicDequeue( void ** inList, size_t inOffset);
void    OSAtomicEnqueue( void ** inList, void * inNewLink, size_t inOffset);

/* Spinlocks.  These use memory barriers as required to synchronize access to shared
 * memory protected by the lock.  The lock operation spins, but employs various strategies
 * to back off if the lock is held, making it immune to most priority-inversion livelocks.
 * The try operation immediately returns false if the lock was held, true if it took the
 * lock.  The convention is that unlocked is zero, locked is nonzero.
 */
#define	OS_SPINLOCK_INIT    0

typedef	int32_t OSSpinLock;

bool    OSSpinLockTry( OSSpinLock *lock );
void    OSSpinLockLock( OSSpinLock *lock );
void    OSSpinLockUnlock( OSSpinLock *lock );

/* Memory barrier.  This strictly orders memory accesses in a weakly ordered model such
 * as PPC.  All loads and stores executed in sequential program order before the barrier
 * will complete with respect to the coherence mechanism, before any load or store
 * executed after the barrier.  Used with an atomic operation, the barrier can be used to
 * create custom synchronization protocols, as an alternative to the spinlock or queue/
 * dequeue operations.  Note that this barrier does not order uncached loads and stores.
 * On a uniprocessor, the barrier is typically a nop.
 */
void    OSMemoryBarrier( void );

__END_DECLS

#endif /* _OSATOMIC_H_ */
