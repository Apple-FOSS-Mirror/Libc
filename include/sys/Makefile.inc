SYS_INSTHDRS += statvfs.h

SYS_INSTHDRS := ${SYS_INSTHDRS:S/^/${.CURDIR}\/include\/sys\//}
