include Makefile.common

all: debug

debug:
	cd $(MATCHBOX_LIB)/debug; make;
	#cd $(MATCHBOX_TESTS)/debug; make;
	cd $(MATCHBOX_EXAMPLES)/debug; make;

optimized:
	cd $(MATCHBOX_LIB)/optimized; make;
	#cd $(MATCHBOX_TESTS)/optimized; make;
	cd $(MATCHBOX_EXAMPLES)/optimized; make;

clean:
	rm -rf *~
	cd $(MATCHBOX_INCLUDE); make clean;
	cd $(MATCHBOX_SRC); make clean;
	cd $(MATCHBOX_LIB); make clean;
	cd $(MATCHBOX_LIB)/debug; make clean;
	cd $(MATCHBOX_LIB)/optimized; make clean;
	cd $(MATCHBOX_TESTS); make clean;
	cd $(MATCHBOX_TESTS)/debug; make clean;
	cd $(MATCHBOX_TESTS)/optimized; make clean;
	cd $(MATCHBOX_EXAMPLES); make clean;
	cd $(MATCHBOX_EXAMPLES)/debug; make clean;
	cd $(MATCHBOX_EXAMPLES)/optimized; make clean;
