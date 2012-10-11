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
 *	File:	slot_name.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	Convert machine slot values to human readable strings.
 *
 * HISTORY
 * 26-Jan-88  Mary Thompson (mrt) at Carnegie Mellon
 *	added case for CUP_SUBTYPE_RT_APC
 *
 * 28-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 *
 */

#include <mach/mach.h>
#include <mach-o/arch.h>
#include <stddef.h>

/*
 *	Convert the specified cpu_type/cpu_subtype pair to their
 *	human readable form.
 */
void slot_name(cpu_type, cpu_subtype, cpu_name, cpu_subname)
        cpu_type_t	cpu_type;
        cpu_subtype_t	cpu_subtype;
        char		**cpu_name, **cpu_subname;
{
        register char	*name = "Unknown CPU";
        register char	*subname = "";
        const NXArchInfo *ai = NXGetArchInfoFromCpuType(cpu_type, cpu_subtype);
        if (ai != NULL) {
            name = ai->name;
            subname = ai->description;
        }
        *cpu_name = name;
        *cpu_subname = subname;
}

kern_return_t msg_rpc(void) {
	return KERN_FAILURE;
}

kern_return_t msg_send(void) {
	return KERN_FAILURE;
}

kern_return_t msg_receive(void) {
	return KERN_FAILURE;
}

mach_port_t task_self_(void) {
	return mach_task_self();
}

mach_port_t host_self(void) {
	return mach_host_self();
}
 
