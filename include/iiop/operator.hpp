/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_OPERATOR_HPP
#define IIOP_OPERATOR_HPP

#include <boost/spirit/home/x3/core.hpp>
// #include <boost/spirit/home/x3/support/traits/container_traits.hpp>
// #include <boost/spirit/home/x3/core/detail/parse_into_container.hpp>
#include <boost/spirit/home/x3/operator/sequence.hpp>
#include <iiop/integer_parser.hpp>

namespace iiop {

// template <typename Left, typename Right, typename Iterator, typename Context, typename RContext, typename Attribute>
// inline bool operator_and_parse(giop::operator_and<Left, Right> const& self
//                                , Iterator& first, Iterator const& last
//                                , Context const& context, RContext const& rcontext, x3::unused_type)
// {
//   Iterator save = first;
//   if (self.left.parse(first, last, context, rcontext, x3::unused)
//       && self.right.parse(first, last, context, rcontext, x3::unused))
//     return true;
//   first = save;
//   return false;
// }

// template <typename Left, typename Right, typename Iterator, typename Context, typename RContext, typename Attribute>
// inline bool operator_and_parse(giop::operator_and<Left, Right> const& self
//                                , Iterator& first, Iterator const& last
//                                , Context const& context, RContext const& rcontext, Attribute& attr)
// {
//   return x3::detail::parse_sequence(self, first, last, context, rcontext, attr
//                                     , typename x3::traits::attribute_category<Attribute>::type());
// }
  
//   unsigned_parser<32u> unsigned_;
//   boost::uint_t<32u>::least size;
//   bool r = unsigned_.parse(first, last, context, rcontext, size);
//   std::cout << "sequence size " << size << std::endl;

//   if(!r)
//     return false;

//   for(;size && r;--size)
//     {
//       // typename spirit::traits::container_value<Attribute>::type value;
//       // r = subject.parse(first, last, ctx, skipper, value);
//       // spirit::traits::push_back(attr, value);
//       if(!x3::detail::parse_into_container(self.subject, first, last, context, rcontext, attr))
//         return false;
//     }
//   return r;
// }
  
}



#endif
