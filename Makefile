include Makefile.config

SRCS=crt0.s
SRCC=start.c
SRCH=main.h jagtypes.h jagdefs.h tom.h gpu.h jerry.h
OBJS=$(SRCC:.c=.o) $(SRCS:.s=.o)
ASUBDIRS=string stdlib stdio
OSUBDIRS=doc ctype
SUBDIRS=$(ASUBDIRS) $(OSUBDIRS)

PROJECT=jlibc
# change also in Doxyfile!!!
PROJECT_NUMBER=0.5.10

export PROJECT_NUMBER

PROJECT_NAME=$(PROJECT)-$(PROJECT_NUMBER)

DISTFILES=Makefile.config Makefile $(SRCS) $(SRCC) $(SRCH) 
DISTFILES+=ChangeLog LICENSE jaguar.inc TODO build.sh
INSTALLH=jagtypes.h jagdefs.h tom.h gpu.h jerry.h
INSTALLLIB=crt0.o $(PROJECT).a

all: .depend $(PROJECT).a

$(PROJECT).a: Makefile subdirs $(OBJS)
	$(AR) rvs $(PROJECT).a start.o 
	for dir in $(ASUBDIRS); do $(AR) rvs $(PROJECT).a $$dir/*.o; done

.PHONY: subdirs $(SUBDIRS) all clean dist list-headers list-objects install

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
	$(CC) -M $(SRCC) > .depend

dist:
	mkdir -p $(PROJECT_NAME); \
	cp $(DISTFILES) $(PROJECT_NAME); \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s dist-files -C $$dir`; do \
	    mkdir -p "$(PROJECT_NAME)/$$dir"; \
	    cp "$$dir/$$file" "$(PROJECT_NAME)/$$dir"; \
	  done; \
	done; \
	tar cfvz $(PROJECT_NAME).tar.gz $(PROJECT_NAME); \
	rm -rf $(PROJECT_NAME)

list-headers:
	for file in $(INSTALLH); do \
	  echo "$$file"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s install-h -C $$dir`; do \
	    echo "$$dir/$$file"; \
	  done; \
	done

list-objects:
	for file in $(INSTALLLIB); do \
	  echo "$$file"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s install-lib -C $$dir`; do \
	    echo "$$dir/$$file"; \
	  done; \
	done

install:
	mkdir -p "$(TARGET)/include"; \
	mkdir -p "$(TARGET)/lib"; \
	for file in $(INSTALLH); do \
	  install -m "u+rw,go+r" "$$file" "$(TARGET)/include"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s install-h -C $$dir`; do \
	    install -m "u+rw,go+r" "$$dir/$$file" "$(TARGET)/include"; \
	  done; \
	done; \
	for file in $(INSTALLLIB); do \
	  install -m "u+rw,go+r" "$$file" "$(TARGET)/lib"; \
	done; \
	for dir in $(SUBDIRS); do \
	  for file in `$(MAKE) -s install-lib -C $$dir`; do \
	    install -m "u+rw,go+r" "$$dir/$$file" "$(TARGET)/lib"; \
	  done; \
	done


-include .depend
