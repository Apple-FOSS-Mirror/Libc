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

#define	__APPLE_API_PRIVATE
#include <machine/cpu_capabilities.h>
#undef	__APPLE_API_PRIVATE

#include <architecture/ppc/mode_independent_asm.h>


/* These are the functions in <libkern/OSAtomic.h>.
 * The actual primitives are implemented on the commpage.
 */
 

/* int32_t	OSAtomicAdd32( int32_t theAmount, int32_t *theValue ); */

MI_ENTRY_POINT(_OSAtomicAdd32)
    ba      _COMM_PAGE_ATOMIC_ADD32


/* int32_t	OSAtomicOr32( int32_t theMask, int32_t *theValue ); */

MI_ENTRY_POINT(_OSAtomicOr32)
    mflr    r12                 // save return address
    mr      r5,r4               // move ptr to where compare-and-swap wants it
    mr      r11,r3              // copy mask
1:
    lwz     r3,0(r5)            // get old value
    or      r4,r3,r11           // make new value
    bla     _COMM_PAGE_COMPARE_AND_SWAP32   // preserves r4,r5,r9-r12
    cmpwi   r3,0                // did swap occur?
    beq--   1b                  // compare-and-swap failed, try again
    mtlr    r12                 // restore return adddress
    mr      r3,r4               // return new value
    blr


/* int32_t	OSAtomicAnd32( int32_t theMask, int32_t *theValue ); */

MI_ENTRY_POINT(_OSAtomicAnd32)
    mflr    r12                 // save return address
    mr      r5,r4               // move ptr to where compare-and-swap wants it
    mr      r11,r3              // copy mask
1:
    lwz     r3,0(r5)            // get old value
    and     r4,r3,r11           // make new value
    bla     _COMM_PAGE_COMPARE_AND_SWAP32   // preserves r4,r5,r9-r12
    cmpwi   r3,0                // did swap occur?
    beq--   1b                  // compare-and-swap failed, try again
    mtlr    r12                 // restore return adddress
    mr      r3,r4               // return new value
    blr


/* int32_t	OSAtomicXor32( int32_t theMask, int32_t *theValue ); */

MI_ENTRY_POINT(_OSAtomicXor32)
    mflr    r12                 // save return address
    mr      r5,r4               // move ptr to where compare-and-swap wants it
    mr      r11,r3              // copy mask
1:
    lwz     r3,0(r5)            // get old value
    xor     r4,r3,r11           // make new value
    bla     _COMM_PAGE_COMPARE_AND_SWAP32   // preserves r4,r5,r9-r12
    cmpwi   r3,0                // did swap occur?
    beq--   1b                  // compare-and-swap failed, try again
    mtlr    r12                 // restore return adddress
    mr      r3,r4               // return new value
    blr


/* int64_t	OSAtomicAdd64( int64_t theAmount, int64_t *theValue ); */

#if defined(__ppc64__)
MI_ENTRY_POINT(_OSAtomicAdd64)
    ba      _COMM_PAGE_ATOMIC_ADD64
#endif  /* defined(__ppc64__) */


/* bool OSAtomicCompareAndSwap32( int32_t oldValue, int32_t newValue, int32_t *theValue ); */

MI_ENTRY_POINT(_OSAtomicCompareAndSwap32)
    ba      _COMM_PAGE_COMPARE_AND_SWAP32
    

/* bool OSAtomicCompareAndSwap64( int364_t oldValue, int64_t newValue, int64_t *theValue ); */

#if defined(__ppc64__)
MI_ENTRY_POINT(_OSAtomicCompareAndSwap64)
    ba      _COMM_PAGE_COMPARE_AND_SWAP64
#endif  /* defined(__ppc64__) */


/* bool OSAtomicTestAndSet( uint32_t n, void *theAddress ); */

MI_ENTRY_POINT(_OSAtomicTestAndSet)
    mflr    r12                 // save return
    srwi    r5,r3,3             // get byte offset of n
    rlwinm  r6,r3,0,0x7         // get bit position within byte
    add     r4,r4,r5            // r4 points to byte containing the bit
    lis     r10,0x8000          // light bit 0
    rlwimi  r6,r4,3,0x18        // r6 is bit position within word
    clrrgi  r5,r4,2             // point to word containing the bit
    srw     r10,r10,r6          // get mask for bit
    addi    r9,r6,1             // save bit position + 1
1:
    lwz     r3,0(r5)            // get old word
    rlwnm   r11,r3,r9,0x1       // right justify old value of bit
    or      r4,r3,r10           // set it in new word
    bla     _COMM_PAGE_COMPARE_AND_SWAP32   // preserves r4,r5,r9-r12
    cmpwi   r3,0                // did swap occur?
    beq--   1b                  // compare-and-swap failed, try again
    mtlr    r12                 // restore return adddress
    mr      r3,r11              // return original value of bit
    blr


/* bool OSAtomicTestAndClear( uint32_t n, void *theAddress ); */

MI_ENTRY_POINT(_OSAtomicTestAndClear)
    mflr    r12                 // save return
    srwi    r5,r3,3             // get byte offset of n
    rlwinm  r6,r3,0,0x7         // get bit position within byte
    add     r4,r4,r5            // r4 points to byte containing the bit
    lis     r10,0x8000          // light bit 0
    rlwimi  r6,r4,3,0x18        // r6 is bit position within word
    clrrgi  r5,r4,2             // point to word containing the bit
    srw     r10,r10,r6          // get mask for bit
    addi    r9,r6,1             // save bit position + 1
1:
    lwz     r3,0(r5)            // get old word
    rlwnm   r11,r3,r9,0x1       // right justify old value of bit
    andc    r4,r3,r10           // clear it in new word
    bla     _COMM_PAGE_COMPARE_AND_SWAP32   // preserves r4,r5,r9-r12
    cmpwi   r3,0                // did swap occur?
    beq--   1b                  // compare-and-swap failed, try again
    mtlr    r12                 // restore return adddress
    mr      r3,r11              // return original value of bit
    blr
    

/* void *	OSAtomicDequeue( void ** inList, size_t inOffset); */

MI_ENTRY_POINT(_OSAtomicDequeue)
    ba      _COMM_PAGE_DEQUEUE
    

/* void OSAtomicEnqueue( void ** inList, void * inNewLink, size_t inOffset); */

MI_ENTRY_POINT(_OSAtomicEnqueue)
    ba      _COMM_PAGE_ENQUEUE
    

/* bool    OSSpinLockTry( OSSpinLock *lock ); */

MI_ENTRY_POINT(_OSSpinLockTry)
    ba      _COMM_PAGE_SPINLOCK_TRY
    

/* void    OSSpinLockLock( OSSpinLock *lock ); */

MI_ENTRY_POINT(_OSSpinLockLock)
    ba      _COMM_PAGE_SPINLOCK_LOCK
    

/* void    OSSpinLockUnlock( OSSpinLock *lock ); */

MI_ENTRY_POINT(_OSSpinLockUnlock)
    ba      _COMM_PAGE_SPINLOCK_UNLOCK
    

/* void    OSMemoryBarrier( void ); */

MI_ENTRY_POINT(_OSMemoryBarrier)
    ba     _COMM_PAGE_MEMORY_BARRIER

