all: prereq binary tests

include Makefile.inc

include src/Makefile
include tests/Makefile

binary: $(BUILDDIR)/lemon

test:   run_tests

clean:
	rm -rf $(BUILDDIR)
prereq: 
	mkdir -p $(BUILDDIR)

run_tests: tests
	for i in "$(TESTLIST)"; do \
	if ! $$i; then \
	echo "****test $$i failed !";\
	fi;\
	done


.PHONY : all prereq binary clean test tests 
.PHONY : run_tests
