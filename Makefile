#	$NetBSD: Makefile,v 1.1 2015/05/13 07:07:36 pgoyette Exp $

.include "../Makefile.inc"

#S?=	/usr/src/sys
KMOD=	current_time
SRCS=	current_time.c

.include <bsd.kmodule.mk>
