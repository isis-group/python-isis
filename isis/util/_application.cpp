#include "_application.hpp"

namespace isis
{
namespace python
{
namespace util
{
namespace Application
{
void _addParameter( isis::util::Application &base, const std::string &name, boost::python::api::object value )
{
	static_cast<isis::util::PropertyValue &>( base.parameters[name] ) = _internal::ConvertFromPython::convert( value );
}

boost::python::api::object _getParameter( const isis::util::Application &base, const std::string &name )
{
	return isis::util::Singletons::get< python::util::_internal::TypesMap, 10>().at(
			   base.parameters.at( name.c_str() ).getTypeID() )->convert( *base.parameters.at( name.c_str() ) );
}


void _setDescription( isis::util::Application &base, const std::string &name, const std::string &desc )
{
	base.parameters.at( name ).setDescription( desc );
}

void _setHidden( isis::util::Application &base, const std::string &name, const bool &hidden )
{
	base.parameters.at( name ).hidden() = hidden;
}

void _setNeeded( isis::util::Application &base, const std::string &name, const bool &needed )
{
	base.parameters.at( name ).needed() = needed;
}

bool _init( isis::util::Application &base, boost::python::list pyargv, bool exitOnError )
{
	size_t n = boost::python::len( pyargv );
	char *argv[n];

	for( size_t i = 0; i < n; i++ ) {
		argv[i] = boost::python::extract<char *>( pyargv[i] );
	}

	return base.init( n, argv, exitOnError );

}



} // end namespace Application

}
}
} // end namespace