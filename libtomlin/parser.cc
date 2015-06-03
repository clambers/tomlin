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

#include "parser.hh"
#include "exceptions.hh"
#include "ast.hh"
#include "lexer.hh"
#include "grammar.hh"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>

toml::parser::parser() {}

toml::parser::parser(std::string const& p) : path(p) {}

toml::parser::~parser() {}

void toml::parser::parse() {
  typedef std::string::iterator base_iterator_type;
  typedef lex::lexertl::token<
    base_iterator_type,
    boost::mpl::vector<
      ast::boolean_type,
      ast::integer_type,
      ast::float_type,
      ast::string_type
    >
  > token_type;
  typedef lex::lexertl::lexer<token_type> lexer_type;
  typedef toml::tokens<lexer_type> tokens_type;
  typedef tokens_type::iterator_type iterator_type;
  typedef toml::grammar<iterator_type, tokens_type::lexer_def> grammar_type;

  tokens_type tokens;
  grammar_type grammar(tokens);

  std::ifstream in(path, std::ios::in | std::ios::binary);
  std::ostringstream os;
  os << in.rdbuf();
  in.close();
  std::string contents(os.str());

  std::string::iterator it = contents.begin();
  iterator_type iter = tokens.begin(it, contents.end());
  iterator_type end = tokens.end();

  ast::statements_type statements;

  bool result =
    qi::phrase_parse(iter, end, grammar,
                     qi::in_state("WS")[tokens.self], statements);

  if (result && iter == end) {
    std::cout << "parsing succeeded" << std::endl;
    for (auto statement : statements) {
      statement.dump(std::cout);
    }
  } else {
    throw runtime_error("parsing failed");
  }
}
