# searching ppc directory as a fallback to avoid unnecessary code duplication
.PATH: ${.CURDIR}/ppc/pthreads

MDSRCS += \
       init_cpu_capabilities.c \
       get_cpu_capabilities.s \
       pthread_set_self.s \
       pthread_self.s \
       pthread_getspecific.s
