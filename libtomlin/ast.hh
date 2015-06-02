#ifndef AST_HH
#define AST_HH

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

#include <boost/config/warning_disable.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace toml {
  namespace ast {
    using integer_type = long;
    using float_type = double;
    using string_type = std::string;
    using identifier_type = std::string;
    using value_type = boost::variant<
      integer_type,
      float_type,
      string_type
    >;

    struct statement_type {
      identifier_type identifier;
      value_type value;

      void dump(std::ostream&);
    };

    using statements_type = std::vector<statement_type>;

    struct ostream_visitor : boost::static_visitor<> {
      std::ostream& os;

      ostream_visitor(std::ostream&);
      void operator()(integer_type const&) const;
      void operator()(float_type const&) const;
      void operator()(string_type const&) const;
    };
  }
}

BOOST_FUSION_ADAPT_STRUCT(
  toml::ast::statement_type,
  (toml::ast::identifier_type, identifier)
  (toml::ast::value_type, value)
)

#endif
