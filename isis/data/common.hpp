/*
 * common.hpp
 *
 *  Created on: Oct 20, 2010
 *      Author: tuerke
 */

#ifndef PYTHON_COMMON_DATA_HPP
#define PYTHON_COMMON_DATA_HPP

#include "CoreUtils/log.hpp"
#include "DataStorage/chunk.hpp"
#include "DataStorage/image.hpp"
#include "DataStorage/valuearray.hpp"
#include <boost/python.hpp>

using namespace isis::data;
namespace isis
{
namespace python
{
namespace data
{
namespace _internal
{
	
void setInitialProperties ( isis::data::Chunk &ch );
	

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


}
}
} //namespace python

} //namespace isis
#endif /* PYTHON_COMMON_HPP_ */


