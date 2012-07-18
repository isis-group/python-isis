/*
 * _global.hpp
 *
 *  Created on: Jun 07, 2012
 *      Author: tuerke
 */

#ifndef _ISIS_PYTHON_GLOBAL_HPP_
#define _ISIS_PYTHON_GLOBAL_HPP_

#include <string>
#include <boost/python/numeric.hpp>

namespace isis
{
namespace python
{
namespace data
{
namespace global
{

void _set_array_module_and_type( const std::string &module, const std::string &type )
{
	boost::python::numeric::array::set_module_and_type( module.c_str(), type.c_str() );
}


}
}
}
}

#endif
