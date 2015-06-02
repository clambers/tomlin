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
      integer = "-?[0-9]+";

      this->self = lex::token_def<>('"') | '=' | integer;
      this->self += identifier;
      this->self("WS") = lex::token_def<>("[ \\t\\n]+");
    }

    lex::token_def<std::string> identifier;
    lex::token_def<long> integer;
  };

  template<typename Iter, typename Lexer>
  struct grammar : qi::grammar<Iter, qi::in_state_skipper<Lexer> > {
    template<typename TokenDef>
    grammar(TokenDef const& tok) : grammar::base_type(data) {
      using qi::_1;
      using qi::_2;
      using boost::spirit::_val;
      using boost::phoenix::val;

      data
        = *assignment
        ;

      assignment
        = (tok.identifier >> '=' >> expression) [
            std::cout << val("assign ") << _1 << " to " << _2 << std::endl
          ]
        ;

      expression
        = tok.identifier [ _val = _1 ]
        | tok.integer    [ _val = _1 ]
        ;
    }

    typedef boost::variant<long, std::string> expression_type;

    qi::rule<Iter, qi::in_state_skipper<Lexer> > data;
    qi::rule<Iter, qi::in_state_skipper<Lexer> > assignment;

    qi::rule<Iter, expression_type(), qi::in_state_skipper<Lexer> > expression;
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
