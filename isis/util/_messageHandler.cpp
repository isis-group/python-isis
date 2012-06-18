#include "_messageHandler.hpp"

boost::python::api::object isis::python::util::PythonMessageHandler::pythonLogger_ = boost::python::api::object();

void isis::python::util::_internal::commit ( const isis::util::Message& mesg, const char* lvl )
{
		std::stringstream commit_stream;
		commit_stream << mesg.m_module << ":" << isis::util::logLevelName( mesg.m_level );
#ifndef NDEBUG //if with debug-info
		commit_stream << "[" << mesg.m_file.leaf() << ":" << mesg.m_line << "] ";
#else
		commit_stream << "[" << mesg.m_object << "] ";
#endif
		commit_stream << mesg.merge();
		PyObject *pLoggingFunc;
		pLoggingFunc = PyObject_GetAttrString( isis::python::util::PythonMessageHandler::pythonLogger_.ptr(), lvl);
		PyObject *pArgs = PyTuple_New(1);
		PyTuple_SetItem(pArgs, 0, PyString_FromString( commit_stream.str().c_str()));
		PyObject_CallObject( pLoggingFunc, pArgs );
}


void isis::python::util::PythonMessageHandler::commit ( const isis::util::Message& mesg )
{
	//only commit if a logging handler is set
	if( pythonLogger_ && (last_ != mesg.str() || last_.empty() ) ) {
		last_ = mesg.str();
		switch ( mesg.m_level ) {
			case isis::notice:
			case isis::verbose_info:
			case isis::info:
				_internal::commit( mesg, "info" );
				break;
			case isis::warning:
				_internal::commit( mesg, "warning" );
				break;
			case isis::error:
				_internal::commit( mesg, "error" );
				break;
		}

	}
}
void isis::python::util::PythonMessageHandlerDebug::commit ( const isis::util::Message& mesg )
{
		//only commit if a logging handler is set
	if( isis::python::util::PythonMessageHandler::pythonLogger_ && ( last_ != mesg.str() || last_.empty() ) ) {
		last_ = mesg.str();
		_internal::commit( mesg, "debug" );
	}
		
}