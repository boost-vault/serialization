/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_yaml_oarchive.ipp:

// (C) Copyright 2008 Esteve Fernandez <esteve.fernandez@gmail.com>
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <algorithm>
#include <cstring>

#if defined(BOOST_NO_STDC_NAMESPACE) && ! defined(__LIBCOMO__)
namespace std{
    using ::strlen;
} // namespace std
#endif

#include <boost/archive/basic_yaml_archive.hpp>
#include <boost/archive/basic_yaml_oarchive.hpp>
#include <boost/detail/no_exceptions_support.hpp>

#include <boost/algorithm/string.hpp>

namespace boost {
namespace archive {

namespace detail {
template<class CharType>
struct YAML_name {
    void operator()(CharType t) const{
        const unsigned char lookup_table[] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0, // -.
            1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0, // 0-9
            0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // A-
            1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1, // -Z _
            0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // a-
            1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0, // -z
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        };
        if((unsigned)t > 127)
            return;
        if(0 == lookup_table[(unsigned)t])
            boost::throw_exception(
                yaml_archive_exception(
                    yaml_archive_exception::yaml_archive_tag_name_error
                )
            );
    }
};

} // namespace detail

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// implemenations of functions common to both types of yaml output

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::write_attribute(
    const char *attribute_name,
    int t,
    const char *conjunction
){
    this->This()->put(' ');
    this->This()->put(attribute_name);
    this->This()->put(conjunction);
    this->This()->save(t);
    this->This()->put('"');
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::write_attribute(
    const char *attribute_name,
    const char *key
){
    this->This()->put(' ');
    this->This()->put(attribute_name);
    this->This()->put("=\"");
    this->This()->put(key);
    this->This()->put('"');
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::indent(){
    int i;
    for(i = depth; i-- > 1;)
        this->This()->put("  ");
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_start(const char *name)
{
    if(NULL == name)
        return;

    // be sure name has no invalid characters
    std::for_each(name, name + std::strlen(name), detail::YAML_name<const char>());

    end_preamble();
    if(depth > 0){
        this->This()->put('\n');
        if (depth > 1) {
            indent();
        }
        if (!hierarchy_stack.empty()) {
            this->This()->save("_");
            this->This()->save(hierarchy_stack.top());
            this->This()->save("__");
        }
        this->This()->save(name);
        this->This()->put(": ");
    }
    ++depth;
    pending_preamble = true;
    indent_next = false;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_start(const char *cname, const char *name)
{
    if(NULL == cname || NULL == name)
        return;

    // be sure name has no invalid characters
    std::for_each(name, name + std::strlen(name), detail::YAML_name<const char>());
    std::for_each(cname, cname + std::strlen(cname), detail::YAML_name<const char>());

    end_preamble();

    preamble[CLASS_NAME()] = cname;

    if(depth > 0){
        this->This()->put('\n');
        if (depth > 1) {
            indent();
        }
        if (!hierarchy_stack.empty() && class_stack.top() == hierarchy_stack.top()) {
            this->This()->save("_");
            this->This()->save(hierarchy_stack.top());
            this->This()->save("__");
        }
        this->This()->save(name);
        this->This()->put(": ");
    }
    class_stack.push(cname);

    ++depth;
    pending_preamble = true;
    indent_next = false;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_start_type(const char *cname, const char *name)
{
    if(NULL == cname || NULL == name)
        return;

    // be sure name has no invalid characters
    std::for_each(name, name + std::strlen(name), detail::YAML_name<const char>());
    std::for_each(cname, cname + std::strlen(cname), detail::YAML_name<const char>());

    hierarchy_stack.push(cname);
    class_stack.push(cname);
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_end(const char *name)
{
    if(NULL == name)
        return;

    // be sure name has no invalid characters
    std::for_each(name, name + std::strlen(name), detail::YAML_name<const char>());

    end_preamble();
    --depth;
    if(indent_next){
        indent();
    }
    indent_next = true;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_end(const char *cname, const char *name)
{
    if(NULL == cname || NULL == name)
        return;

    // be sure name has no invalid characters
    std::for_each(name, name + std::strlen(name), detail::YAML_name<const char>());
    std::for_each(cname, cname + std::strlen(cname), detail::YAML_name<const char>());

    if(!class_stack.empty()) {
        class_stack.pop();
    }

    end_preamble();
    --depth;
    if(indent_next){
        indent();
    }
    indent_next = true;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_end_type(const char *cname, const char *name)
{
    if (!hierarchy_stack.empty()) {
        hierarchy_stack.pop();
    }
    if (!class_stack.empty()) {
        class_stack.pop();
    }
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::end_preamble(){
    if(pending_preamble){
        if (!preamble[OBJECT_ID()].empty()) {
            this->This()->put(preamble[OBJECT_ID()].c_str());
            this->This()->put(' ');
        }
        if (!preamble[OBJECT_REFERENCE()].empty()) {
            this->This()->put(preamble[OBJECT_REFERENCE()].c_str());
            this->This()->put(' ');
        }
        if (!preamble[CLASS_NAME()].empty()) {
                this->This()->put("!!boost/object:");
                this->This()->put(preamble[CLASS_NAME()].c_str());
                if(!preamble[TRACKING()].empty()) {
                    this->This()->put(":");
                    this->This()->put(preamble[TRACKING()].c_str());
                }
                if(!preamble[VERSION()].empty()) {
                    this->This()->put(":");
                    this->This()->put(preamble[VERSION()].c_str());
                }
        }
        preamble.clear();
        pending_preamble = false;
    }
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(const object_id_type & t, int)
{
    if (depth > 1) {
    int i = t.t; // extra .t is for borland
    std::ostringstream oss;
    oss << "&id" << i;
    preamble[OBJECT_ID()] = oss.str();
    }
}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(
    const object_reference_type & t,
    int
){
    int i = t.t; // extra .t is for borland
    std::ostringstream oss;
    oss << "*id" << i;
    preamble[OBJECT_REFERENCE()] = oss.str();
}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(const version_type & t, int)
{
    int i = t.t; // extra .t is for borland
    std::ostringstream oss;
    oss << "version:" << i;
    preamble[VERSION()] = oss.str();
}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(const class_id_type & t, int)
{
    if (preamble[CLASS_NAME()].empty()) {
        std::ostringstream oss;
        oss << "class_id" << t;
        preamble[CLASS_NAME()] = oss.str();
    }
}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(
    const class_id_reference_type & t,
    int
){
    int i = t.t; // extra .t is for borland
    std::ostringstream oss;
    oss << "class_id_reference:" << i;
    preamble[CLASS_ID_REFERENCE()] = oss.str();
}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(
    const class_id_optional_type & t,
    int
){
    if (preamble[CLASS_NAME()].empty()) {
        std::ostringstream oss;
        oss << "class_id" << t;
        preamble[CLASS_NAME()] = oss.str();
    }
}
template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(const class_name_type & t, int)
{
    const char * key = t;
    if(NULL == key)
        return;
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::save_override(const tracking_type & t, int)
{
    int i = t.t; // extra .t is for borland
    std::ostringstream oss;
    oss << "tracking:" << i;
    preamble[TRACKING()] = oss.str();
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
basic_yaml_oarchive<Archive>::init(){
    this->This()->put("#boost_serialization");
    write_attribute("signature", ARCHIVE_SIGNATURE());
    write_attribute("version", ARCHIVE_VERSION());
    this->This()->put("\n");
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
basic_yaml_oarchive<Archive>::basic_yaml_oarchive(unsigned int flags) :
    detail::common_oarchive<Archive>(flags),
    depth(0),
    indent_next(false),
    pending_preamble(false)
{
}

template<class Archive>
BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY())
basic_yaml_oarchive<Archive>::~basic_yaml_oarchive(){
}

} // namespace archive
} // namespace boost
