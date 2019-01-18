include ../../Makefile.gnu_32

COMPILE = $(COMPILE_OPTIMIZED)
CFLAGS = $(CFLAGS_OPTIMIZED)

LINK = $(LINK_OPTIMIZED)
LFLAGS = $(LFLAGS_OPTIMIZED)

all: libmatchbox.a

include ../Makefile.lib

libmatchbox.a: $(OBJS)
	$(ARCHIVE) $(AFLAGS) *.o

clean:
	rm -f *~ *.o *.a
