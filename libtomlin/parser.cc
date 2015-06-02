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

#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

using namespace toml;

parser::parser() {}

parser::parser(std::string const& p) : path(p) {}

parser::~parser() {}

void parser::parse() {
  std::ifstream in(path, std::ios_base::in);

  if (!in) {
    throw runtime_error("couldn't open file");
  }

  using storage_type = std::string;
  using storage_iterator = storage_type::const_iterator;
  using grammar = grammar<storage_iterator>;

  storage_type storage;
  in.unsetf(std::ios::skipws);
  std::copy(std::istream_iterator<char>(in),
            std::istream_iterator<char>(),
            std::back_inserter(storage));

  grammar data;
  std::vector<string_type> ast;

  using boost::spirit::ascii::space;

  storage_iterator iter = std::begin(storage);
  storage_iterator end = std::end(storage);

  bool result = phrase_parse(iter, end, data, space, ast);

  if (result && iter == end) {
    for (auto s : ast) {
      std::cout << s << std::endl;
    }
  }
}
