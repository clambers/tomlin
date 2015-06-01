# Copyright (C) 2015 Chris Lamberson.
#
# This file is part of Tomlin.
#
# Tomlin is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Tomlin is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Tomlin.  If not, see <http://www.gnu.org/licenses/>.

TESTSUITE = $(top_srcdir)/tests/testsuite
TESTSUITE_AT = testsuite.at library.at

AUTOM4TE = $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

check_SCRIPTS = atlocal atconfig
RUN_TESTSUITE_deps = all $(TESTSUITE) $(check_SCRIPTS)

EXTRA_DIST = $(TESTSUITE_AT) $(TESTSUITE)
DISTCLEANFILES = $(check_SCRIPTS)
MAINTAINERCLEANFILES = $(TESTSUITE)

$(TESTSUITE): $(TESTSUITE_AT)
	$(AM_V_GEN) $(AUTOTEST) -I$(srcdir) -o $@.tmp $@.at
	$(AM_V_at)mv $@.tmp $@

check-local: $(RUN_TESTSUITE_deps)
	$(TESTSUITE)

installcheck-local: $(RUN_TESTSUITE_deps)
	$(TESTSUITE) AUTOTEST_PATH='$(bindir)'

clean-local:
	test ! -f $(TESTSUITE) || $(TESTSUITE) --clean
