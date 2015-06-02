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

#include "ast.hh"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace toml {
  namespace {
    namespace qi = boost::spirit::qi;
    namespace lex = boost::spirit::lex;
  }

  template<typename Lexer>
  struct tokens : lex::lexer<Lexer> {
    tokens() {
      identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
      integer = "[+-]?[0-9]+";
      float_ = "[+-]?[0-9]+\\.[0-9]+";
      string = "\\\"[^\"]*\\\"";

      this->self
        = lex::token_def<>('=')
        | '[' | ']'
        | identifier
        | integer
        | float_
        | string
        ;

      this->self("WS") = lex::token_def<>("[ \\t\\n]+");
    }

    lex::token_def<ast::identifier_type> identifier;
    lex::token_def<ast::integer_type> integer;
    lex::token_def<ast::float_type> float_;
    lex::token_def<ast::string_type> string;
  };

  template<typename Iter, typename Lexer>
  struct grammar : qi::grammar<Iter, ast::statements_type(), qi::in_state_skipper<Lexer> > {
    template<typename TokenDef>
    grammar(TokenDef const& tok) : grammar::base_type(data) {
      data %= *assignment;
      assignment %= tok.identifier >> '=' >> expression;
      expression %= tok.integer | tok.float_ | tok.string;
    }

    qi::rule<Iter, ast::statements_type(), qi::in_state_skipper<Lexer> > data;
    qi::rule<Iter, ast::statement_type(), qi::in_state_skipper<Lexer> > assignment;
    qi::rule<Iter, ast::value_type(), qi::in_state_skipper<Lexer> > expression;
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
