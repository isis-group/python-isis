/*
 * datastorage.cpp
 *
 *  Created on: Oct 20, 2010
 *      Author: tuerke
 */

#ifndef DATA_HPP_
#define DATA_HPP_

#include <boost/python.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include "common.hpp"
#include "_ioapplication.hpp"
#include "_ndimensional.hpp"
#include "_image.hpp"
#include "_writingvalueadapter.hpp"
#include "_chunk.hpp"
#include "_iofactory.hpp"
#include "std_item.hpp"
#include "util/_application.hpp"
#include "util/_propmap.hpp"

using namespace boost::python;
using namespace isis::python::data;

BOOST_PYTHON_MODULE ( _data )
{
	boost::python::numeric::array::set_module_and_type( "numpy", "ndarray" );
	//#######################################################################################
	//  IOApplication
	//#######################################################################################
	class_<isis::data::IOApplication, _IOApplication, bases< isis::util::Application> > ( "IOApplication", init<const char *, bool, bool>() )
	.def ( "autoload", &_IOApplication::_autoload )
	.def ( "autowrite", ( bool ( ::IOApplication:: * ) ( std::list<isis::data::Image>, bool ) ) ( &isis::data::IOApplication::autowrite ), ( arg ( "imageList" ), arg ( "exitOnError" ) ) )
	.def ( "autowrite", ( bool ( ::IOApplication:: * ) ( isis::data::Image, bool ) ) ( &isis::data::IOApplication::autowrite ), ( arg ( "image" ), arg ( "exitOnError" ) ) )
	//wrappings for standard values
	.def ( "autowrite", ( bool ( ::_IOApplication:: * ) ( std::list<isis::data::Image> ) ) ( &_IOApplication::_autowrite ), ( arg ( "imageList" ), arg ( "exitOnError" ) ) )
	.def ( "autowrite", ( bool ( ::_IOApplication:: * ) ( isis::data::Image ) ) ( &_IOApplication::_autowrite ), ( arg ( "image" ), arg ( "exitOnError" ) ) )
	.def ( "images", &_IOApplication::_images )
	.def ( "fetchImage", &IOApplication::fetchImage )
	.def ( "fetchImageAs", &_IOApplication::_fetchImageAs )
	;
	//#######################################################################################
	//  NDimensional<4>
	//#######################################################################################
	//function pointers
	void ( *_init1 ) ( isis::data::_internal::NDimensional<4>&, const isis::util::ivector4 & ) = isis::python::data::NDimensional::_init;
	void ( *_init2 ) ( isis::data::_internal::NDimensional<4>&, const size_t &, const size_t &, const size_t &, const size_t & ) = isis::python::data::NDimensional::_init;
	size_t ( *_getLinearIndex1 ) ( const isis::data::_internal::NDimensional<4>&, const isis::util::ivector4 & ) = isis::python::data::NDimensional::_getLinearIndex;
	size_t ( *_getLinearIndex2 ) ( const isis::data::_internal::NDimensional<4>&, const size_t &, const size_t &, const size_t &, const size_t & ) = isis::python::data::NDimensional::_getLinearIndex;
	bool ( *_isInRange1 ) ( const isis::data::_internal::NDimensional<4>&, const isis::util::ivector4 & ) = isis::python::data::NDimensional::_isInRange;
	bool ( *_isInRange2 ) ( const isis::data::_internal::NDimensional<4>&,  const size_t &, const size_t &, const size_t &, const size_t & ) = isis::python::data::NDimensional::_isInRange;
	// the class itself
	class_<isis::data::_internal::NDimensional<4>, _NDimensional > ( "NDimensional4", init<const isis::util::ivector4 &>() )
	.def ( init<>() )
	.def ( "init", _init1, ( arg ( "dims" ) ) )
	.def ( "init", _init2, ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ) ) )
	.def ( "getLinearIndex", _getLinearIndex1, ( arg ( "dims" ) ) )
	.def ( "getLinearIndex", _getLinearIndex2, ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ) ) )
	.def ( "getCoordsFromLinIndex", &isis::python::data::NDimensional::_getCoordsFromLinIndex )
	.def ( "isInRange", _isInRange1, ( arg ( "dims" ) ) )
	.def ( "isInRange", _isInRange2, ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ) ) )
	.def ( "getVolume", &isis::data::_internal::NDimensional<4>::getVolume )
	.def ( "getDimSize", &isis::data::_internal::NDimensional<4>::getDimSize )
	.def ( "getSizeAsString", &isis::data::_internal::NDimensional<4>::getSizeAsString )
	.def ( "getSizeAsString", &isis::python::data::NDimensional::_getSizeAsString ) // this is for the one that has no argument
	.def ( "getSizeAsVector", &isis::python::data::NDimensional::_getSizeAsVector )
	.def ( "getRelevantDims", &isis::data::_internal::NDimensional<4>::getRelevantDims )
	.def ( "getFoV", &isis::python::data::NDimensional::_getFoV )
	;

	//#######################################################################################
	//  WritingValueAdapter
	//#######################################################################################
	class_<isis::data::_internal::WritingValueAdapter, _WritingValueAdapter > ( "WritingValueAdapter", no_init )
	.def ( "get", &_WritingValueAdapter::_get )
	.def ( "set", &_WritingValueAdapter::_set );

	//#######################################################################################
	//  Image
	//#######################################################################################
	//function pointer
	api::object ( *_getVoxel1 ) ( const isis::data::Image &, const isis::util::ivector4 & ) = isis::python::data::Image::_voxel;
	api::object ( *_getVoxel2 ) ( const isis::data::Image &, const size_t &, const size_t &, const size_t &, const size_t & ) = isis::python::data::Image::_voxel;
	bool ( *_setVoxel1 ) ( const isis::data::Image &, const isis::util::ivector4 &, const api::object & ) = isis::python::data::Image::_setVoxel;
	bool ( *_setVoxel2 ) ( const isis::data::Image &, const size_t &, const size_t &, const size_t &, const size_t &, const api::object & ) = isis::python::data::Image::_setVoxel;
	isis::data::Chunk ( *_getChunk ) ( const isis::data::Image &, const isis::util::ivector4 &, bool ) = isis::python::data::Image::_getChunk;
	isis::data::Chunk ( *_getChunkAs1 ) ( const isis::data::Image &, const isis::util::ivector4 &, const isis::python::data::image_types & ) = isis::python::data::Image::_getChunkAs;
	isis::data::Chunk ( *_getChunkAs2 ) ( const isis::data::Image &, const size_t &, const size_t &, const size_t &, const size_t &, const isis::python::data::image_types & ) = isis::python::data::Image::_getChunkAs;
	boost::python::numeric::array ( *_getArray1 ) ( isis::python::data::_Image & ) = isis::python::data::Image::_getArray;
	boost::python::numeric::array ( *_getArray2 ) ( isis::python::data::_Image &, isis::python::data::image_types ) = isis::python::data::Image::_getArray;
	isis::data::Image ( *_createFromArray1 ) ( const boost::python::numeric::array & ) = isis::python::data::Image::_createFromArray;
	isis::data::Image ( *_createFromArray2 ) ( const boost::python::numeric::array &, const isis::data::Image & ) = isis::python::data::Image::_createFromArray;

	class_<isis::data::Image, _Image, bases< isis::data::_internal::NDimensional<4>, isis::util::PropertyMap > > ( "Image", init<>() )
	.def ( init<isis::data::Image>() )
	.def ( "checkMakeClean", &isis::data::Image::checkMakeClean )
	.def ( "getVoxel", _getVoxel1, ( arg ( "coords" ) ) )
	.def ( "getVoxel", _getVoxel2, ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ) ) )
	.def ( "setVoxel", _setVoxel1, ( arg ( "coords" ), arg ( "value" ) ) )
	.def ( "setVoxel", _setVoxel2, ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ), arg ( "value" ) ) )
	.def ( "getChunkList", &isis::python::data::Image::_getChunksAsVector )
	.def ( "getChunksAsList", &isis::python::data::Image::_getChunksAsVector )
	.def ( "getMajorTypeID", &isis::data::Image::getMajorTypeID )
	.def ( "getChunkAt", &isis::data::Image::getChunkAt )
	.def ( "getChunk", ( isis::data::Chunk ( ::isis::data::Image:: * ) ( size_t, size_t, size_t, size_t, bool ) ) ( &isis::data::Image::getChunk ), ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ), arg ( "copy_metadata" ) ) )
	.def ( "getChunk", _getChunk, ( arg ( "coords" ), arg ( "copy_metadata" ) ) )
	.def ( "getChunkAs", _getChunkAs1, ( arg ( "coords" ), arg ( "type" ) ) )
	.def ( "getChunkAs", _getChunkAs2, ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ), arg ( "type" ) ) )
	.def ( "insertChunk", &isis::data::Image::insertChunk )
	.def ( "reIndex", &isis::data::Image::reIndex )
	.def ( "isEmpty", &isis::data::Image::isEmpty )
	.def ( "bytesPerVoxel", &isis::data::Image::getMaxBytesPerVoxel )
	.def ( "getMin", &isis::python::data::Image::_getMin )
	.def ( "getMax", &isis::python::data::Image::_getMax )
	.def ( "compare", &isis::data::Image::compare )
	.def ( "transformCoords", &isis::python::data::Image::_transformCoords )
	.def ( "getMainOrientationAsString", &isis::python::data::Image::_getMainOrientationAsString )
	.def ( "getMainOrientation", &isis::data::Image::getMainOrientation )
	.def ( "getPhysicalCoordsFromIndex", &isis::data::Image::getPhysicalCoordsFromIndex )
	.def ( "getIndexFromPhysicalCoords", &isis::data::Image::getIndexFromPhysicalCoords )
	.def ( "convertToType", &isis::python::data::Image::_convertToType )
	.def ( "spliceDownTo", &isis::python::data::Image::_spliceDownTo )
	.def ( "getDeepCopy", &isis::python::data::Image::_deepCopy )
	.def ( "getDeepCopyAs", &isis::python::data::Image::_deepCopyAs )
	.def ( "getCheapCopy", &isis::python::data::Image::_cheapCopy )
	.def ( "createEmpty", &isis::python::data::Image::_createImage )
	.staticmethod ( "createEmpty" )
	.def ( "getArray",  _getArray1 )
	.def ( "getArray",  _getArray2, arg( "type" ) )
	.def ( "createFromChunks", &isis::python::data::Image::_createImageFromChunks )
	.staticmethod( "createFromChunks" )
	.def ( "createFromArray", _createFromArray1, arg ( "array" ) )
	.def ( "createFromArray", _createFromArray2, arg( "array" ), arg( "template_image" ) )
	.staticmethod( "createFromArray" )
	.def ( "__iter__", iterator<isis::data::Image>() )
	;
	//#######################################################################################
	//  Chunk
	//#######################################################################################
	class_<isis::data::Chunk, _Chunk, bases< isis::data::_internal::NDimensional<4>, isis::util::PropertyMap> > ( "Chunk", init<_Chunk>() )
	.def ( "getVoxel", ( api::object ( ::_Chunk:: * ) ( const isis::util::ivector4 & ) ) ( &_Chunk::_voxel ), ( arg ( "coord" ) ) )
	.def ( "getVoxel", ( api::object ( ::_Chunk:: * ) ( const size_t &, const size_t &, const size_t &, const size_t & ) ) ( &_Chunk::_voxel ), ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ) ) )
	.def ( "setVoxel", ( bool ( ::_Chunk:: * ) ( const isis::util::ivector4 &, const api::object & ) ) ( &_Chunk::_setVoxel ), ( arg ( "coord" ), arg ( "value" ) ) )
	.def ( "setVoxel", ( bool ( ::_Chunk:: * ) ( const size_t &, const size_t &, const size_t &, const size_t &, const api::object & ) ) ( &_Chunk::_setVoxel ), ( arg ( "first" ), arg ( "second" ), arg ( "third" ), arg ( "fourth" ), arg ( "value" ) ) )
	.def ( "useCount", &isis::data::Chunk::useCount )
	.def ( "cloneToNew", &isis::data::Chunk::cloneToNew )
	.def ( "convertToType", ( bool ( ::_Chunk:: * ) ( const unsigned short ) ) ( &_Chunk::_convertToType ), ( arg ( "ID" ) ) )
	.def ( "convertToType", ( bool ( ::_Chunk:: * ) ( const unsigned short, float, size_t ) ) ( &_Chunk::_convertToType ), ( arg ( "ID" ), arg ( "scaling" ), arg ( "offset" ) ) )
	;
	//#######################################################################################
	//  IOFactory
	//#######################################################################################
	bool ( *_writeImage1 ) ( const isis::data::Image &, const std::string &, const std::string &, const std::string & ) = isis::python::data::_IOFactory::_write;
	bool ( *_writeImage2 ) ( const isis::data::Image &, const std::string &, const std::string & ) = isis::python::data::_IOFactory::_write;
	bool ( *_writeImage3 ) ( const isis::data::Image &, const std::string & ) = isis::python::data::_IOFactory::_write;
	bool ( *_writeImages1 ) ( const list &, const std::string &, const std::string &, const std::string & ) = isis::python::data::_IOFactory::_write;
	bool ( *_writeImages2 ) ( const list &, const std::string &, const std::string & ) = isis::python::data::_IOFactory::_write;
	bool ( *_writeImages3 ) ( const list &, const std::string & ) = isis::python::data::_IOFactory::_write;
	list ( *_loadImages1 ) ( const std::string &, const std::string &, const std::string & ) = isis::python::data::_IOFactory::_load;
	list ( *_loadImages2 ) ( const std::string &, const std::string & ) = isis::python::data::_IOFactory::_load;
	list ( *_loadImages3 ) ( const std::string & ) = isis::python::data::_IOFactory::_load;

	class_< _IOFactory> ( "IOFactory", no_init )
	.def ( "write", _writeImage1, ( arg ( "image" ), arg ( "path" ), arg ( "suffix_override" ), arg ( "dialect" ) ) )
	.def ( "write", _writeImage2, ( arg ( "image" ), arg ( "path" ), arg ( "suffix_override" ) ) )
	.def ( "write", _writeImage3, ( arg ( "image" ), arg ( "path" ) ) )
	.def ( "write", _writeImages1, ( arg ( "images" ), arg ( "path" ), arg ( "suffix_override" ), arg ( "dialect" ) ) )
	.def ( "write", _writeImages2, ( arg ( "images" ), arg ( "path" ), arg ( "suffix_override" ) ) )
	.def ( "write", _writeImages3, ( arg ( "images" ), arg ( "path" ) ) )
	.staticmethod ( "write" )
	.def ( "load", _loadImages1, ( arg ( "path" ), arg ( "suffix_override" ), arg ( "dialect" ) ) )
	.def ( "load", _loadImages2, ( arg ( "path" ), arg ( "suffix_override" ) ) )
	.def ( "load", _loadImages3, ( arg ( "path" ) ) )
	.staticmethod ( "load" )
	.def ( "getFormats", &_IOFactory::_getFormats )
	.staticmethod ( "getFormats" )
	;
	//#######################################################################################
	//  enums for image_types
	//#######################################################################################
	using namespace isis::python::data::_internal;
	enum_<image_types> ( "image_types" )
	.value ( "INT8_T", INT8_T )
	.value ( "UINT8_T", UINT8_T )
	.value ( "INT16_T", INT16_T )
	.value ( "UINT16_T", UINT16_T )
	.value ( "INT32_T", INT32_T )
	.value ( "UINT32_T", UINT32_T )
	.value ( "INT64_T", INT64_T )
	.value ( "UINT64_T", UINT64_T )
	.value ( "FLOAT", FLOAT )
	.value ( "DOUBLE", DOUBLE )
	.value ( "CFLOAT", CFLOAT )
	.value ( "CDOUBLE", CDOUBLE )
	.value ( "COLOR_24", COLOR_24 )
	.value ( "COLOR_48", COLOR_48 )
	;
	//#######################################################################################
	//  enums for orientations
	//#######################################################################################
	enum_<isis::data::Image::orientation> ( "orientation" )
	.value ( "AXIAL", isis::data::Image::axial )
	.value ( "REVERSED_AXIAL", isis::data::Image::reversed_axial )
	.value ( "SAGITTAL", isis::data::Image::sagittal )
	.value ( "REVERSED_SAGITTAL", isis::data::Image::reversed_sagittal )
	.value ( "CORONAL", isis::data::Image::coronal )
	.value ( "REVERSED_CORONAL", isis::data::Image::reversed_coronal )
	;
	//#######################################################################################
	//  enums for dimensions
	//#######################################################################################
	enum_<isis::data::dimensions> ( "dimensions" )
	.value ( "ROW_DIM", rowDim )
	.value ( "COLUMN_DIM", columnDim )
	.value ( "SLICE_DIM", sliceDim )
	.value ( "TIME_DIM", timeDim )
	;




}
#endif
