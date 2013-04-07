#ifndef  BOOST_SERIALIZATION_BITSET_HPP
#define BOOST_SERIALIZATION_BITSET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// bitset.hpp: serialization for stl bitset templates

// Written by Steven F. McKay, based on vector.hpp:
// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <bitset>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/serialization/split_free.hpp>

// function specializations must be defined in the appropriate
// namespace - boost::serialization
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD std
#endif

namespace boost { 
namespace serialization {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// bitset<Bits>
template<class Archive, size_t Bits>
inline void save(
    Archive & ar,
    const STD::bitset<Bits> &t,
    const unsigned int /* file_version */
){
    if (ar.get_flags() & boost::archive::packed_bools) {
        const unsigned Bytes = Bits / 8;
        // handle full bytes
        for (unsigned int i = 0; i < Bytes; i++){
            const unsigned int count = 8 * i;
            // start with the highest bit
            unsigned char theByte = t[count + 7];
            for (int j = 6; j >= 0; j--) {
                theByte = (theByte << 1) + t[count + j];
            }
            ar << boost::serialization::make_nvp("item", theByte);
        }
        // handle any partial byte
        const unsigned extraBits = Bits - 8 * Bytes;
        if (extraBits > 0) {
            const unsigned int count = 8 * Bytes;
            // start with the highest bit
            unsigned char theByte = t[count + extraBits - 1];
            for (int j = extraBits - 2; j >= 0; j--) {
                theByte = (theByte << 1) + t[count + j];
            }
            ar << boost::serialization::make_nvp("item", theByte);
        }
    }
    else {
        for (unsigned int i = 0; i < Bits; i++){
            bool tb = t[i];
            ar << boost::serialization::make_nvp("item", tb);
        }
    }
}

template<class Archive, size_t Bits>
inline void load(
    Archive & ar,
    STD::bitset<Bits> &t,
    const unsigned int /* file_version */
){
    if (ar.get_flags() & boost::archive::packed_bools) {
        const unsigned Bytes = Bits / 8;
        for (unsigned int i = 0; i < Bytes; i++){
            unsigned char theByte;
            ar >> boost::serialization::make_nvp("item", theByte);
            const unsigned int count = 8 * i;
            t.set(count, theByte & 0x01);
            for (unsigned int j = 1; j < 8; j++) {
                theByte = theByte >> 1;
                t.set(count + j, theByte & 0x01);
            }
        }
        // handle any partial byte
        const unsigned extraBits = Bits - 8 * Bytes;
        if (extraBits > 0) {
            unsigned char theByte;
            ar >> boost::serialization::make_nvp("item", theByte);
            const unsigned int count = 8 * Bytes;
            t.set(count, theByte & 0x01);
            for (unsigned int j = 1; j < extraBits; j++) {
                theByte = theByte >> 1;
                t.set(count + j, theByte & 0x01);
            }
        }
    }
    else {
        for (unsigned int i = 0; i < Bits; i++){
            bool tb;
            ar >> boost::serialization::make_nvp("item", tb);
            t.set(i, tb);
        }
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, size_t Bits>
inline void serialize(
    Archive & ar,
    STD::bitset<Bits> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace boost

#undef STD

#endif // BOOST_SERIALIZATION_BITSET_HPP
