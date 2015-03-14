/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_INTEGER_HPP
#define IIOP_INTEGER_HPP

#include <giop/integer.hpp>
#include <iiop/integer_parser.hpp>

#include <boost/spirit/home/x3/core.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;
namespace mpl = boost::mpl;
  
template <typename Iterator, typename Context, typename Attribute>
bool integer_parse(mpl::identity<class giop::ushort_>, Iterator& first, Iterator const& last
                   , Context const& context, x3::unused_type, Attribute& attr)
{
  return unsigned_parser<16u>().parse(first, last, context, x3::unused, attr);
}
  
}

namespace boost { namespace spirit { namespace x3 { namespace traits { namespace detail {

template <typename Context>
struct default_attribute_of<giop::integer_terminal<class giop::ushort_>, Context>
{
  typedef boost::uint_t<16u>::least type;
};
        
} } } } }

#endif
