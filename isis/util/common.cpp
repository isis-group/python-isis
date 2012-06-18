#include "common.hpp"
#include <DataStorage/common.hpp>

namespace isis {
namespace python {

void setPythonLoggingHandler ( const boost::python::api::object& mH )
{
	isis::python::util::PythonMessageHandler::pythonMessageHandler_ = mH;


}

	
}}