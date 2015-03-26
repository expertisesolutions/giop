/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_PARSE_HPP
#define IIOP_PARSE_HPP

#include <boost/spirit/home/x3/core.hpp>

#include <iiop/alignment.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;

struct iiop_parse_tag;
  
template <typename Iterator, typename ET, typename Attribute>
inline bool
parse(Iterator& first, Iterator last, ET const& expression, Attribute& attr)
{
  Iterator saved = first;
  auto iiop_context = boost::spirit::x3::make_context<iiop_parse_tag>(x3::unused);
  auto align_context = boost::spirit::x3::make_context<alignment_tag, Iterator>(saved, iiop_context);
  return as_parser(expression).parse(first, last, align_context, x3::unused, attr);
}

}

#endif
