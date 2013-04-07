// (C) Copyright 2006 Todd Greer. tgreer <at> affinegy <dot> com
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt)

// Some code snippets were copied from the Boost Serialization library, which is
// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt)

// This header declares skip_xmp_iarchive, an archive for use with the Boost
// Serialization library. It reads data serialized by xml_oarchive and can
// handle extra elements that have been inserted into the XML. 
//
// Though those extra elements may have been inserted by hand, the purpose of 
// this archive is to support forwards compatibility. Consider the following events:
// 1. Version two of a class adds some data members that are serialized.
// 2. This serialization record is deserialized by version one of the class.
// With xml_iarchive, this would cause a serialization failure. With skip_xml_iarchive, 
// the new elements will simply be ignored. Unexpected elements can be inserted at any
// level in the hierarchy, and will be skipped over, as long as the document remains
// well-formed XML.

#ifndef BOOST_ARCHIVE_SKIP_XML_IARCHIVE
#define BOOST_ARCHIVE_SKIP_XML_IARCHIVE

#if defined(_MSC_VER)
# pragma once
# pragma warning(push) // Disable some optional warnings
# pragma warning(disable: 4100 4244 4267 4640)
#endif
#include <boost/archive/xml_iarchive.hpp>
#if defined(_MSC_VER)
# pragma warning( pop )
#endif

namespace boost
{
	namespace archive
	{
		template<class IStream>
		inline std::basic_string<typename IStream::char_type, typename IStream::traits_type> read_tag(IStream& is);

		template<class Archive>
		class skip_xml_iarchive_impl: public boost::archive::xml_iarchive_impl<Archive>
		{
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
		public:
#elif defined(BOOST_MSVC)
			// for some inexplicable reason insertion of "class" generates compile erro
			// on msvc 7.1
			friend boost::archive::detail::interface_iarchive<Archive>;
		protected:
#else
			friend class boost::archive::detail::interface_iarchive<Archive>;
		protected:
#endif

			skip_xml_iarchive_impl(std::istream & is, unsigned int flags = 0);

			void read_end_tag(std::string const& name);
			
			//Skip the element whose start tag was just read, and whose name is 'name'.
			//The stream is left at the end of this complete element.
			void skip_all_elements(std::string const& name);
			
			template<class T> void load_override(
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
				const
#endif
				boost::serialization::nvp<T> & t, int);

				template<class T> void load_override(T & t, BOOST_PFTO int i);
		};

		class skip_xml_iarchive: public skip_xml_iarchive_impl<skip_xml_iarchive>
		{
		public:
			skip_xml_iarchive(std::istream & is, unsigned int flags = 0);
		};
	}
}
#endif //BOOST_ARCHIVE_SKIP_XML_IARCHIVE