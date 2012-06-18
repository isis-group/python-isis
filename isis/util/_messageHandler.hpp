#ifndef _ISIS_PYTHON_MESSAGE_HANDLER_HPP
#define _ISIS_PYTHON_MESSAGE_HANDLER_HPP

#include <CoreUtils/message.hpp>
#include <boost/python.hpp>

namespace isis {
namespace python {
namespace util {

class PythonMessageHandler : public isis::util::MessageHandlerBase
{
public:
	PythonMessageHandler( LogLevel level ): MessageHandlerBase( level ) {}
	virtual ~PythonMessageHandler() {}
	void commit( const isis::util::Message &mesg );
	
	static boost::python::api::object pythonMessageHandler_;
};


}}}


#endif // _ISIS_PYTHON_MESSAGE_HANDLER_HPP