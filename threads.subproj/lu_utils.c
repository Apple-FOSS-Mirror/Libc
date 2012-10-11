/*
 * Port and memory management for doing lookups to the lookup server
 * Copyright (C) 1989 by NeXT, Inc.
 */
/*
 * HISTORY
 * 27-Mar-90  Gregg Kellogg (gk) at NeXT
 *	Changed to use bootstrap port instead of service port.
 *
 */
#include <stdio.h>
#include <mach/mach.h>
#include <servers/bootstrap.h>

mach_port_t _lu_port = MACH_PORT_NULL;
static name_t LOOKUP_NAME = "lookup daemon";

mach_port_t _lookupd_port(mach_port_t port) {
	if (port != MACH_PORT_NULL) {
		kern_return_t ret;
		mach_port_t bp;
		ret = task_get_bootstrap_port(mach_task_self(), &bp);
		if (ret != KERN_SUCCESS) {
			mach_error("task_get_bootstrap_port() failed", ret);
			abort();
		}
		if (bp == MACH_PORT_NULL) {
			mach_error("task_get_bootstrap_port() returned MACH_PORT_NULL!", 0);
			return MACH_PORT_NULL;
		}
		ret = bootstrap_register(bp, LOOKUP_NAME, port);
		if (ret != BOOTSTRAP_SUCCESS) {
			mach_error("bootstrap_register() failed", ret);
			abort();
		}
                return port;
	}
	return _lu_port;
}

/* called as child starts up.  mach ports aren't inherited: trash cache */
void
_lu_fork_child()
{
	mach_port_t bp;
	kern_return_t ret;
	int pid = getpid();

	_lu_port = MACH_PORT_NULL;
	if (pid > 2) {
		ret = task_get_bootstrap_port(mach_task_self(), &bp);
		if (ret != KERN_SUCCESS) {
			mach_error("task_get_bootstrap_port() failed", ret);
			abort();
		}
		if (bp == MACH_PORT_NULL) {
			fprintf(stderr, "task_get_bootstrap_port() returned MACH_PORT_NULL!\n");
			return;
		}
		ret = bootstrap_look_up(bp, LOOKUP_NAME, &_lu_port);
		if (ret != BOOTSTRAP_SUCCESS && ret != BOOTSTRAP_UNKNOWN_SERVICE) {
			mach_error("bootstrap_look_up() failed", ret);
			_lu_port = MACH_PORT_NULL;
		}
	}
}

void
_lu_setport(mach_port_t desired)
{
	if (_lu_port != MACH_PORT_NULL) {
		mach_port_deallocate(mach_task_self(), _lu_port);
	}
	_lu_port = desired;
}

static int
port_valid(mach_port_t port)
{
	mach_port_type_t ptype;
	kern_return_t ret;
	
	ret = mach_port_type(mach_task_self(), port, &ptype);
	if (ret != KERN_SUCCESS) {
		mach_error("mach_port_type() failed", ret);
		return 0;
	}
	return 1;
}

int
_lu_running(void)
{
	if (_lu_port == MACH_PORT_NULL) {
		_lu_fork_child();
	}
	if (_lu_port != MACH_PORT_NULL) {
		if (port_valid(_lu_port)) {
			return (1);
		}
		_lu_fork_child();
		if (port_valid(_lu_port)) {
			return (1);
		}
	}
	return 0;
}

