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

include_HEADERS = tomlin.hpp

lib_LTLIBRARIES = libtomlin.la
libtomlin_la_SOURCES = exceptions.cc exceptions.hh parser.cc parser.hh
libtomlin_la_CPPFLAGS = $(BOOST_CPPFLAGS)
libtomlin_la_CXXFLAGS = -std=c++11
libtomlin_la_LDFLAGS = -version-info 0:0:0
