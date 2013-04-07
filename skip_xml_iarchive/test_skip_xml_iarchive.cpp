// (C) Copyright 2006 Todd Greer. tgreer <at> affinegy <dot> com
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt)

//Test skip_xml_iarchive.
//To make this test compile in your environment, you need to 
//#define TEST in such a way as to work with your test harness
//in your test framework, and ensure that skip_xml_iarchive.ipp
//is in your #include path.
//
//Other than that, this test should compile and run cleanly.

#include "skip_xml_iarchive.ipp"
#if defined(_MSC_VER)
# pragma warning(push)// Disable some optional warnings
# pragma warning(disable: 4100 4244 4267 4640)
#endif
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/impl/basic_xml_iarchive.ipp>
#include <boost/archive/impl/archive_pointer_iserializer.ipp>
#include <boost/archive/impl/xml_iarchive_impl.ipp>
#include <boost/serialization/vector.hpp>
#if defined(_MSC_VER)
# pragma warning( pop )
#endif

using namespace std;
using namespace boost::archive;
using boost::serialization::make_nvp;

namespace
{
	struct nested1
	{
		int a;
		int b;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
		{ 
			ar & BOOST_SERIALIZATION_NVP(a);
			ar & BOOST_SERIALIZATION_NVP(b); 
		}
	};

	struct nested2
	{
		int extra1;
		int a;
		int extra2;
		int b;
		int extra3;
		template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
		{ 
			ar & BOOST_SERIALIZATION_NVP(extra1); 
			ar & BOOST_SERIALIZATION_NVP(a); 
			ar & BOOST_SERIALIZATION_NVP(extra2); 
			ar & BOOST_SERIALIZATION_NVP(b); 
			ar & BOOST_SERIALIZATION_NVP(extra3);
		}
	};

	struct test1
	{
		string c;
		vector<nested1> d;
		int e;
		template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
		{ 
			ar & BOOST_SERIALIZATION_NVP(c);
			ar & BOOST_SERIALIZATION_NVP(d); 
			ar & BOOST_SERIALIZATION_NVP(e); 
		}
	};

	struct test2
	{
		vector<int> extra4;
		string c;
		double extra5;
		vector<nested2> d;
		string extra6;
		int e;
		int extra7;
		template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
		{ 
			ar & BOOST_SERIALIZATION_NVP(extra4); 
			ar & BOOST_SERIALIZATION_NVP(c); 
			ar & BOOST_SERIALIZATION_NVP(extra5); 
			ar & BOOST_SERIALIZATION_NVP(d); 
			ar & BOOST_SERIALIZATION_NVP(extra6); 
			ar & BOOST_SERIALIZATION_NVP(e); 
			ar & BOOST_SERIALIZATION_NVP(extra7); 
		}
	};
}

TEST(test_skip_xml_iarchive)
{
	nested2 const n2 = { 1, 2, 3, 4, 5 };
	test2 const t2 = { vector<int>(3), "A", 42.0, vector<nested2>(1, n2), "extra", 42, 52 };
	
	stringstream stream;
	{
		xml_oarchive out(stream);
		out << make_nvp("t1", t2);
	}

	skip_xml_iarchive in(stream);
	test1 t1;
	in >> make_nvp("t1", t1);
	BOOST_REQUIRE_EQUAL(t1.c, t2.c);
	BOOST_REQUIRE_EQUAL(t1.d.size(), t2.d.size());
	BOOST_REQUIRE_EQUAL(t1.d.front().a, t2.d.front().a);
	BOOST_REQUIRE_EQUAL(t1.d.front().b, t2.d.front().b);
	BOOST_REQUIRE_EQUAL(t1.e, t2.e);
}
