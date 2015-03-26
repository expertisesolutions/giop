/* (c) Copyright 2014 Felipe Magno de Almeida
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <giop/integer.hpp>
#include <giop/endianness.hpp>
#include <giop/octet.hpp>
#include <giop/string.hpp>
#include <giop/operator.hpp>
#include <giop/sequence.hpp>
#include <iiop/integer.hpp>
#include <iiop/generate.hpp>
#include <iiop/endianness.hpp>
#include <iiop/operator.hpp>
#include <iiop/sequence.hpp>
#include <iiop/octet.hpp>
#include <iiop/string.hpp>
#include <iiop/alignment.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/equal_to.hpp>
#include <boost/fusion/include/at.hpp>

int main()
{
  namespace fusion = boost::fusion;
  typedef fusion::vector<unsigned char, unsigned char, std::string
                         , unsigned short, std::vector<unsigned char> > attribute_type;

  const char object_key_literal[] = "RootPOA/OBJECTKEY";
  std::vector<unsigned char> object_key;
  std::copy(&object_key_literal[0], &object_key_literal[sizeof(object_key_literal)-1]
            , std::back_inserter(object_key));
  attribute_type attribute('\1', '\0', "localhost", 8080, object_key);

  const char test_output[] = 
    "\x01\x01\x00\x00\x0A\x00\x00\x00\x6C\x6F\x63\x61\x6C"
    "\x68\x6F\x73\x74\x00\x90\x1F\x11\x00\x00\x00\x52\x6F"
    "\x6F\x74\x50\x4F\x41\x2F\x4F\x42\x4A\x45\x43\x54\x4B\x45\x59";
  std::vector<char> output;
  if(iiop::generate(output
                 , 
                 (
                  // giop::endianness
                  // [
                   giop::octet                      // IIOP major version
                   & giop::octet                    // IIOP minor version
                   & giop::string                   // host
                   & giop::ushort_                  // port
                   & giop::sequence[giop::octet]    // object key
                   // ]
                  )
                 , attribute))
  {
    std::cout << "Success" << std::endl;
    std::cout << " size " << output.size() << " should be " << sizeof(test_output)-1 << std::endl;
    assert(output.size() == (sizeof(test_output)-1) && std::equal(output.begin(), output.end(), &output[0]));
  }
  else
  {
    std::cout << "Failed" << std::endl;
    std::abort();
  }
}

