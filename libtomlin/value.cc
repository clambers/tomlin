/**
 * Copyright (C) 2015 Chris Lamberson.
 *
 * This file is part of Tomlin.
 *
 * Tomlin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tomlin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tomlin.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "value.hh"

using namespace toml;

ostream_visitor::ostream_visitor(std::ostream& os) : os(os) {}

void ostream_visitor::operator()(dumpable const& d) const {
  d.dump(os);
}

ostream_joiner::ostream_joiner(std::ostream& os) : os(os), first(true) {}

void ostream_joiner::operator()(array_type::value_type const& v) {
  os << (first ? "" : ", ");
  boost::apply_visitor(ostream_visitor(os), v);
  first = false;
}

void ostream_joiner::operator()(object_type::value_type const& v) {
  os << (first ? "" : ", ") << v.first << ": ";
  boost::apply_visitor(ostream_visitor(os), v.second);
  first = false;
}
