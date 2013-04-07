#ifndef BOOST_SERIALIZATION_TUPLE_HPP
#define BOOST_SERIALIZATION_TUPLE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// serialization/utility.hpp:
// serialization for stl utility templates

// (C) Copyright 2006 - Christian Henning
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


namespace boost { 
namespace serialization {

// double
template<class Archive, class FIRST, class SECOND>
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , t.get<0>()  );
   ar & boost::serialization::make_nvp("second", t.get<1>()  );
}

// triple
template<class Archive, class FIRST, class SECOND, class THIRD>
inline void serialize( Archive & ar
                     , boost::tuple<FIRST, SECOND, THIRD>& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , t.get<0>()  );
   ar & boost::serialization::make_nvp("second", t.get<1>()  );
   ar & boost::serialization::make_nvp("third" , t.get<2>()  );
}


// quadruple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH 
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first" , t.get<0>()  );
   ar & boost::serialization::make_nvp("second", t.get<1>()  );
   ar & boost::serialization::make_nvp("third" , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth", t.get<3>()  );
}

//quintuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
}

// sextuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
}

// septuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
}

// octet
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT 
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
   ar & boost::serialization::make_nvp("eighth"  , t.get<7>()  );
}

// 9-tuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT, class NINE
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT, NINE 
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
   ar & boost::serialization::make_nvp("eighth"  , t.get<7>()  );
   ar & boost::serialization::make_nvp("ninth"   , t.get<8>()  );
}

// 10-tuple
template< class Archive, class FIRST, class SECOND, class THIRD, class FOURTH
        , class FIFTH, class SIXTH, class SEVENTH, class EIGHT, class NINE, class TEN
        >
inline void serialize( Archive & ar
                     , boost::tuple< FIRST, SECOND, THIRD, FOURTH
                                   , FIFTH, SIXTH, SEVENTH, EIGHT
                                   , NINE, TEN
                                   >& t
                     , const unsigned int /* file_version */
)
{
   ar & boost::serialization::make_nvp("first"   , t.get<0>()  );
   ar & boost::serialization::make_nvp("second"  , t.get<1>()  );
   ar & boost::serialization::make_nvp("third"   , t.get<2>()  );
   ar & boost::serialization::make_nvp("fourth"  , t.get<3>()  );
   ar & boost::serialization::make_nvp("fifth"   , t.get<4>()  );
   ar & boost::serialization::make_nvp("sixth"   , t.get<5>()  );
   ar & boost::serialization::make_nvp("seventh" , t.get<6>()  );
   ar & boost::serialization::make_nvp("eighth"  , t.get<7>()  );
   ar & boost::serialization::make_nvp("ninth"   , t.get<8>()  );
   ar & boost::serialization::make_nvp("tenth"   , t.get<9>()  );
}

} // serialization
} // boost


#endif // BOOST_SERIALIZATION_TUPLE_HPP
