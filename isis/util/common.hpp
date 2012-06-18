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

namespace python
{

void _setPythonLogger( const boost::python::api::object &mH );
} //namespace python

} //namespace isis
#endif /* PYTHON_COMMON_HPP_ */


