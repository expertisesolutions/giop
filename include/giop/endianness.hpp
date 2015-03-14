/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GIOP_ENDIANNESS_HPP
#define GIOP_ENDIANNESS_HPP

#include <boost/spirit/home/x3/core.hpp>
#include <boost/mpl/identity.hpp>

namespace giop {

namespace x3 = boost::spirit::x3;

template <typename Subject>
struct endianness_directive : x3::unary_parser<Subject, endianness_directive<Subject> >
{
  typedef x3::unary_parser<Subject, endianness_directive<Subject>> base_type;
  
  static bool const has_attribute = true;

  endianness_directive(Subject const& subject)
    : base_type(subject) {}
  
  template <typename Iterator, typename Context, typename RContext, typename Attribute>
  inline bool parse(Iterator& first, Iterator const& last
                    , Context const& context, RContext const& rcontext, Attribute& attr) const
  {
    return endianness_parse(*this, first, last, context, rcontext, attr);
  }
};
  
struct endianess_gen
{
  template <typename Subject>
  endianness_directive<typename x3::extension::as_parser<Subject>::value_type>
  operator[](Subject const& subject) const
  {
    return {x3::as_parser(subject)};
  }
};

endianess_gen const endianness = {};

}

#endif
