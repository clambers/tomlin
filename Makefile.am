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

ACLOCAL_AMFLAGS = -I m4
AM_MAKEFLAGS = --no-print-directory
EXTRA_DIST = m4/ax_boost_base.m4
SUBDIRS = libtomlin tests

pcdir = $(libdir)/pkgconfig

pc_DATA = tomlin.pc
doc_DATA = COPYING COPYING.LESSER README.md NEWS.md AUTHORS.md

EXTRA_DIST += $(doc_DATA)
