#include "ast.hh"

void toml::ast::statement_type::dump(std::ostream& os) {
  os << identifier << ": ";
  boost::apply_visitor(value, ostream_visitor(os));
}

toml::ast::ostream_visitor(std::ostream& os) : os(os) {}

void toml::ast::ostream_visitor::operator()(integer_type const& integer) const {
  os << integer;
}

void toml::ast::ostream_visitor::operator()(float_type const& float_) const {
  os << float_;
}

void toml::ast::ostream_visitor::operator()(string_type const& string) const {
  os << string;
}
