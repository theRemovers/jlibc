include ../Makefile.config

SRCC=strchr.c strrchr.c memchr.c memcmp.c 
SRCC+=strlen.c strcpy.c strncpy.c strcmp.c strncmp.c strcoll.c
SRCC+=strcat.c strncat.c strxfrm.c
SRCS=bzero.s bcopy.s
SRCH=string.h
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)

DISTFILES=Makefile $(SRCC) $(SRCS) $(SRCH)
INSTALLH=string.h
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

