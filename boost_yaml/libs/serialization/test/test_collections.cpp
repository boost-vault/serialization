//  (C) Copyright Gennadiy Rozental 2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

// Boost.Test

#define BOOST_TEST_MAIN "YAML archive test - collections"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <boost/archive/yaml_oarchive.hpp>
#include <boost/archive/yaml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <fstream>
#include <vector>
#include <boost/serialization/vector.hpp>
#include <list>
#include <boost/serialization/list.hpp>

struct TestVector {
    std::vector<int> *v;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(v);
    }

    TestVector(std::vector<int> *v_) : v(v_) { };
    TestVector() { };
};

struct TestList {
    std::list<int> *l;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int) {
        ar & BOOST_SERIALIZATION_NVP(l);
    }

    TestList(std::list<int> *l_) : l(l_) { };
    TestList() { };
};

BOOST_AUTO_TEST_CASE( test_vector )
{
    std::vector<int> v;
    v.push_back(1);

    TestVector x(&v);
    TestVector test;
    const char *path = "collections_vector.yaml";

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

    BOOST_CHECK_EQUAL( x.v->size(), test.v->size() );
    BOOST_CHECK_EQUAL( x.v->at(0), test.v->at(0) );
}

BOOST_AUTO_TEST_CASE( test_list )
{
    std::list<int> l;
    l.push_back(1);

    TestVector x(&l);
    TestVector test;
    const char *path = "collections_list.yaml";

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

    BOOST_CHECK_EQUAL( x.v->size(), test.v->size() );
    BOOST_CHECK_EQUAL( x.v->front(), test.v->front() );
}
