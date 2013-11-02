include ../Makefile.config

INCL=-I../include

SRCC=strchr.c strrchr.c memchr.c memcmp.c 
SRCC+=strlen.c strcpy.c strncpy.c strcmp.c strncmp.c strcoll.c
SRCC+=strcat.c strncat.c strxfrm.c
SRCS=bzero.s bcopy.s
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)

DISTFILES=Makefile $(SRCC) $(SRCS)
INSTALLLIB=

include ../Makefile.template

