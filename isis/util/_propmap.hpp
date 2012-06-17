/*
 * _propmap.hpp
 *
 *  Created on: Oct 22, 2010
 *      Author: tuerke
 */

#ifndef _PROPMAP_HPP_
#define _PROPMAP_HPP_

#include "_types.hpp"
#include "common.hpp"
#include "CoreUtils/propmap.hpp"
#include "boost/python.hpp"
#include "_convertFromPython.hpp"
#include "_convertToPython.hpp"
#include "CoreUtils/singletons.hpp"
#include "DataStorage/image.hpp"


using namespace boost::python;

namespace isis
{
namespace python
{
namespace util
{
class _PropertyMap : public isis::util::PropertyMap, public boost::python::wrapper<isis::util::PropertyMap>
{
public:
	_PropertyMap( PyObject *p );
	_PropertyMap( PyObject *p, const dict &d );
	_PropertyMap( PyObject *p, const isis::util::PropertyMap &base );
private:
	PyObject *self;
};
	
namespace PropertyMap
{

void _setPropertyAs( isis::util::PropertyMap &base, isis::python::util::types type, const std::string &key, api::object value );

void _setProperty( isis::util::PropertyMap &base, const std::string &key, api::object value );

api::object _getProperty( const isis::util::PropertyMap &base, const std::string &key );

bool _hasProperty( const isis::util::PropertyMap &base, const std::string &key );
bool _hasBranch( const isis::util::PropertyMap &base, const std::string &key );

isis::util::PropertyMap _branch( const isis::util::PropertyMap &base, const std::string &key );

void _join( isis::util::PropertyMap &base, const isis::data::Image &, bool overwrite );

void _join( isis::util::PropertyMap &base, const isis::util::PropertyMap &, bool overwrite );

void _join( isis::util::PropertyMap &base, const isis::data::Chunk &, bool overwrite );

bool _removeProperty( isis::util::PropertyMap &base, const std::string & );

list _getKeys( const isis::util::PropertyMap &base );

list _getMissing( const isis::util::PropertyMap &base );

dict _getDict( const isis::util::PropertyMap &base );

} // end namespace PropertyMap
}
}
}
#endif /* _PROPMAP_HPP_ */
