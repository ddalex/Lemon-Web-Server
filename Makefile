all: prereq binary

include Makefile.inc

include src/Makefile

binary: $(BUILDDIR)/lemon

clean:
	rm -rf $(BUILDDIR)

prereq: 
	mkdir -p $(BUILDDIR)


.PHONY : all prereq binary clean

