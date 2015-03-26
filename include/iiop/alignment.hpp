/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef IIOP_ALIGNMENT_HPP
#define IIOP_ALIGNMENT_HPP

#include <climits>

#include <boost/spirit/home/x3/support/context.hpp>

namespace iiop {

namespace x3 = boost::spirit::x3;
namespace mpl = boost::mpl;

struct alignment_tag;

template <typename OutputIterator>
struct alignment_attribute
{
  OutputIterator first;
  std::size_t offset;
};
  
template <std::size_t N, typename Iterator, typename Context>
bool alignment_padding(Iterator& first, Iterator last, Context const& context)
{
  std::cout << "alignment_padding for " << N/CHAR_BIT << " bytes" << std::endl;
  std::cout << (void*)first << std::endl;
  Iterator saved = context.get(mpl::identity<alignment_tag>());
  std::cout << (void*)saved << std::endl;

  std::size_t distance = std::distance(saved, first) + /*align_from.offset*/0;
  std::cout << "position distance " << distance << std::endl;

  const std::size_t alignment = N/CHAR_BIT;

  int remainder = distance % alignment;
  int padding = remainder? alignment - remainder : 0;
  for(;padding && first != last; --padding)
  {
    std::cout << "padding byte" << std::endl;
    ++first;
  }
  return first != last;
}

template <std::size_t N, typename OutputIterator, typename Context>
void alignment_padding(OutputIterator& sink, Context const& context)
{
  auto align_from = context.get(mpl::identity<alignment_tag>());
  std::cout << "alignment_padding for " << N/CHAR_BIT << " bytes of alignment" << std::endl;

  std::size_t distance = std::distance(align_from.first, sink) + align_from.offset;
  std::cout << "alignment_padding distance from start " << distance << std::endl;
  const std::size_t alignment = N/CHAR_BIT;

  int remainder = distance % alignment;
  int padding = remainder? alignment - remainder : 0;
  std::cout << "padding bytes " << padding << std::endl;
  for(;padding != 0; --padding)
  {
    std::cout << "padding byte" << std::endl;
    *sink = '\0';
    ++sink;
  }
}
  
}

#endif
