#ifndef BOOST_SERIALIZATION_CNV_HPP
#define BOOST_SERIALIZATION_CNV_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// cnv.hpp: interface for serialization system.

// (C) Copyright 2008 Esteve Fernandez <esteve.fernandez@gmail.com> 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/tuple/tuple.hpp>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
// supress noise
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1200)
# pragma warning (disable : 4786) // too long name, harmless warning
#endif

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/traits.hpp>

namespace boost {
namespace serialization {

template<class T>
struct cnv : 
    public boost::tuple<const char*, const char *, T *>,
    public traits<cnv<T>, object_serializable, track_never>
{
    explicit cnv(const char * cname, const char * name, T & t) :
        // note: redundant cast works around borland issue
        boost::tuple<const char *, const char *, T *>(cname, name, (T*)(& t))
    {}
    cnv(const cnv & rhs) : 
        // note: redundant cast works around borland issue
        boost::tuple<const char *, const char *, T *>(rhs.get<0>(), rhs.get<1>(), (T*)rhs.get<2>())
    {}

    const char * cname() const {
        return this->get<0>();
    }
    const char * name() const {
        return this->get<1>();
    }
    T & value() const {
        return *(this->get<2>());
    }

    const T & const_value() const {
        return *(this->get<2>());
    }

    // True64 compiler complains with a warning about the use of
    // the name "Archive" hiding some higher level usage.  I'm sure this
    // is an error but I want to accomodated as it generates a long warning
    // listing and might be related to a lot of test failures.
    // default treatment for name-value pairs. The name is
    // just discarded and only the value is serialized. 
    template<class Archivex>
    void save(
        Archivex & ar, 
        const unsigned int /* file_version */
    ) const {
        // CodeWarrior 8.x can't seem to resolve the << op for a rhs of "const T *"
        ar.operator<<(const_value());
    }
    template<class Archivex>
    void load(
        Archivex & ar, 
        const unsigned int /* file_version */
    ){
        // CodeWarrior 8.x can't seem to resolve the >> op for a rhs of "const T *"
        ar.operator>>(value());
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

template<class T>
struct cnv_type : 
    public boost::tuple<const char*, const char *, T *>,
    public traits<cnv_type<T>, object_serializable, track_never>
{
    explicit cnv_type(const char * cname, const char * name, T & t) :
        // note: redundant cast works around borland issue
        boost::tuple<const char *, const char *, T *>(cname, name, (T*)(& t))
    {}
    cnv_type(const cnv_type & rhs) : 
        // note: redundant cast works around borland issue
        boost::tuple<const char *, const char *, T *>(rhs.get<0>(), rhs.get<1>(), (T*)rhs.get<2>())
    {}

    const char * cname() const {
        return this->get<0>();
    }
    const char * name() const {
        return this->get<1>();
    }
    T & value() const {
        return *(this->get<2>());
    }

    const T & const_value() const {
        return *(this->get<2>());
    }

    // True64 compiler complains with a warning about the use of
    // the name "Archive" hiding some higher level usage.  I'm sure this
    // is an error but I want to accomodated as it generates a long warning
    // listing and might be related to a lot of test failures.
    // default treatment for name-value pairs. The name is
    // just discarded and only the value is serialized. 
    template<class Archivex>
    void save(
        Archivex & ar, 
        const unsigned int /* file_version */
    ) const {
        // CodeWarrior 8.x can't seem to resolve the << op for a rhs of "const T *"
        ar.operator<<(const_value());
    }
    template<class Archivex>
    void load(
        Archivex & ar, 
        const unsigned int /* file_version */
    ){
        // CodeWarrior 8.x can't seem to resolve the >> op for a rhs of "const T *"
        ar.operator>>(value());
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
cnv<T> make_cnv(const char * cname, const char * name, T & t){
    return cnv<T>(cname, name, t);
}

template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
cnv_type<T> make_cnv_type(const char * cname, const char * name, T & t){
    return cnv_type<T>(cname, name, t);
}

// to maintain efficiency and portability, we want to assign
// specific serialization traits to all instances of this wrappers.
// we can't strait forward method below as it depends upon
// Partial Template Specialization and doing so would mean that wrappers
// wouldn't be treated the same on different platforms.  This would
// break archive portability. Leave this here as reminder not to use it !!!
#if 0 // #ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template <class T>
struct implementation_level<cnv<T> >
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level::type::value);
};

// cnv objects are generally created on the stack and are never tracked
template<class T>
struct tracking_level<cnv<T> >
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
};

#endif

} // seralization
} // boost

#include <boost/preprocessor/stringize.hpp>

#define BOOST_SERIALIZATION_CNV(cname, name)                       \
    boost::serialization::make_cnv(                                \
    BOOST_PP_STRINGIZE(cname),                                     \
    BOOST_PP_STRINGIZE(name),                                      \
    name)
/**/

#define BOOST_SERIALIZATION_BASE_OBJECT_CNV(name)                  \
    boost::serialization::make_cnv_type(                           \
        BOOST_PP_STRINGIZE(name),                                  \
        BOOST_PP_STRINGIZE(name),                                  \
        boost::serialization::base_object<name >(*this)            \
    )
/**/

#endif // BOOST_SERIALIZATION_CNV_HPP
