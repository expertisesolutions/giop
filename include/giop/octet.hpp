/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GIOP_OCTET_HPP
#define GIOP_OCTET_HPP

namespace giop {

namespace x3 = boost::spirit::x3;

struct octet_partor : x3::parser<octet_partor>
                    , x3::generator<octet_partor>
{
  typedef int attribute_type;
  static bool const has_attribute = true;

  template <typename Iterator, typename Context, typename Attribute>
  bool parse(Iterator& first, Iterator const& last
             , Context const& context, x3::unused_type, Attribute& attr) const
  {
    return octet_parse(*this, first, last, context, x3::unused, attr);
  }

  template <typename OutputIterator, typename Context, typename Attribute>
  bool generate(OutputIterator& first
                , Context const& context, x3::unused_type, Attribute& attr) const
  {
    return octet_generate(*this, first, context, x3::unused, attr);
  }
};
  
octet_partor octet = {};
  
}

#endif
