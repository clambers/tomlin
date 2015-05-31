TESTSUITE = $(top_srcdir)/tests/testsuite
TESTSUITE_AT = testsuite.at library.at

EXTRA_DIST = $(TESTSUITE_AT) $(TESTSUITE)
DISTCLEANFILES = atlocal
MAINTAINERCLEANFILES = $(TESTSUITE)

AUTOM4TE = $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

check_SCRIPTS = atlocal atconfig
RUN_TESTSUITE_deps = all $(TESTSUITE) $(check_SCRIPTS)

$(TESTSUITE): $(TESTSUITE_AT)
	$(AM_V_GEN) $(AUTOTEST) -I$(srcdir) -o $@.tmp $@.at
	$(AM_V_at)mv $@.tmp $@

check-local: $(RUN_TESTSUITE_deps)
	$(TESTSUITE)

installcheck-local: $(RUN_TESTSUITE_deps)
	$(TESTSUITE) AUTOTEST_PATH='$(bindir)'

clean-local:
	test ! -f $(TESTSUITE) || $(TESTSUITE) --clean
