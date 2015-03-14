/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GIOP_STRING_HPP
#define GIOP_STRING_HPP

#include <boost/spirit/home/x3/core.hpp>

namespace giop {

struct string_terminal : x3::parser<string_terminal>
{
  template <typename Iterator, typename Context, typename RContext, typename Attribute>
  bool parse(Iterator& first, Iterator const& last
             , Context const& context, RContext const& rcontext, Attribute& attr) const
  {
    return string_parse(*this, first, last, context, rcontext, attr);
  }  
};

string_terminal const string = {};

}
  
// namespace boost { namespace spirit { namespace x3 { namespace traits { namespace detail {

// template <typename Context>
// struct default_attribute_of<giop::string_terminal, Context>
// {
//   typedef unsigned char type;
// };
        
// } } } } }

#endif
