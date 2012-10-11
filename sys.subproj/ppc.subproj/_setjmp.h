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
 *	Copyright (c) 1998, Apple Computer Inc. All rights reserved.
 *
 *	File: _setjmp.h
 *
 *	Defines for register offsets in the save area.
 *
 */

#define JMP_r1	0x00
#define JMP_r2	0x04
#define JMP_r13	0x08
#define JMP_r14	0x0c
#define JMP_r15	0x10
#define JMP_r16	0x14
#define JMP_r17	0x18
#define JMP_r18	0x1c
#define JMP_r19	0x20
#define JMP_r20	0x24
#define JMP_r21	0x28
#define JMP_r22	0x2c
#define JMP_r23	0x30
#define JMP_r24	0x34
#define JMP_r25	0x38
#define JMP_r26	0x3c
#define JMP_r27	0x40
#define JMP_r28	0x44
#define JMP_r29	0x48
#define JMP_r30	0x4c
#define JMP_r31	0x50
#define JMP_lr  0x54
#define JMP_cr  0x58
#define JMP_ctr	0x5c
#define JMP_xer	0x60
#define JMP_sig	0x64
#define JMP_SIGFLAG 0x68
