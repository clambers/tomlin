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

#include "exceptions.hh"

std::ostringstream toml::runtime_error::full_message;

toml::runtime_error::runtime_error(std::string const& e)
  : std::runtime_error("tomlin error: "), error_message(e) {}

char const* toml::runtime_error::what() const noexcept {
  full_message.str("");
  full_message << std::runtime_error::what() << error_message;
  return full_message.str().c_str();
}
