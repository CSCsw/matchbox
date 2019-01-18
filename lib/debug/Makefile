include ../../Makefile.gnu_32

COMPILE = $(COMPILE_DEBUG)
CFLAGS = $(CFLAGS_DEBUG)

LINK = $(LINK_DEBUG) 
LFLAGS = $(LFLAGS_DEBUG)

all: libmatchbox.a

include ../Makefile.lib

libmatchbox.a: $(OBJS)
	$(ARCHIVE) $(AFLAGS) *.o

clean:
	rm -f *~ *.o *.a
