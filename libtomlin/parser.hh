#ifndef PARSER_HH
#define PARSER_HH

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

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <vector>

namespace toml {
  namespace {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
  }

  template<typename T> struct grammar :
    qi::grammar<T, std::vector<string_type>(), ascii::space_type> {
    grammar() : grammar::base_type(data) {
      using qi::lit;
      using qi::lexeme;
      using ascii::char_;

      string %= '"'
             >> lexeme[+(char_ - '"')]
             >> '"';

      data %= *string;
    }

    qi::rule<T, std::vector<string_type>(), ascii::space_type> data;
    qi::rule<T, string_type(), ascii::space_type> string;
  };

  class parser {
  public:
    parser();
    parser(std::string const&);
    virtual ~parser();
    void parse();

  private:
    std::string path;
  };
}

#endif
