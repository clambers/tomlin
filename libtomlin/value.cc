#include "value.hh"

using namespace toml;

ostream_visitor::ostream_visitor(std::ostream& os) : os(os) {}

void ostream_visitor::operator()(dumpable const& d) const {
  d.dump(os);
}

ostream_joiner::ostream_joiner(std::ostream& os) : os(os), first(true) {}

void ostream_joiner::operator()(array_type::value_type const& v) {
  os << (first ? "" : ", ");
  boost::apply_visitor(ostream_visitor(os), v);
  first = false;
}

void ostream_joiner::operator()(object_type::value_type const& v) {
  os << (first ? "" : ", ") << v.first << ": ";
  boost::apply_visitor(ostream_visitor(os), v.second);
  first = false;
}
