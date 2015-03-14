/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_INTEGER_PARSER_HPP
#define IIOP_INTEGER_PARSER_HPP

#include <boost/detail/endian.hpp>
#include <boost/integer.hpp>
#include <iiop/endianness.hpp>
#include <iiop/alignment.hpp>

#include <climits>

namespace iiop {

namespace x3 = boost::spirit::x3;

template <std::size_t N>
struct unroll_tag {};

template <typename Iterator, typename Value, std::size_t E>
bool unroll_copy(Iterator& first, Iterator last, Value& v, unroll_tag<E>, unroll_tag<E>)
{
  std::cout << "All copied, value " << v << std::endl;
  return true; 
}

template <typename Iterator, typename Value, std::size_t N, std::size_t E>
bool unroll_copy(Iterator& first, Iterator last, Value& v, unroll_tag<N>, unroll_tag<E> e)
{
  if(first != last)
  {
    static_cast<unsigned char*>(static_cast<void*>(&v))[N] = *first;
    ++first;
    return unroll_copy(first, last, v, unroll_tag<N+1>(), e);
  }
  else
    return false;
}

template <typename Iterator, typename Value>
bool unroll_copy_backward(Iterator& first, Iterator last, Value& v, unroll_tag<0>) { return true; }

template <typename Iterator, typename Value, std::size_t N>
bool unroll_copy_backward(Iterator& first, Iterator last, Value& v, unroll_tag<N>)
{
  if(first != last)
  {
    static_cast<unsigned char*>(static_cast<void*>(&v))[N-1] = *first;
    ++first;
    return unroll_copy_backward(first, last, v, unroll_tag<N-1>());
  }
  else
    return false;
}

template <std::size_t N, typename Iterator, typename T>
bool reverse_unsigned_parse(Iterator& first, Iterator last, T& value)
{
  BOOST_MPL_ASSERT_RELATION(sizeof(T), ==, N/CHAR_BIT);
  return unroll_copy_backward(first, last, value, unroll_tag<N/CHAR_BIT>());
}

template <std::size_t N, typename Iterator, typename T>
bool normal_unsigned_parse(Iterator& first, Iterator last, T& value)
{
  BOOST_MPL_ASSERT_RELATION(sizeof(T), ==, N/CHAR_BIT);
  return unroll_copy(first, last, value, unroll_tag<0u>(), unroll_tag<N/CHAR_BIT>());
}

template <std::size_t N>
struct unsigned_parser : x3::parser<unsigned_parser<N> >
{
  static bool const handles_container = true;
  
  template <typename Iterator, typename Context, typename Attribute>
  bool parse(Iterator& first, Iterator const& last
             , Context& context, x3::unused_type
             , Attribute& attr) const
  {
    // Should align
    if(!alignment_padding<N>(first, last, context))
      return false;

    // bool endianness = generator_endianness<typename Context::attributes_type>
    //   ::call(ctx.attributes);
    bool endianness = true;
    
#ifdef BOOST_BIG_ENDIAN
    if(endianness)
#elif defined(BOOST_LITTLE_ENDIAN)
    if(!endianness)
#else
#error No native endianness found
#endif
      return reverse_unsigned_parse<N>(first, last, attr);
    else
      return normal_unsigned_parse<N>(first, last, attr);
  }
};

template <std::size_t N>
struct specific_unsigned_parser : x3::parser<specific_unsigned_parser<N> >
{
  static bool const handles_container = true;

  specific_unsigned_parser(typename boost::uint_t<N>::least value)
    : value(value) {}
  
  template <typename Iterator, typename Context, typename Skipper, typename Attribute>
  bool parse(Iterator& first, Iterator const& last
             , Context& ctx, Skipper const& skipper
             , Attribute& attr) const
  {
    std::cout << "specific_unsigned_parser::parse" << std::endl;
    // Should align
    // if(!alignment_padding<N>(first, last, ctx.attributes))
    //   return false;

    // bool endianness = generator_endianness<typename Context::attributes_type>
    //   ::call(ctx.attributes);
    bool endianness = true;

    typename boost::uint_t<N>::least v;
    bool r;
#ifdef BOOST_BIG_ENDIAN
    if(endianness)
#elif defined(BOOST_LITTLE_ENDIAN)
    if(!endianness)
#else
#error No native endianness found
#endif
    {
      r = reverse_unsigned_parse<N>(first, last, v);
    }
    else
    {
      r = normal_unsigned_parse<N>(first, last, v);
    }
    std::cout << "Value read " << v << " expecting value " << value << std::endl;
    return r && v == value;
  }

  typename boost::uint_t<N>::least value;
};

}

#endif
