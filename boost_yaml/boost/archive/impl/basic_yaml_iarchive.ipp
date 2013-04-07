/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_yaml_iarchive.ipp:

// (C) Copyright 2008 Esteve Fernandez <esteve.fernandez@gmail.com> 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cassert>
#include <algorithm>

#include <boost/throw_exception.hpp>

#include <boost/archive/basic_yaml_iarchive.hpp>
#include <boost/serialization/tracking.hpp>
//#include <boost/serialization/extended_type_info.hpp>

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// implementation of yaml_text_archive

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_iarchive<Archive>::load_start(const char *name){
    // if there's no name
    if(NULL == name)
        return;

    bool result = this->This()->gimpl->parse_start_tag(this->This()->get_is());
    if(true != result){
        boost::throw_exception(
            archive_exception(archive_exception::stream_error)
        );
    }
    // don't check start tag at highest level
    ++depth;
    return;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_iarchive<Archive>::load_end(const char *name){
    // if there's no name
    if(NULL == name)
        return;

    this->This()->gimpl->parse_end_tag(this->This()->get_is());

    // don't check start tag at highest level
    if(0 == --depth)
        return;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_iarchive<Archive>::load_override(object_id_type & t, int){
    t = this->This()->gimpl->rv.object_id;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_iarchive<Archive>::load_override(version_type & t, int){
    t = this->This()->gimpl->rv.version;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_iarchive<Archive>::load_override(class_id_type & t, int){
    t = this->This()->gimpl->rv.class_id;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_iarchive<Archive>::load_override(tracking_type & t, int){
    t = this->This()->gimpl->rv.tracking_level;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
basic_yaml_iarchive<Archive>::basic_yaml_iarchive(unsigned int flags) :
    detail::common_iarchive<Archive>(flags),
    depth(0)
{}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
basic_yaml_iarchive<Archive>::~basic_yaml_iarchive(){}

} // namespace archive
} // namespace boost
