/*!
 * \file      test_bitset.cpp
 * \brief     Test that serialization of std::bitset works.
 * \note      Should pass compilation and execution
 * \author    Brian Ravnsgaard Riis
 * \date      16.09.2004
 * \license   Boost Software License 1.0
 */
#include <fstream>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
  using ::remove;
}
#endif

#include "test_tools.hpp"

#include <boost/serialization/bitset.hpp>

int test_main(int /* argc */, char * /* argv */ [])
{
  const char * testfile = boost::archive::tmpnam(NULL);
  BOOST_REQUIRE(NULL != testfile);

  // Make a bitset of some values...
  std::bitset<8> abitset;
  abitset.set(0, false);
  abitset.set(1, true);
  abitset.set(2, false);
  abitset.set(3, true);
  abitset.set(4, false);
  abitset.set(5, false);
  abitset.set(6, true);
  abitset.set(7, true);
  {
    test_ostream os(testfile, TEST_STREAM_FLAGS);
    test_oarchive oa(os);
    oa << boost::serialization::make_nvp("abitset", abitset);
  }
  std::bitset<8> abitset1;
  {
    test_istream is(testfile, TEST_STREAM_FLAGS);
    test_iarchive ia(is);
    ia >> boost::serialization::make_nvp("abitset", abitset1);
  }
  BOOST_CHECK(abitset1 == abitset);
  std::remove(testfile);
  return boost::exit_success;
}

