
#ifndef CORE_HPP_
#define CORE_HPP_

#include <boost/python.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include "_application.hpp"
#include "_convertToPython.hpp"
#include "_vector.hpp"
#include "_propmap.hpp"
#include "_messageHandler.hpp"
#include "CoreUtils/selection.hpp"
#include "CoreUtils/singletons.hpp"
#include "common.hpp"
#include "../common.hpp"

using namespace boost::python;
using namespace isis::python::util;

BOOST_PYTHON_MODULE( _util )
{
	def( "setLogger", &isis::python::_setPythonLogger );
	def( "getLogger", &isis::python::_getPythonLogger );
	def( "hasLogger", &isis::python::_hasLogger );
	
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
	void ( *_join1 ) ( isis::util::PropertyMap &, const isis::util::PropertyMap &, bool ) = isis::python::util::PropertyMap::_join;
	void ( *_join2 ) ( isis::util::PropertyMap &, const isis::data::Image &, bool ) = isis::python::util::PropertyMap::_join;
	void ( *_join3 ) ( isis::util::PropertyMap &, const isis::data::Chunk &, bool ) = isis::python::util::PropertyMap::_join;;
	class_<isis::util::PropertyMap, isis::python::util::_PropertyMap>( "PropertyMap", init<>() )
	.def( init<const dict&>() )
	.def( init<const isis::util::PropertyMap &>() )
	.def( "hasProperty", &_hasProperty )
	.def( "hasBranch", &_hasBranch )
	.def( "getBranch", &_branch )
	.def( "removeProperty", &_removeProperty )
	.def( "isValid", &isis::util::PropertyMap::isValid )
	.def( "isEmpty", &isis::util::PropertyMap::isEmpty )
	.def( "setProperty", &_setProperty )
	.def( "getProperty", &_getProperty )
	.def( "setPropertyAs", &_setPropertyAs )
	.def( "join", _join1, ( arg ( "PropertyMap" ), arg( "overwrite" ) ) )
	.def( "join", _join2, ( arg ( "Image" ), arg( "overwrite" ) ) )
	.def( "join", _join3, ( arg ( "Chunk" ), arg( "overwrite" ) ) )
	.def( "getDifference", &isis::util::PropertyMap::getDifference )
	.def( "getKeys", &_getKeys )
	.def( "getMissing", &_getMissing )
	.def( "getDict", &_getDict )
	.def( "__str__", &isis::python::util::PropertyMap::_toString )
	
	;
	//#######################################################################################
	//  Selection
	//#######################################################################################
	class_<isis::util::Selection>( "Selection", init<const char *>() )
	.def( init<>() )
	.def( "set", ( bool ( ::isis::util::Selection:: * ) ( const char *) ) ( &isis::util::Selection::set ), ( arg( "entry" ) ) )
	.def( "set", ( bool ( ::isis::util::Selection:: * ) ( unsigned short ) ) ( &isis::util::Selection::set ) , ( arg( "entry" ) ) )
	;
	//#######################################################################################
	//  Vector3
	//#######################################################################################
	class_<isis::util::fvector3, _Vector3<float> >( "fvector3", init<float, float, float>() )
	.def( init<>() )
	.def( init<isis::util::fvector3>() )
	.def( "__setitem__", &_Vector3<float>::setItem )
	.def( "__getitem__", &_Vector3<float>::getItem )
	.def( "__iter__", iterator<isis::util::fvector4>() )
	.def( "__str__", &_Vector3<double>::_toString )
	.def( "toString", &_Vector3<float>::_toString )
	;
	class_<isis::util::dvector3, _Vector3<double> >( "dvector3", init<double, double, double>() )
	.def( init< isis::util::dvector3>() )
	.def( "__setitem__", &_Vector3<double>::setItem )
	.def( "__getitem__", &_Vector3<double>::getItem )
	.def( "__iter__", iterator<isis::util::dvector4>() )
	.def( "__str__", &_Vector3<double>::_toString )
	.def( "toString", &_Vector3<double>::_toString )
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
	.def( "__str__", &_Vector4<double>::_toString )	
	.def( "toString", &_Vector4<float>::_toString )
	;
	class_<isis::util::ivector4, _Vector4<int32_t> >( "ivector4", init<int32_t, int32_t, int32_t, int32_t>() )
	.def( init< isis::util::ivector4 >() )
	.def( init<>() )
	.def( "__setitem__", &_Vector4<int32_t>::setItem )
	.def( "__getitem__", &_Vector4<int32_t>::getItem )
	.def( "__iter__", iterator<isis::util::ivector4>() )
	.def( "__str__", &_Vector4<double>::_toString )
	.def( "toString", &_Vector4<int32_t>::_toString )
	;
	class_<isis::util::dvector4, _Vector4<double> >( "dvector4", init<double, double, double, double>() )
	.def( init< isis::util::dvector4>() )
	.def( "__setitem__", &_Vector4<double>::setItem )
	.def( "__getitem__", &_Vector4<double>::getItem )
	.def( "__iter__", iterator<isis::util::dvector4>() )
	.def( "__str__", &_Vector4<double>::_toString )
	.def( "toString", &_Vector4<double>::_toString )
	.def( init<>() )
	;
	//#######################################################################################
	//  enums for types
	//#######################################################################################
	using namespace isis::python::util::_internal;
	enum_<types>( "types" )
	.value( "INT8", INT8_T )
	.value( "UINT8", UINT8_T )
	.value( "INT16", INT16_T )
	.value( "UINT16", UINT16_T )
	.value( "INT32", INT32_T )
	.value( "UINT32", UINT32_T )
	.value( "INT64", INT64_T )
	.value( "UINT64", UINT64_T )
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
	.value( "CFLOAT", CFLOAT )
	.value( "CDOUBLE", CDOUBLE )
	.value( "BOOST_PTIME", BOOST_PTIME )
	.value( "BOOST_DATE", BOOST_DATE )
	.value( "COLOR_24", COLOR_24 )
	.value( "COLOR_48", COLOR_48 )
	;

}
#endif
