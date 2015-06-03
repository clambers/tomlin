#ifndef LEXER_HH
#define LEXER_HH

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
#include <boost/spirit/include/lex_lexertl.hpp>

namespace toml {
  namespace {
    namespace lex = boost::spirit::lex;
  }

  template<typename Lexer>
  struct tokens : lex::lexer<Lexer> {
    tokens() {
      identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
      boolean = "\"true\"|\"false\"";
      integer = "[+-]?[0-9]+";
      float_ = "[+-]?[0-9]+\\.[0-9]+";
      basic_string = "\\\"[^\"]*\\\"";
      literal_string = "'[^']*'";

      this->self
        = lex::token_def<>('=')
        | '[' | ']'
        | identifier
        | boolean
        | integer
        | float_
        | basic_string
        | literal_string
        ;

      this->self("WS") = lex::token_def<>("[ \\t\\n]+");
    }

    lex::token_def<ast::identifier_type> identifier;
    lex::token_def<ast::boolean_type> boolean;
    lex::token_def<ast::integer_type> integer;
    lex::token_def<ast::float_type> float_;
    lex::token_def<ast::string_type> basic_string;
    lex::token_def<ast::string_type> literal_string;
  };
}

#endif
