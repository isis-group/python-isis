#include "_chunk.hpp"
#include "VoxelOp.hpp"
#include <numpy/oldnumeric.h>

namespace isis
{
namespace python
{
namespace data
{

_Chunk::_Chunk ( PyObject *p, const Chunk &base )
	: Chunk( base ), boost::python::wrapper< isis::data::Chunk >(), self( p )
{}

_Chunk::_Chunk ( PyObject *p, const numeric::array &array )
	: boost::python::wrapper< isis::data::Chunk >(), self( p )
{
	*this = _Chunk( p, isis::python::data::Chunk::_createFromArray( array ) );
}

_Chunk::_Chunk ( PyObject *p, const numeric::array &array, const isis::data::Chunk &chunk )
	: boost::python::wrapper< isis::data::Chunk >(), self( p )
{
	*this = _Chunk( p, isis::python::data::Chunk::_createFromArray( array, chunk ) );
}


namespace Chunk
{

object _voxel ( const isis::data::Chunk &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	const unsigned int typeID = base.getTypeID();
	return isis::python::data::VoxelOp::getVoxelAsPyObject( base, typeID, first, second, third, fourth );
}

object _voxel ( const isis::data::Chunk &base, const isis::util::ivector4 &coord )
{
	return _voxel( base, coord[0], coord[1], coord[2], coord[3] );
}

object _voxelAs ( const isis::data::Chunk &base, const image_types &type, const isis::util::ivector4 &coord )
{
	return isis::python::data::VoxelOp::getVoxelAsPyObject( base, static_cast<unsigned int>( type ), coord[0], coord[1], coord[2], coord[3] );
}

object _voxelAs ( const isis::data::Chunk &base, const image_types &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	return isis::python::data::VoxelOp::getVoxelAsPyObject( base, static_cast<unsigned int>( type ), first, second, third, fourth );
}

object _voxelAs ( const isis::data::Chunk &base, const int &type, const isis::util::ivector4 &coord )
{
	return _voxelAs( base, static_cast<isis::python::data::image_types>( type ), coord );
}

object _voxelAs ( const isis::data::Chunk &base, const int &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	return isis::python::data::VoxelOp::getVoxelAsPyObject( base, type, first, second, third, fourth );
}

bool _setVoxel( isis::data::Chunk &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value )
{
	const unsigned int typeID = base.getTypeID();
	return isis::python::data::VoxelOp::setVoxelAsPyObject( base, typeID, first, second, third, fourth, value );
}

bool _setVoxel ( isis::data::Chunk &base, const isis::util::ivector4 &coord, const object &value )
{
	return _setVoxel( base, coord[0], coord[1], coord[2], coord[3], value );
}

bool _setVoxelAs ( isis::data::Chunk &base, const isis::python::data::image_types &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const object &value )
{
	return isis::python::data::VoxelOp::setVoxelAsPyObject( base, static_cast<unsigned int>( type ), first, second, third, fourth, value );
}

bool _setVoxelAs ( isis::data::Chunk &base, const isis::python::data::image_types &type, const isis::util::ivector4 &coord, const object &value )
{
	return isis::python::data::VoxelOp::setVoxelAsPyObject( base, static_cast<unsigned int>( type ), coord[0], coord[1], coord[2], coord[3], value );
}

bool _setVoxelAs ( isis::data::Chunk &base, const int &type, const isis::util::ivector4 &coord, const object &value )
{
	return _setVoxelAs( base, static_cast<isis::python::data::image_types>( type ), coord, value );
}

bool _setVoxelAs ( isis::data::Chunk &base, const int &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const object &value )
{
	return _setVoxelAs( base, static_cast<isis::python::data::image_types>( type ), first, second, third, fourth, value );
}

bool _convertToType( isis::data::Chunk &base, const unsigned short ID )
{
	return base.convertToType( ID );
}

bool _convertToType ( isis::data::Chunk &base, const short unsigned int ID, float scaling, size_t offset )
{
	return base.convertToType( ID, std::make_pair<isis::util::Value<float>, isis::util::Value<size_t> >( scaling, offset ) );
}

object _getMax( const isis::data::Chunk &base )
{
	const isis::util::ValueReference min = base.getMinMax().first;
	return  isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				min->getTypeID() )->convert ( *min );
}


object _getMin( const isis::data::Chunk &base )
{
	const isis::util::ValueReference max = base.getMinMax().second;
	return  isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				max->getTypeID() )->convert ( *max );
}

object _getMinMax ( const isis::data::Chunk &base )
{
	const std::pair< isis::util::ValueReference, isis::util::ValueReference> minMax = base.getMinMax();
	object min = isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
					 minMax.first->getTypeID() )->convert ( *minMax.first );
	object max = isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
					 minMax.second->getTypeID() )->convert ( *minMax.second );

	return boost::python::make_tuple( min, max );
}

isis::data::Chunk _createFromArray ( const numeric::array &arr )
{
	import_array();
	const boost::python::object shape = arr.attr( "shape" );
	const boost::python::ssize_t len = boost::python::len( shape );
	isis::util::ivector4 size( 1, 1, 1, 1 );

	for ( boost::python::ssize_t i = 0; i < len; i++ ) {
		size[i] = boost::python::extract<int32_t>( shape[i] );
	}

	switch( PyArray_TYPE( arr.ptr() ) ) {
	case NPY_FLOAT: {
		isis::data::MemChunk<float>ch( ( float * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<float>( ch );
		break;
	}
	case NPY_DOUBLE: {
		isis::data::MemChunk<double>ch( ( double * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<double>( ch );
		break;
	}
	case NPY_INT8: {
		isis::data::MemChunk<int8_t>ch( ( int8_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<int8_t>( ch );
		break;
	}
	case NPY_UINT8: {
		isis::data::MemChunk<uint8_t>ch( ( uint8_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<uint8_t>( ch );
		break;
	}
	case NPY_INT16: {
		isis::data::MemChunk<int16_t>ch( ( int16_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<int16_t>( ch );
		break;
	}
	case NPY_UINT16: {
		isis::data::MemChunk<uint16_t>ch( ( uint16_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<uint16_t>( ch );
		break;
	}
	case NPY_INT32: {
		isis::data::MemChunk<int32_t>ch( ( int32_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<int32_t>( ch );
		break;
	}
	case NPY_UINT32: {
		isis::data::MemChunk<uint32_t>ch( ( uint32_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<uint32_t>( ch );
		break;
	}
	case NPY_INT64: {
		isis::data::MemChunk<int64_t>ch( ( int64_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<int64_t>( ch );
		break;
	}
	case NPY_UINT64: {
		isis::data::MemChunk<uint64_t>ch( ( uint64_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<uint64_t>( ch );
		break;
	}
	case NPY_BOOL: {
		isis::data::MemChunk<bool>ch( ( bool * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<bool>( ch );
		break;
	}
	case NPY_CFLOAT: {
		isis::data::MemChunk<std::complex< float > >ch( ( std::complex< float > * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<std::complex< float > >( ch );
		break;
	}
	case NPY_CDOUBLE: {
		isis::data::MemChunk<std::complex< double > >ch( ( std::complex< double > * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::VoxelOp::getSwappedChunk<std::complex< double > >( ch );
		break;
	}
	default:
		LOG( isis::python::data::Runtime, error ) << "Unregistered datatype: " << PyArray_TYPE( arr.ptr() ) << ". Returning empty chunk of type double.";
		return isis::data::MemChunk<double>( size[3], size[2], size[1], size[0] );
	}
}

isis::data::Chunk _createFromArray ( const numeric::array &arr, const isis::data::Chunk &chunk )
{
	isis::data::Chunk retChunk = _createFromArray( arr );
	retChunk.join( chunk, true );
	return retChunk;
}

numeric::array _getArray ( _Chunk &base )
{
	return _getArray( base, static_cast<isis::python::data::image_types>( base.getTypeID() ) );
}

numeric::array _getArray ( _Chunk &base, image_types image_type )
{
	import_array()
	const isis::util::ivector4 size = base.getSizeAsVector();
	const size_t relDims = base.getRelevantDims();
	npy_intp dims[relDims];

	for( size_t i = 0; i < relDims; i++ ) {
		dims[i] = size[i];
	}

	switch( image_type ) {
	case isis::python::data::DOUBLE: {
		base.makeContiguousChunk<double>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_DOUBLE, &base.contiguousChunkList_.back()->voxel<double>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::FLOAT: {
		base.makeContiguousChunk<float>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_FLOAT, &base.contiguousChunkList_.back()->voxel<float>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::INT8_T: {
		base.makeContiguousChunk<int8_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_INT8, &base.contiguousChunkList_.back()->voxel<int8_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::UINT8_T: {
		base.makeContiguousChunk<uint8_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_UINT8, &base.contiguousChunkList_.back()->voxel<uint8_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::INT16_T: {
		base.makeContiguousChunk<int16_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_INT16, &base.contiguousChunkList_.back()->voxel<int16_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::UINT16_T: {
		base.makeContiguousChunk<uint16_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_UINT16, &base.contiguousChunkList_.back()->voxel<uint16_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::INT32_T: {
		base.makeContiguousChunk<int32_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_INT32, &base.contiguousChunkList_.back()->voxel<int32_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::UINT32_T: {
		base.makeContiguousChunk<uint32_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_UINT32, &base.contiguousChunkList_.back()->voxel<uint32_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::INT64_T: {
		base.makeContiguousChunk<int64_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_INT64, &base.contiguousChunkList_.back()->voxel<int64_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::UINT64_T: {
		base.makeContiguousChunk<uint64_t>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_UINT64, &base.contiguousChunkList_.back()->voxel<uint64_t>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::BOOL: {
		base.makeContiguousChunk<bool>();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_BOOL, &base.contiguousChunkList_.back()->voxel<bool>( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::CFLOAT: {
		base.makeContiguousChunk<std::complex< float > >();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_CFLOAT, &base.contiguousChunkList_.back()->voxel< std::complex< float > >( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	case isis::python::data::CDOUBLE: {
		base.makeContiguousChunk<std::complex< double > >();
		const boost::python::object obj( boost::python::handle<>( PyArray_SimpleNewFromData( relDims, dims, NPY_CDOUBLE, &base.contiguousChunkList_.back()->voxel< std::complex< double > >( 0 ) ) ) );
		return boost::python::extract<boost::python::numeric::array>( obj );
		break;
	}
	}
}

isis::util::PropertyMap _getProperties ( const isis::data::Chunk &base )
{
	return static_cast<const isis::util::PropertyMap &>( base );
}

std::string _toString ( const isis::data::Chunk &base )
{
	std::stringstream output;
	output << "ISIS Chunk of size: " << base.getSizeAsString() << " and type: " << base.getTypeName();
	return output.str();
}




}

}
}
}