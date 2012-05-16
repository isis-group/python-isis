
#ifndef CORE_HPP_
#define CORE_HPP_

#include <boost/python.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include "common.hpp"
#include "_application.hpp"
#include "_convertToPython.hpp"
#include "_vector.hpp"
#include "_propmap.hpp"
#include "CoreUtils/selection.hpp"
#include "CoreUtils/singletons.hpp"

using namespace boost::python;
using namespace isis::python::util;

BOOST_PYTHON_MODULE( _util )
{
	isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().create();
	//#######################################################################################
	//  Application
	//#######################################################################################
	using namespace isis::python::util::Application;
	class_<isis::util::Application>( "Application", init<const char *>() )
	.def( "printHelp", &isis::util::Application::printHelp )
	.def( "getCoreVersion", &isis::util::Application::getCoreVersion )
	.staticmethod( "getCoreVersion" )
	.def( "init", &_init )
	.def( "addParameter", &_addParameter )
	.def( "getParameter", &_getParameter )
	.def( "setNeeded", &_setNeeded )
	.def( "setHidden", &_setHidden )
	.def( "setDescription", &_setDescription )
	;
	//#######################################################################################
	//  PropertyMap
	//#######################################################################################
	using namespace isis::python::util::PropertyMap;
	void ( *_join1 ) ( isis::util::PropertyMap &, const isis::util::PropertyMap&, bool ) = isis::python::util::PropertyMap::_join;
	void ( *_join2 ) ( isis::util::PropertyMap &, const isis::data::Image&, bool ) = isis::python::util::PropertyMap::_join;
	class_<isis::util::PropertyMap>( "PropertyMap", init<>() )
	.def( "hasProperty", &_hasProperty )
	.def( "hasBranch", &_hasBranch )
	.def( "getBranch", &_branch )
	.def( "removeProperty", &_removeProperty )
	.def( "isValid", &isis::util::PropertyMap::isValid )
	.def( "isEmpty", &isis::util::PropertyMap::isEmpty )
	.def( "setProperty", &_setProperty )
	.def( "getProperty", &_getProperty )
	.def( "setPropertyAs", &_setPropertyAs )
	.def( "join", _join1, ( arg ( "PropertyMap" ), arg( "overwrite") ) )
	.def( "join", _join2, ( arg ( "Image" ), arg( "overwrite" ) ) )
	;
	//#######################################################################################
	//  Selection
	//#######################################################################################
	class_<isis::util::Selection>( "Selection", init<const char *>() )
	.def( init<>() )
	;
	//#######################################################################################
	//  Vector4
	//#######################################################################################
	class_<isis::util::fvector4, _Vector4<float> >( "fvector4", init<float, float, float, float>() )
	.def( init<>() )
	.def( init<isis::util::fvector4>() )
	.def( "__setitem__", &_Vector4<float>::setItem )
	.def( "__getitem__", &_Vector4<float>::getItem )
	.def( "__iter__", iterator<isis::util::fvector4>() )
	;
	class_<isis::util::ivector4, _Vector4<int32_t> >( "ivector4", init<int32_t, int32_t, int32_t, int32_t>() )
	.def( init< isis::util::ivector4 >() )
	.def( init<>() )
	.def( "__setitem__", &_Vector4<int32_t>::setItem )
	.def( "__getitem__", &_Vector4<int32_t>::getItem )
	.def( "__iter__", iterator<isis::util::ivector4>() )
	;
	class_<isis::util::dvector4, _Vector4<double> >( "dvector4", init<double, double, double, double>() )
	.def( init< isis::util::dvector4>() )
	.def( "__setitem__", &_Vector4<double>::setItem )
	.def( "__getitem__", &_Vector4<double>::getItem )
	.def( "__iter__", iterator<isis::util::dvector4>() )
	.def( init<>() )
	;
	//#######################################################################################
	//  enums for types
	//#######################################################################################
	using namespace isis::python::util::_internal;
	enum_<types>( "types" )
	.value( "INT8_T", INT8_T )
	.value( "UINT8_T", UINT8_T )
	.value( "INT16_T", INT16_T )
	.value( "UINT16_T", UINT16_T )
	.value( "INT32_T", INT32_T )
	.value( "UINT32_T", UINT32_T )
	.value( "INT64_T", INT64_T )
	.value( "UINT64_T", UINT64_T )
	.value( "FLOAT", FLOAT )
	.value( "DOUBLE", DOUBLE )
	.value( "FVECTOR4", FVECTOR4 )
	.value( "IVECTOR4", IVECTOR4 )
	.value( "DVECTOR4", DVECTOR4 )
	.value( "ILIST", ILIST )
	.value( "SLIST", SLIST )
	.value( "DLIST", DLIST )
	.value( "STD_STRING", STDSTRING )
	.value( "STRING", STDSTRING )
	.value( "SELECTION", SELECTION )
	.value( "COMPLEX_FLOAT", COMPLEX_FLOAT )
	.value( "COMPLEX_DOUBLE", COMPLEX_DOUBLE )
	.value( "BOOST_PTIME", BOOST_PTIME )
	.value( "BOOST_DATE", BOOST_DATE )
	;

}
#endif
