#ifndef GRAMMAR_HH
#define GRAMMAR_HH

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
#include "lexer.hh"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace toml {
  namespace {
    namespace qi = boost::spirit::qi;
  }

  template<typename Iter, typename Lexer>
  struct grammar : qi::grammar<Iter, ast::statements_type(), qi::in_state_skipper<Lexer> > {
    template<typename TokenDef>
    grammar(TokenDef const& tok) : grammar::base_type(data) {
      data %= *assignment;

      assignment %= tok.identifier >> '=' >> expression;

      string
        %= tok.basic_string
         | tok.literal_string;

      expression
        %= tok.boolean
         | tok.integer
         | tok.float_
         | string;
    }

    qi::rule<Iter, ast::statements_type(), qi::in_state_skipper<Lexer> > data;
    qi::rule<Iter, ast::statement_type(), qi::in_state_skipper<Lexer> > assignment;
    qi::rule<Iter, ast::string_type(), qi::in_state_skipper<Lexer> > string;
    qi::rule<Iter, ast::value_type(), qi::in_state_skipper<Lexer> > expression;
  };
}

#endif
