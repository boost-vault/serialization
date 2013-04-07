/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_yaml_grammar.ipp:

// (C) Copyright 2008 Esteve Fernandez <esteve.fernandez@gmail.com> 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#if (defined _MSC_VER) && (_MSC_VER == 1200)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

#include <istream>
#include <algorithm>
#include <boost/config.hpp> // BOOST_DEDUCED_TYPENAME

// spirit stuff
#include <boost/spirit/core/composite/operators.hpp>
#include <boost/spirit/core/composite/actions.hpp>
#include <boost/spirit/core/primitives/numerics.hpp>

// for head_iterator test
#include <boost/bind.hpp> 
#include <boost/function.hpp>
#include <boost/pfto.hpp>

#include <boost/io/ios_state.hpp>
#include <boost/throw_exception.hpp>
#include <boost/archive/impl/basic_yaml_grammar.hpp>
#include <boost/archive/basic_yaml_archive.hpp>
#include <boost/archive/iterators/xml_unescape.hpp>

using namespace boost::spirit;

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// template code for basic_yaml_grammar of both wchar_t and char types

namespace { // anonymous

template<class T>
struct assign_impl {
    T & t;
    void operator()(const T t_) const {
        t = t_;
    }
    assign_impl(T &  t_)
        : t(t_)
    {}
};

template<>
struct assign_impl<std::string> {
    std::string & t;
    void operator()(
        std::string::const_iterator b, 
        std::string::const_iterator e
    ) const {
        t.resize(0);
        while(b != e){
            t += * b;
            ++b;
        }
    }
    assign_impl(std::string & t_)
        : t(t_)
    {}
};

#ifndef BOOST_NO_STD_WSTRING
template<>
struct assign_impl<std::wstring> {
    std::wstring & t;
    void operator()(
        std::wstring::const_iterator b, 
        std::wstring::const_iterator e
    ) const {
        t.resize(0);
        while(b != e){
            t += * b;
            ++b;
        }
    }
    assign_impl(std::wstring & t_)
        : t(t_)
    {}
};
#endif

template<class T>
assign_impl<T> assign_object(T &t){
    return assign_impl<T>(t);
} 

struct assign_level {
    tracking_type & tracking_level;
    void operator()(const unsigned int tracking_level_) const {
        tracking_level = (0 == tracking_level_) ? false : true;
    }
    assign_level(tracking_type &  tracking_level_)
        : tracking_level(tracking_level_)
    {}
};

template<class String, class Iterator>
struct append_string {
    String & contents;
    void operator()(Iterator start, Iterator end) const {
    #if 0
        typedef boost::archive::iterators::xml_unescape<Iterator> translator;
        contents.append(
            translator(BOOST_MAKE_PFTO_WRAPPER(start)), 
            translator(BOOST_MAKE_PFTO_WRAPPER(end))
        );

    #endif
        contents.append(start, end);
    }
    append_string(String & contents_)
        : contents(contents_)
    {}
};

template<class String>
struct append_char {
    String & contents;
    void operator()(const unsigned int char_value) const {
        const typename String::value_type z = char_value;
        contents += z;
    }
    append_char(String & contents_)
        : contents(contents_)
    {}
};

template<class String, unsigned int c>
struct append_lit {
    String & contents;
    template<class X, class Y>
    void operator()(const X & /*x*/, const Y & /*y*/) const {
        const typename String::value_type z = c;
        contents += z;
    }
    append_lit(String & contents_)
        : contents(contents_)
    {}
};

} // namespace anonymous

template<class CharType>
bool basic_yaml_grammar<CharType>::my_parse(
    BOOST_DEDUCED_TYPENAME basic_yaml_grammar<CharType>::IStream & is,
    const rule_t & rule_,
    CharType delimiter
){
    if(is.fail()){
        boost::throw_exception(
            archive_exception(archive_exception::stream_error)
        );
    }
    
    boost::io::ios_flags_saver ifs(is);
    is >> std::noskipws;

    std::basic_string<CharType> arg;

    std::getline(is, arg, delimiter);

    // read just one more character.  This will be the newline after the tag
    // this is so that the next operation will return fail if the archive
    // is terminated.  This will permit the archive to be used for debug
    // and transaction data logging in the standard way.


    parse_info<BOOST_DEDUCED_TYPENAME std::basic_string<CharType>::iterator> result
        = boost::spirit::parse(arg.begin(), arg.end(), rule_);

    if (!rv.value.empty()) {
        for(int i=rv.value.size(); i>=0;i--) {
            is.putback(rv.value[i]);
        }
        rv.value.clear();
    }

    return result.hit;
}

template<class CharType>
bool basic_yaml_grammar<CharType>::parse_start_tag(
    BOOST_DEDUCED_TYPENAME basic_yaml_grammar<CharType>::IStream & is
) {
    if(is.fail()){
        boost::throw_exception(
            archive_exception(archive_exception::stream_error)
        );
    }
    rv.class_name.resize(0);
    return my_parse(is, STag);
}

template<class CharType>
void basic_yaml_grammar<CharType>::parse_end_tag(IStream & is) {
    if(is.fail()){
        boost::throw_exception(
            archive_exception(archive_exception::stream_error)
        );
    }

    if(!is.eof()) {
        CharType arg = is.get();
        if(!is.eof()) {
            if (arg != '\n' && arg != '\r') {
                is.putback(arg);
            }
        } else {
            is.clear();
        }
    } else{
        is.clear();
    }
}

template<class CharType>
bool basic_yaml_grammar<CharType>::parse_string(IStream & is, StringType & s) {
    if(is.fail()){
        boost::throw_exception(
            archive_exception(archive_exception::stream_error)
        );
    }
    rv.contents.resize(0);
    bool result = my_parse(is, content, '\n');
    // note: unget caused a problem with dinkumware.  replace with
 // is.unget();
    // putback another dilimiter instead
    //is.putback('\n');
    if(result) {
        std::getline(is, s);
    }
    return result;
}

template<class CharType>
basic_yaml_grammar<CharType>::basic_yaml_grammar(){
    init_chset();

    S =
        +(Sch)
    ;

    // refactoring to workaround template depth on darwin
    NameHead = (Letter | '_' | ':');
    NameTail = *NameChar ;
    Name =
      NameHead >> NameTail
    ;

    Eq =
        !S >> '=' >> !S
    ;

    VariableName = (Letter | '_') >> *(Letter | Digit | '_');

    ClassHeader =
        // >> CLASS_ID() Doesn't work, why?
        L"!!boost/object:class_id"
        >> int_p [assign_object(rv.class_id.t)]
        >> !(L":tracking:"
        >> uint_p [assign_level(rv.tracking_level)]
        >> L":version:"
        >> uint_p [assign_object(rv.version.t)])
    ;

    Value =
        (+(anychar_p - '\n'))[assign_object(rv.value)]
    ;

    content =
        Value
    ;

    VariableNameHeader =
        VariableName  [assign_object(rv.object_name)]
        >> ":"
    ;

    ObjectID =
        L"&id"
        >> uint_p [assign_object(rv.object_id.t)]
    ;
   
    ObjectReference =
        L"*id"
        >> uint_p [assign_object(rv.object_id.t)]
    ;
 
    STag =
        (ClassHeader
        | !S >> VariableNameHeader >> S >> ObjectID >> S >> ClassHeader
        | !S >> VariableNameHeader >> S >> Value
        | !S >> VariableNameHeader >> S >> ObjectReference
        | Value)
    ;

    ETag =
        !S
    ;

    VersionAttribute = 
        str_p(VERSION())
        >> Eq
        >> L'"'
        >> uint_p [assign_object(rv.version.t)]
        >> L'"'
    ;

    SignatureAttribute = 
        str_p(L"signature") 
        >> Eq 
        >> L'"'
        >> Name [assign_object(rv.class_name)]
        >> L'"'
    ;
    
    SerializationWrapper =
        !S
        >> L"#boost_serialization"
        >> S
        >> SignatureAttribute
        >> S
        >> VersionAttribute
    ;
}

template<class CharType>
void basic_yaml_grammar<CharType>::init(IStream & is){
    init_chset();
    if(! my_parse(is, SerializationWrapper))
        boost::throw_exception(
            yaml_archive_exception(yaml_archive_exception::yaml_archive_parsing_error)
        );
    if(! std::equal(rv.class_name.begin(), rv.class_name.end(), ARCHIVE_SIGNATURE()))
        boost::throw_exception(
            archive_exception(archive_exception::invalid_signature)
        );
}

template<class CharType>
void basic_yaml_grammar<CharType>::windup(IStream & is){
}

} // namespace archive
} // namespace boost
