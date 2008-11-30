include ../Makefile.config

SRCC=fclose.c feof.c fflush.c fseek.c ftell.c
SRCC+=fputc.c fputs.c fgetc.c fgets.c 
SRCC+=fread.c fwrite.c
SRCC+=fprintf.c
SRCC+=vfprintf.c sprintf.c vsprintf.c
SRCS=
SRCH=stdio.h
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)

DISTFILES=Makefile $(SRCC) $(SRCS) $(SRCH)
INSTALLH=stdio.h
INSTALLLIB=

all: .depend $(OBJS)

%.o: %.s
	$(MADMAC) $(MACFLAGS) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ $(OBJS) .depend

.depend: $(SRCC)
	$(CC) -MM $(SRCC) > .depend

dist-files:
	@echo $(DISTFILES)

install-h:
	@echo $(INSTALLH)

install-lib:
	@echo $(INSTALLLIB)

-include .depend


