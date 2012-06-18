#include "common.hpp"
#include <DataStorage/common.hpp>

namespace isis {
namespace python {

void _setPythonLogger ( const boost::python::api::object& mH )
{
	isis::python::util::PythonMessageHandler::pythonLogger_ = mH;
}

	
}}