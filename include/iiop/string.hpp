/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_STRING_HPP
#define IIOP_STRING_HPP

#include <giop/string.hpp>
#include <iiop/octet.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;
  
template <typename Iterator, typename Context, typename Attribute>
bool string_parse(giop::string_terminal const&, Iterator& first, Iterator const& last
                 , Context const& context, x3::unused_type, Attribute& attr)
{
  unsigned_parser<32u> unsigned_;
  boost::uint_t<32u>::least size;
  bool r = unsigned_.parse(first, last, context, x3::unused, size);
  std::cout << "sequence size " << size << std::endl;

  if(!r)
    return false;

  giop::octet_parser octet;
  for(;size > 1 && r;--size)
    {
      if(!x3::detail::parse_into_container(octet, first, last, context, x3::unused, attr))
        return false;
    }
  if(size != 1 || !r)
    return false;
  unsigned char c = 0;
  r = octet.parse(first, last, context, x3::unused, c);
  return r && c == 0;
}

}

namespace boost { namespace spirit { namespace x3 { namespace traits { namespace detail {

template <typename Context>
struct default_attribute_of<giop::string_terminal, Context>
{
  typedef std::string type;
};
        
} } } } }

#endif
