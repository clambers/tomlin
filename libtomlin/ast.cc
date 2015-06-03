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

#include "ast.hh"

#include <boost/variant/apply_visitor.hpp>

void toml::ast::statement_type::dump(std::ostream& os) {
  os << identifier << ": ";
  boost::apply_visitor(ostream_visitor(os), value);
  os << std::endl;
}

toml::ast::ostream_visitor::ostream_visitor(std::ostream& os) : os(os) {}

void toml::ast::ostream_visitor::operator()(integer_type const& integer) const {
  os << integer;
}

void toml::ast::ostream_visitor::operator()(float_type const& float_) const {
  os << float_;
}

void toml::ast::ostream_visitor::operator()(string_type const& string) const {
  os << string;
}
