#ifndef VALUE_HH
#define VALUE_HH

#include <boost/variant/recursive_variant.hpp>
#include <boost/function_output_iterator.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <utility>

namespace toml {
  using identifier_type = std::string;
  using boolean_type = bool;
  using integer_type = int;
  using float_type = double;
  using string_type = std::string;
  template<typename T> using array_type_cons = std::vector<T>;
  template<typename T> using object_type_cons = std::map<identifier_type, T>;

  struct dumpable {
    virtual ~dumpable() {}
    virtual void dump(std::ostream&) const = 0;
  };

  template<typename T> class value : public dumpable {
  public:
    using value_type = T;

    value();
    value(value_type const&);
    virtual ~value();
    virtual void dump(std::ostream&) const override;

  private:
    value_type v;
  };

  using value_type = boost::make_recursive_variant<
    value<boolean_type>,
    value<integer_type>,
    value<float_type>,
    value<string_type>,
    value<array_type_cons<boost::recursive_variant_> >,
    value<object_type_cons<boost::recursive_variant_> >
  >::type;

  using array_type = array_type_cons<value_type>;
  using object_type = object_type_cons<value_type>;

  class ostream_visitor : public boost::static_visitor<void> {
  public:
    ostream_visitor(std::ostream&);
    void operator()(dumpable const&) const;

  private:
    std::ostream& os;
  };

  class ostream_joiner {
  public:
    ostream_joiner(std::ostream&);
    void operator()(array_type::value_type const&);
    void operator()(object_type::value_type const&);

  private:
    std::ostream& os;
    bool first;
  };

  template<typename T> value<T>::value() {}

  template<typename T> value<T>::value(value_type const& v) : v(v) {}

  template<typename T> value<T>::~value() {}

  template<typename T> void value<T>::dump(std::ostream& os) const {
    os << v;
  }

  template<> void value<boolean_type>::dump(std::ostream& os) const {
    os << (v ? "true" : "false");
  }

  template<> void value<string_type>::dump(std::ostream& os) const {
    os << '"' << v << '"';
  }

  template<> void value<array_type>::dump(std::ostream& os) const {
    os << "[ ";
    std::copy(std::begin(v), std::end(v),
              boost::make_function_output_iterator(ostream_joiner(os)));
    os << " ]";
  }

  template<> void value<object_type>::dump(std::ostream& os) const {
    os << "{ ";
    std::copy(std::begin(v), std::end(v),
              boost::make_function_output_iterator(ostream_joiner(os)));
    os << " }";
  }
}

#endif
