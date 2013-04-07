/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// yaml_oarchive.cpp:

// (C) Copyright 2008 Esteve Fernandez <esteve.fernandez@gmail.com> 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#if (defined _MSC_VER) && (_MSC_VER == 1200)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/yaml_oarchive.hpp>

#include <boost/archive/impl/basic_yaml_oarchive.ipp>
#include <boost/archive/impl/archive_pointer_oserializer.ipp>
#include <boost/archive/impl/yaml_oarchive_impl.ipp>

namespace boost {
namespace archive {

// explicitly instantiate for this type of yaml stream
template class basic_yaml_oarchive<yaml_oarchive> ;
template class detail::archive_pointer_oserializer<yaml_oarchive> ;
template class yaml_oarchive_impl<yaml_oarchive> ;

} // namespace archive
} // namespace boost
