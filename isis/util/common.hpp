/*
 * common.hpp
 *
 *  Created on: Oct 20, 2010
 *      Author: tuerke
 */

#ifndef PYTHON_UTIL_COMMON_HPP
#define PYTHON_UTIL_COMMON_HPP

#include "CoreUtils/log.hpp"
#include "CoreUtils/common.hpp"
#include "CoreUtils/value.hpp"
#include <boost/python.hpp>
#include "_messageHandler.hpp"

namespace isis
{

struct PythonLog {static const char *name() {return "Python";}; enum {use = _ENABLE_LOG};};
struct PythonDebug {static const char *name() {return "PythonDebug";}; enum {use = _ENABLE_DEBUG};};

namespace python
{
typedef PythonLog Runtime;
typedef PythonDebug Debug;

template<typename HANDLE> void enable_log( LogLevel level )
{
	ENABLE_LOG( Runtime, HANDLE, level );
	ENABLE_LOG( Debug, HANDLE, level );
}
template <typename TYPE>
boost::python::list stdIter2PyList( const TYPE &stdList )
{
	boost::python::list retList;
	BOOST_FOREACH( const typename TYPE::const_reference listItem, stdList ) {
		retList.append( listItem );
	}
	return retList;
}

template <typename TYPE>
std::list<TYPE> pyList2StdList( const boost::python::list &pyList )
{
	std::list<TYPE> retList;

	for( unsigned short i = 0; i < boost::python::len( pyList ); i++ ) {
		retList.push_back( boost::python::extract<TYPE>( pyList[i] ) );
	}

	return retList;
}

void setPythonLoggingHandler( const boost::python::api::object &mH );
} //namespace python

} //namespace isis
#endif /* PYTHON_COMMON_HPP_ */


