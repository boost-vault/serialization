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
#include <string>

BOOST_AUTO_TEST_CASE( test_simple )
{
    std::string x("hello");
    std::string test;
    const char *path = "string_simple.yaml";

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

BOOST_AUTO_TEST_CASE( test_spaces )
{
    std::string x("hello world");
    std::string test;
    const char *path = "string_spaces.yaml";

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

BOOST_AUTO_TEST_CASE( test_alphanum )
{
    std::string x("hello world 1234");
    std::string test;
    const char *path = "string_alphanum.yaml";

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

BOOST_AUTO_TEST_CASE( test_nonalphanum )
{
    std::string x("hello world!#.");
    std::string test;
    const char *path = "string_nonalphanum.yaml";

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


