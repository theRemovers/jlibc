include ../Makefile.config

SRCC=islower.c isprint.c
SRCC+=ispunct.c isspace.c isupper.c isxdigit.c toupper.c tolower.c
SRCS=
SRCH=ctype.h
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)

DISTFILES=Makefile $(SRCC) $(SRCH) $(SRCS) 

INSTALLH=ctype.h
INSTALLLIB=

all: .depend $(OBJS)

%.o: %.s
	$(MADMAC) $(MACFLAGS) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ $(OBJS) .depend

.depend: $(SRCC)
	$(CC) -M $(SRCC) > .depend

dist-files:
	@echo $(DISTFILES)

install-h:
	@echo $(INSTALLH)

install-lib:
	@echo $(INSTALLLIB)

-include .depend
