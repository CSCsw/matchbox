include ../../Makefile.gnu_32

COMPILE = $(COMPILE_DEBUG)
CFLAGS = $(CFLAGS_DEBUG)

LINK = $(LINK_DEBUG)
LFLAGS = $(LFLAGS_DEBUG)

MATCHBOX_LIBRARY = $(MATCHBOX_LIB_DEBUG_DIR)/$(MATCHBOX_LIB_FILES)

include ../Makefile.tests

clean:
	rm -f $(TESTS) *.o *~
