/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_OCTET_HPP
#define IIOP_OCTET_HPP

#include <giop/octet.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;
  
template <typename Iterator, typename Context, typename Attribute>
bool octet_parse(giop::octet_parser const&, Iterator& first, Iterator const& last
                 , Context const& context, x3::unused_type, Attribute& attr)
{
  if(first != last)
    {
      attr = *first++;
      std::cout << "octet parsed " << (int)attr << std::endl;
      return true;
    }
  else
    {
      std::cout << "failed octet" << std::endl;
      return false;
    }
}

}

namespace boost { namespace spirit { namespace x3 { namespace traits { namespace detail {

template <typename Context>
struct default_attribute_of<giop::octet_parser, Context>
{
  typedef unsigned char type;
};
        
} } } } }

#endif
