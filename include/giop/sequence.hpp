/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GIOP_SEQUENCE_HPP
#define GIOP_SEQUENCE_HPP

#include <boost/spirit/home/x3/core.hpp>

namespace giop {

template <typename Subject>
struct sequence_directive : x3::unary_parser<Subject, sequence_directive<Subject>>
  , x3::generator_base
{
  typedef x3::unary_parser<Subject, sequence_directive<Subject>> base_type;

  template <typename Iterator, typename Context, typename RContext, typename Attribute>
  bool parse(Iterator& first, Iterator const& last
             , Context const& context, RContext const& rcontext, Attribute& attr) const
  {
    return sequence_parse(*this, first, last, context, rcontext, attr);
  }  

  template <typename OutputIterator, typename Context, typename RContext, typename Attribute>
  bool generate(OutputIterator& first
             , Context const& context, RContext const& rcontext, Attribute& attr) const
  {
    return sequence_generate(*this, first, context, rcontext, attr);
  }

  sequence_directive(Subject const& subject)
    : base_type(subject) {}
};
  
struct sequence_gen
{
  template <typename Subject>
  sequence_directive<typename x3::extension::as_parser<Subject>::value_type>
  operator[](Subject const& subject) const
  {
    return {x3::as_parser(subject)};
  }
};

sequence_gen const sequence = {};
  
}

#endif
