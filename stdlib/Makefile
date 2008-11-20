# JAGPATH=$(HOME)/Jaguar
# CROSSPATH=/usr/local/m68k-aout/m68k-aout
MADMAC=$(JAGPATH)/bin/mac
CC=$(CROSSPATH)/bin/gcc
AR=$(CROSSPATH)/bin/ar

MACFLAGS=-fb -v
CFLAGS=-mc68000 -Wall -fomit-frame-pointer -O2 -msoft-float 

#SRCC=malloc.c calloc.c free.c 
SRCC=malloc.c atoi.c
#SRCC+=abort.c
SRCS=rand.s
SRCH=stdlib.h malloc.h
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)

DISTFILES=Makefile $(SRCC) $(SRCS) $(SRCH)
INSTALLH=stdlib.h 
INSTALLLIB=

all: .depend $(OBJS)

%.o: %.s
	$(MADMAC) $(MACFLAGS) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ $(OBJS)

.depend: $(SRCC)
	$(CC) -MM $(SRCC) > .depend

dist-files:
	@echo $(DISTFILES)

install-h:
	@echo $(INSTALLH)

install-lib:
	@echo $(INSTALLLIB)

-include .depend
