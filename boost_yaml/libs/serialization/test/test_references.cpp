//  (C) Copyright Gennadiy Rozental 2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

// Boost.Test

#define BOOST_TEST_MAIN "YAML archive test - references"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <boost/archive/yaml_oarchive.hpp>
#include <boost/archive/yaml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <fstream>

struct TestSimple {
    int a;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(a);
    }

    TestSimple(int a_): a(a_) { };
    TestSimple() { };
};

struct TestReferences {
    TestSimple* ref1;
    TestSimple* ref2;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(ref1);
        ar & BOOST_SERIALIZATION_NVP(ref2);
    }

    TestReferences(TestSimple* ref1_, TestSimple* ref2_) : ref1(ref1_), ref2(ref2_) { };
    TestReferences() { };
};

BOOST_AUTO_TEST_CASE( test_references )
{
    TestSimple s(123);
    TestReferences x(&s, &s);
    TestReferences test;
    const char *path = "references.yaml";

    {
        std::ofstream ofs(path);
        boost::archive::yaml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(x);
    }

    {
        std::ifstream ifs(path);
        boost::archive::yaml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(test);
    }

    BOOST_CHECK_EQUAL( x.ref1->x, test.ref1->x );
    BOOST_CHECK_EQUAL( x.ref2->x, test.ref2->x );
    BOOST_CHECK_EQUAL( test.ref1, test.ref2 );
}
