/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_ENDIANNESS_HPP
#define IIOP_ENDIANNESS_HPP

#include <giop/endianness.hpp>
#include <giop/octet.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;

template <typename Subject, typename Iterator, typename Context, typename RContext, typename Attribute>
inline bool endianness_parse(giop::endianness_directive<Subject> const& self
                             , Iterator& first, Iterator const& last
                             , Context const& context, RContext const& rcontext, Attribute& attr)
{
  std::cout << "endianness_parse" << std::endl;
  unsigned char octet;
  if(giop::octet_partor().parse(first, last, context, x3::unused, octet))
    {
      std::cout << "endianness " << (int)octet << std::endl;
      return self.subject.parse(first, last, context, rcontext, attr);
    }
  else
    return false;
}

  
}

#endif
