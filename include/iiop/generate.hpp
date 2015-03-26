/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_GENERATE_HPP
#define IIOP_GENERATE_HPP

#include <boost/spirit/home/x3/core.hpp>

#include <iiop/alignment.hpp>
#include <iiop/forward_back_insert_iterator.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;

struct iiop_generate_tag;
  
template <typename Container, typename ET, typename Attribute>
inline bool
generate(Container& container, ET const& expression, Attribute& attr)
{
  typedef forward_back_insert_iterator<Container> iterator;
  iterator sink(container);
  auto iiop_context = boost::spirit::x3::make_context<iiop_generate_tag>(x3::unused);
  alignment_attribute<iterator> alignment_attr{sink, 0u};
  auto align_context = boost::spirit::x3::make_context<alignment_tag, alignment_attribute<iterator>>
    (alignment_attr, iiop_context);
  return as_generator(expression).generate(sink, align_context, x3::unused, attr);
}

}

#endif
