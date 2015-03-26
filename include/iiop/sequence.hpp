/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_SEQUENCE_HPP
#define IIOP_SEQUENCE_HPP

#include <iiop/integer_parser.hpp>
#include <giop/sequence.hpp>

#include <boost/spirit/home/x3/core.hpp>
#include <boost/spirit/home/x3/support/traits/container_traits.hpp>
#include <boost/spirit/home/x3/core/detail/parse_into_container.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>

namespace iiop {

template <typename Subject, typename Iterator, typename Context, typename RContext, typename Attribute>
bool sequence_parse(giop::sequence_directive<Subject> const& self
                    , Iterator& first, Iterator const& last
                    , Context const& context, RContext const& rcontext, Attribute& attr)
{  
  unsigned_parser<32u> unsigned_;
  boost::uint_t<32u>::least size;
  bool r = unsigned_.parse(first, last, context, rcontext, size);
  std::cout << "sequence size " << size << std::endl;

  if(!r)
    return false;

  for(;size && r;--size)
    {
      // typename spirit::traits::container_value<Attribute>::type value;
      // r = subject.parse(first, last, ctx, skipper, value);
      // spirit::traits::push_back(attr, value);
      if(!x3::detail::parse_into_container(self.subject, first, last, context, rcontext, attr))
        return false;
    }
  return r;
}

template <typename Subject, typename OutputIterator, typename Context, typename RContext, typename Attribute>
bool sequence_generate(giop::sequence_directive<Subject> const& self
                       , OutputIterator& sink
                       , Context const& context, RContext const& rcontext, Attribute& attr)
{  
  unsigned_generator<32u> unsigned_;
  boost::uint_t<32>::least size = attr.size();
  bool r = unsigned_.generate(sink, context, x3::unused, size);
  for(auto
        first = x3::traits::begin(attr)
        , last = x3::traits::end(attr)
        ;first != last; ++first)
  {
    r = self.subject.generate(sink, context, x3::unused, *first);
  }
  return r;
}
  
}

namespace boost { namespace spirit { namespace x3 { namespace traits { namespace detail {

template <typename Subject, typename Context>
struct default_attribute_of<giop::sequence_directive<Subject>, Context>
  : build_container<typename attribute_of<Subject, Context>::type>
{};
        
} } } } }

#endif
