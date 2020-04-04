#	$NetBSD$

.include "../Makefile.inc"

#S?=	/usr/src/sys
KMOD=	current_time
SRCS=	current_time.c

.include <bsd.kmodule.mk>
