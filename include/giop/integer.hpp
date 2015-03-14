/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GIOP_TERMINALS_HPP
#define GIOP_TERMINALS_HPP

#include <boost/spirit/home/x3/core.hpp>
#include <boost/mpl/identity.hpp>

#include <iostream>

namespace giop {

namespace x3 = boost::spirit::x3;
namespace mpl = boost::mpl;
  
template <typename T>
struct integer_terminal : x3::parser<integer_terminal<T>>
{
  static bool const has_attribute = true;

  template <typename Iterator, typename Context, typename Attribute>
  bool parse(Iterator& first, Iterator const& last
             , Context const& context, x3::unused_type, Attribute& attr) const
  {
    return integer_parse(mpl::identity<T>(), first, last, context, x3::unused, attr);
  }
};

#define GIOP_INT_TERMINAL(name)                   \
  typedef integer_terminal<class name##_> name##type; \
  name##type const name##_ = {};

GIOP_INT_TERMINAL(ushort)
GIOP_INT_TERMINAL(short)
GIOP_INT_TERMINAL(ulong)
GIOP_INT_TERMINAL(long)
GIOP_INT_TERMINAL(ulong_long)
GIOP_INT_TERMINAL(long_long)
GIOP_INT_TERMINAL(float)
GIOP_INT_TERMINAL(double)
  
// using ::boost::spirit::bool_;
// using ::boost::spirit::ushort_;
// using ::boost::spirit::short_;
// using ::boost::spirit::ulong_;
// using ::boost::spirit::long_;
// using ::boost::spirit::ulong_long;
// using ::boost::spirit::long_long;
// using ::boost::spirit::float_;
// using ::boost::spirit::double_;
// using ::boost::spirit::lit;

// BOOST_SPIRIT_TERMINAL_EX(long_double);
// BOOST_SPIRIT_TERMINAL_EX(string);
// BOOST_SPIRIT_TERMINAL_EX(octet);
// BOOST_SPIRIT_TERMINAL_EX(endianness);
// BOOST_SPIRIT_TERMINAL_EX(sequence);
// BOOST_SPIRIT_TERMINAL_EX(raw_size);
  
}

#endif
