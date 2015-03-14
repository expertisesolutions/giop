/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GIOP_OPERATOR_HPP
#define GIOP_OPERATOR_HPP

#include <boost/spirit/home/x3/core.hpp>
#include <boost/spirit/home/x3/operator/sequence.hpp>

namespace giop {

// template <typename Left, typename Right>
// struct operator_and : x3::binary_parser<Left, Right, operator_and<Left, Right>>
// {
//   typedef x3::binary_parser<Left, Right, operator_and<Left, Right>> base_type;

//   template <typename Iterator, typename Context, typename RContext, typename Attribute>
//   inline bool parse(Iterator& first, Iterator const& last
//                     , Context const& context, RContext const& rcontext, Attribute& attr) const
//   {
//     return operator_and_parse(*this, first, last, context, rcontext, attr);
//   }
  
//   operator_and(Left left, Right right)
//     : base_type(left, right) {}
// };

template <typename Left, typename Right>
inline
x3::sequence
<typename x3::extension::as_parser<Left>::value_type
 , typename x3::extension::as_parser<Right>::value_type
 >
operator&(Left const& left, Right const& right)
{
  return {x3::as_parser(left), x3::as_parser(right)};
}

}

#endif
