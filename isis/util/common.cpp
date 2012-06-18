#include "common.hpp"
#include "../common.hpp"
#include <DataStorage/common.hpp>

namespace isis {
namespace python {

void _setPythonLogger ( const boost::python::api::object& mH )
{
	isis::python::util::PythonMessageHandler::pythonLogger_ = mH;
}
boost::python::api::object _getPythonLogger()
{
	if( isis::python::util::PythonMessageHandler::pythonLogger_ ) {
		return isis::python::util::PythonMessageHandler::pythonLogger_;
	} else {
		LOG( PythonLog, warning ) << "No python logger found. Use \"setLogger()\" to set the python logger";
		return boost::python::api::object();
	}
}

bool _hasLogger()
{
	return isis::python::util::PythonMessageHandler::pythonLogger_;
}


	
}}