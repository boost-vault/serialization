//  (C) Copyright Gennadiy Rozental 2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

// Boost.Test

#define BOOST_TEST_MAIN "YAML archive test - classes"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <boost/archive/yaml_oarchive.hpp>
#include <boost/archive/yaml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <fstream>

struct TestPrimitives {
    int a;
    char b;
    float c;
    double d;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(a);
        ar & BOOST_SERIALIZATION_NVP(b);
        ar & BOOST_SERIALIZATION_NVP(c);
        ar & BOOST_SERIALIZATION_NVP(d);
    }

    TestPrimitives(int a_, char b_, float c_, double d_): a(a_), b(b_), c(c_), d(d_) { };
    TestPrimitives() { };
};

struct TestContainer {
    TestPrimitives* inner;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(a);
        ar & BOOST_SERIALIZATION_NVP(b);
        ar & BOOST_SERIALIZATION_NVP(c);
        ar & BOOST_SERIALIZATION_NVP(d);
    }

    TestContainer(TestPrimitives* inner_): inner(inner_) { };
    TestContainer() { };
};

BOOST_AUTO_TEST_CASE( test_primitives )
{
    TestPrimitives x(1, 'a', 1.2, 3.4);
    TestPrimitives test;
    const char *path = "class_primitives.yaml";

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

    BOOST_CHECK_EQUAL( x.a, test.a );
    BOOST_CHECK_EQUAL( x.b, test.b );
    BOOST_CHECK_EQUAL( x.c, test.c );
    BOOST_CHECK_EQUAL( x.d, test.d );
}

BOOST_AUTO_TEST_CASE( test_container )
{
    TestPrimitives inner(1, 'a', 1.2, 3.4);

    TestContainer x(&inner);
    TestContainer test;
    const char *path = "class_container.yaml";

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

    BOOST_CHECK_EQUAL( x.inner->a, test.inner->a );
    BOOST_CHECK_EQUAL( x.inner->b, test.inner->b );
    BOOST_CHECK_EQUAL( x.inner->c, test.inner->c );
    BOOST_CHECK_EQUAL( x.inner->d, test.inner->d );
}

BOOST_AUTO_TEST_CASE( test_mixed )
{
    TestPrimitives inner(1, 'a', 1.2, 3.4);

    TestMixed x(42, &inner);
    TestMixed test;
    const char *path = "class_container.yaml";

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

    BOOST_CHECK_EQUAL( x.inner->a, test.inner->a );
    BOOST_CHECK_EQUAL( x.inner->b, test.inner->b );
    BOOST_CHECK_EQUAL( x.inner->c, test.inner->c );
    BOOST_CHECK_EQUAL( x.inner->d, test.inner->d );
}

