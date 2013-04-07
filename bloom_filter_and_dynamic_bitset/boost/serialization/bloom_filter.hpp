/*!
 * \file      dynamic_bitset.hpp
 * \brief     Provides Boost.Serialization support for [static_]bloom_filter
 * \author    Paul Fee
 * \date      08.01.2010
 * \copyright 2010 Paul Fee
 * \license   Boost Software License 1.0
 */

#ifndef BOOST_SERIALIZATION_BLOOM_FILTER_HPP
#define BOOST_SERIALIZATION_BLOOM_FILTER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/bloom_filter.hpp>
#include <boost/serialization/dynamic_bitset.hpp>
#include <boost/serialization/bitset.hpp>

namespace boost{
namespace serialization{

template <class Archive, typename Input, typename HashFunctions,
          typename Block, typename Allocator>
inline void serialize(
    Archive & ar,
    bloom_filter<Input, HashFunctions, Block, Allocator>& t,
    const unsigned int version)
{
    ar & t.bit_set;
}

template<class Archive, typename Input, size_t M, typename HashFunctions>
inline void serialize(
    Archive & ar,
    static_bloom_filter<Input, M, HashFunctions>& t,
    const unsigned int version)
{
    ar & t.bit_set;
}

} //serialization
} //boost

#endif // BOOST_SERIALIZATION_BITSET_HPP
