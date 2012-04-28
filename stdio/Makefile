include ../Makefile.config

INCL=-I../include

SRCC=fclose.c feof.c fflush.c fseek.c ftell.c
SRCC+=fputc.c fputs.c fgetc.c fgets.c 
SRCC+=fread.c fwrite.c
SRCC+=fprintf.c
SRCC+=vfprintf.c sprintf.c vsprintf.c
SRCS=
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)

DISTFILES=Makefile $(SRCC) $(SRCS) $(SRCH)
INSTALLLIB=

include ../Makefile.template



