// (C) Copyright 2006 Todd Greer. tgreer <at> affinegy <dot> com
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt)

// Some code snippets were copied from the Boost Serialization library, which is
// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt)

#include "skip_xml_iarchive.hpp"
#include <climits>
#include <sstream>

template<class IStream>
std::basic_string<typename IStream::char_type, typename IStream::traits_type> boost::archive::read_tag(IStream& is)
{
	typedef typename IStream::char_type char_type;

	char_type val = '<';
	is.ignore(INT_MAX, val); //Skip anything before the tag.
	basic_string<char_type, typename IStream::traits_type> tag(1, val);

	while(val != '>' && !is.fail())
	{
#if defined(_MSC_VER)
# pragma warning( push ) // Disable optional warning
# pragma warning(disable: 4242)
#endif
		val = is.get();
#if defined(_MSC_VER)
# pragma warning( pop )
#endif
		tag += val;
	}
	if(tag.size() < 3) //Smallest tag is <x>.
		boost::throw_exception(archive_exception(archive_exception::stream_error));
	return tag;
}

template<class Archive>
boost::archive::skip_xml_iarchive_impl<Archive>::skip_xml_iarchive_impl(std::istream & is, unsigned int flags)
: xml_iarchive_impl<Archive>(is, flags | no_xml_tag_checking)
{}

template<class Archive>
void boost::archive::skip_xml_iarchive_impl<Archive>::read_end_tag(std::string const& name)
{
	for(;;)
	{
		//We're either looking at a start tag or an end tag.
		std::string const next_tag = read_tag(this->This()->get_is());

		if(next_tag[1] == '/')
		{ //It's an end tag. Check that it's the end tag we expect, and we're done.
			if(this->This()->gimpl->parse_end_tag(istringstream(next_tag))
				&& this->This()->gimpl->rv.object_name == name)
			{ 
				break;
			}
			boost::throw_exception(archive_exception(archive_exception::stream_error));				
		}

		//It's a start tag. Skip the element.
		if(this->This()->gimpl->parse_start_tag(istringstream(next_tag)))
			skip_all_elements(this->This()->gimpl->rv.object_name);
		else
			boost::throw_exception(archive_exception(archive_exception::stream_error));
	}
}

//Skip the element whose start tag was just read, and whose name is 'name'.
//The stream is left at the end of this complete element.
template<class Archive>
void boost::archive::skip_xml_iarchive_impl<Archive>::skip_all_elements(std::string const& name)
{
	std::string ignore;
	if(!this->This()->gimpl->parse_string(this->This()->get_is(), ignore))
		return;

	read_end_tag(name);
}

template<class Archive>
template<class T>
void boost::archive::skip_xml_iarchive_impl<Archive>::load_override(
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
	const
#endif
	boost::serialization::nvp<T> & t, int)
{
	if(!t.name())
		return xml_iarchive_impl<Archive>::load_override(t, 0);
	load_start(t.name());
	// don't check start tag at highest level
	std::string name_found = this->This()->gimpl->rv.object_name;
	bool const skip = 
		depth > 1
		&& name_found != t.name();
	if(skip)
	{
		skip_all_elements(name_found);
		load_override(t, 0); //We still haven't loaded t, so load t.
	}
	else
	{
		boost::archive::load(*this->This(), t.value());
		read_end_tag(t.name());
	}
}

template<class Archive>
template<class T>
void boost::archive::skip_xml_iarchive_impl<Archive>::load_override(T & t, BOOST_PFTO int i)
{ xml_iarchive_impl<Archive>::load_override(t, i); }

boost::archive::skip_xml_iarchive::skip_xml_iarchive(std::istream & is, unsigned int flags)
: skip_xml_iarchive_impl<skip_xml_iarchive>(is, flags)
{}
