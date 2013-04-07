/*!
 * \file      dynamic_bitset.hpp
 * \brief     Provides Boost.Serialization support for boost::dynamic_bitset
 * \author    Paul Fee
 * \date      08.01.2010
 * \copyright 2010 Paul Fee
 * \license   Boost Software License 1.0
 */

#ifndef BOOST_SERIALIZATION_DYNAMIC_BITSET_HPP
#define BOOST_SERIALIZATION_DYNAMIC_BITSET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cstddef> // size_t

#include <boost/config.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/serialization/vector.hpp>

namespace boost{
namespace serialization{

template <class Archive, typename Block, typename Allocator>
inline void save(
    Archive & ar,
    boost::dynamic_bitset<Block, Allocator> const & t,
    const unsigned int /* version */
){
    // Serialize bitset size
    std::size_t size = t.size();
    ar << size;

    // Convert bitset into a vector
    std::vector<Block> vec(t.num_blocks());
    to_block_range(t, vec.begin());

    // Serialize vector
    ar & vec;
}

template <class Archive, typename Block, typename Allocator>
inline void load(
    Archive & ar,
    boost::dynamic_bitset<Block, Allocator> & t,
    const unsigned int /* version */
){
    std::size_t size;
    ar & size;

    t.resize(size);

    // Load vector
    std::vector<Block> vec;
    ar & vec;

    // Convert vector into a bitset
    from_block_range(vec.begin(), vec.end(), t);
}

template <class Archive, typename Block, typename Allocator>
inline void serialize(
    Archive & ar,
    boost::dynamic_bitset<Block, Allocator> & t,
    const unsigned int version
){
    boost::serialization::split_free( ar, t, version );
}

} //serialization
} //boost

#endif // BOOST_SERIALIZATION_BITSET_HPP