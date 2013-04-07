//  (C) Copyright Gennadiy Rozental 2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

// Boost.Test

#define BOOST_TEST_MAIN "YAML archive test - primitives"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <boost/archive/yaml_oarchive.hpp>
#include <boost/archive/yaml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <fstream>

BOOST_AUTO_TEST_CASE( test_int )
{
    int x = 0;
    int test;
    const char *path = "primitive_int.yaml";

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

    BOOST_CHECK_EQUAL( x, test );
}

BOOST_AUTO_TEST_CASE( test_char )
{
    char x = 'a';
    char test;
    const char *path = "primitive_char.yaml";

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

    BOOST_CHECK_EQUAL( x, test );
}

BOOST_AUTO_TEST_CASE( test_float )
{
    float x = 1.2;
    float test;
    const char *path = "primitive_float.yaml";

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

    BOOST_CHECK_EQUAL( x, test );
}

BOOST_AUTO_TEST_CASE( test_double )
{
    double x = 3.4;
    double test;
    const char *path = "primitive_double.yaml";

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

    BOOST_CHECK_EQUAL( x, test );
}

