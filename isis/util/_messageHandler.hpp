#ifndef _ISIS_PYTHON_MESSAGE_HANDLER_HPP
#define _ISIS_PYTHON_MESSAGE_HANDLER_HPP

#include <CoreUtils/message.hpp>
#include <boost/python.hpp>

namespace isis
{
namespace python
{
namespace util
{
namespace _internal
{

void commit( const isis::util::Message &mesg, const char *lvl );

}

class PythonMessageHandler : public isis::util::MessageHandlerBase
{
public:
	PythonMessageHandler( LogLevel level ): MessageHandlerBase( level ) {}
	virtual ~PythonMessageHandler() {}
	void commit( const isis::util::Message &mesg );

	static boost::python::api::object pythonLogger_;
private:
	std::string last_;

};

class PythonMessageHandlerDebug : public isis::util::MessageHandlerBase
{
public:
	PythonMessageHandlerDebug( LogLevel level ): MessageHandlerBase( level ) {}
	virtual ~PythonMessageHandlerDebug() {}
	void commit( const isis::util::Message &mesg );

private:
	std::string last_;

};


}
}
}


#endif // _ISIS_PYTHON_MESSAGE_HANDLER_HPP