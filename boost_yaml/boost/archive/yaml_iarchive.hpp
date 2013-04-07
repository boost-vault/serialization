#ifndef BOOST_ARCHIVE_YAML_IARCHIVE_HPP
#define BOOST_ARCHIVE_YAML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// yaml_iarchive.hpp

// (C) Copyright 2008 Esteve Fernandez <esteve.fernandez@gmail.com> 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>

//#include <boost/scoped_ptr.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_yaml_iarchive.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost { 
namespace archive {

template<class CharType>
class basic_yaml_grammar;
typedef basic_yaml_grammar<char> yaml_grammar;

template<class Archive>
class yaml_iarchive_impl : 
    public basic_text_iprimitive<std::istream>,
    public basic_yaml_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class detail::interface_iarchive<Archive>;
    friend class basic_yaml_iarchive<Archive>;
    friend class load_access;
protected:
#endif
    // instances of micro yaml parser to parse start preambles
    // scoped_ptr doesn't play nice with borland - so use a naked pointer
    // scoped_ptr<yaml_grammar> gimpl;
    yaml_grammar *gimpl;

    std::istream & get_is(){
        return is;
    }
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
    }
    BOOST_ARCHIVE_DECL(void)
    load(char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL(void)
    load(wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL(void)
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL(void)
    load(std::wstring &ws);
    #endif
    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        basic_yaml_iarchive<Archive>::load_override(t, 0);
    }
    BOOST_ARCHIVE_DECL(void)
    load_override(class_name_type & t, int);
    BOOST_ARCHIVE_DECL(void)
    init();
    BOOST_ARCHIVE_DECL(BOOST_PP_EMPTY()) 
    yaml_iarchive_impl(std::istream & is, unsigned int flags);
    BOOST_ARCHIVE_DECL(BOOST_PP_EMPTY())
    ~yaml_iarchive_impl();
};

// we use the following because we can't use
// typedef yaml_iarchive_impl<yaml_iarchive_impl<...> > yaml_iarchive;

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from yaml_iarchive_impl instead.  This will
// preserve correct static polymorphism.
class yaml_iarchive : 
    public yaml_iarchive_impl<yaml_iarchive>
{
public:
    yaml_iarchive(std::istream & is, unsigned int flags = 0) :
        yaml_iarchive_impl<yaml_iarchive>(is, flags)
    {}
    ~yaml_iarchive(){};
};

} // namespace archive
} // namespace boost

// required by smart_cast for compilers not implementing 
// partial template specialization
BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(boost::archive::yaml_iarchive)

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#define BOOST_ARCHIVE_CUSTOM_IARCHIVE_TYPES boost::archive::yaml_oarchive

#endif // BOOST_ARCHIVE_YAML_IARCHIVE_HPP
