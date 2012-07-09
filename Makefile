include Makefile.config

INCL=-I./include

SRCS=crt0.s
SRCC=start.c
SRCH=main.h
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)
ASUBDIRS=string stdlib stdio
OSUBDIRS=doc ctype
SUBDIRS=$(ASUBDIRS) $(OSUBDIRS)

PROJECT=jlibc
# change also in Doxyfile!!!
PROJECT_NUMBER=0.5.11

export PROJECT_NUMBER

PROJECT_NAME=$(PROJECT)-$(PROJECT_NUMBER)

DISTFILES=Makefile.config Makefile.template Makefile
DISTFILES+=ChangeLog LICENSE jaguar.inc TODO
DISTFILES+=$(SRCS) $(SRCC) $(SRCH) 
INSTALLLIB=crt0.o $(PROJECT).a

all: lib

$(PROJECT).a: Makefile subdirs $(OBJS)
	$(AR) rvs $(PROJECT).a start.o 
	for dir in $(ASUBDIRS); do $(AR) rvs $(PROJECT).a $$dir/*.o; done

.PHONY: subdirs $(SUBDIRS) all clean dist list-objects install lib uninstall

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ 

%.o: %.s
	$(MADMAC) $(MACFLAGS) $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	for dir in $(SUBDIRS); do $(MAKE) clean -C $$dir; done
	rm -f *~ $(OBJS) $(PROJECT).a .depend

.depend: $(SRCC)
	$(CC) $(CFLAGS) -M $(SRCC) > .depend

dist:
	mkdir -p $(PROJECT_NAME); \
	cp $(DISTFILES) $(PROJECT_NAME); \
	for file in include/*.h; do \
	  mkdir -p "$(PROJECT_NAME)/include"; \
	  cp "$$file" "$(PROJECT_NAME)/include"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s dist-files -C $$dir`; do \
	    mkdir -p "$(PROJECT_NAME)/$$dir"; \
	    cp "$$dir/$$file" "$(PROJECT_NAME)/$$dir"; \
	  done; \
	done; \
	tar cfvz $(PROJECT_NAME).tar.gz $(PROJECT_NAME); \
	rm -rf $(PROJECT_NAME)

list-objects:
	for file in $(INSTALLLIB); do \
	  echo "$$file"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s install-lib -C $$dir`; do \
	    echo "$$dir/$$file"; \
	  done; \
	done

lib: .depend $(INSTALLLIB)
	mkdir -p lib; \
	rm -f lib/*; \
	for file in $(INSTALLLIB); do \
	  install -m "u+rw,go+r" "$$file" "lib"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s install-lib -C $$dir`; do \
	    install -m "u+rw,go+r" "$$dir/$$file" "lib"; \
	  done; \
	done

install: lib
	mkdir -p "$(TARGET)/include"; \
	mkdir -p "$(TARGET)/lib"; \
	for file in include/*.h; do \
	  install -m "u+rw,go+r" "$$file" "$(TARGET)/include"; \
	done; \
	for file in lib/*; do \
	  install -m "u+rw,go+r" "$$file" "$(TARGET)/lib"; \
	done

uninstall: 
	for file in include/*.h; do \
	  rm -f "$(TARGET)/$$file"; \
	done; \
	for file in lib/*; do \
	  rm -f "$(TARGET)/$$file"; \
	done

-include .depend
