#include "_messageHandler.hpp"

boost::python::api::object isis::python::util::PythonMessageHandler::pythonMessageHandler_ = boost::python::api::object();

void isis::python::util::PythonMessageHandler::commit ( const isis::util::Message& mesg )
{
	std::cout << "commit" << std::endl;
}
