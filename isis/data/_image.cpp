#include "_image.hpp"

namespace isis
{
namespace python
{
namespace data
{


_Image::_Image ( PyObject *p )
	: boost::python::wrapper< Image >(), self ( p )
{
	updateOrientationMatrices();
}

_Image::_Image ( PyObject *p, const isis::data::Image &base )
	: Image ( base ), boost::python::wrapper< Image >(), self ( p )
{
	updateOrientationMatrices();
}

namespace Image
{

api::object _voxel ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	const Chunk &ch = base.getChunk ( first, second, third, fourth, false );
	return isis::python::data::_internal::VoxelOp::getVoxelAsPyObject ( ch, first, second, third, fourth );
}

object _voxel ( const isis::data::Image &base, const util::ivector4 &coord )
{
	return _voxel ( base, coord[0], coord[1], coord[2], coord[3] );
}

bool _setVoxel ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value )
{
	Chunk ch = base.getChunk ( first, second, third, fourth, false );
	return isis::python::data::_internal::VoxelOp::setVoxelAsPyObject ( ch, first, second, third, fourth, value );
}

bool _setVoxel ( const isis::data::Image &base, const util::ivector4 &coord, const object &value )
{
	return _setVoxel ( base, coord[0], coord[1], coord[2], coord[3], value );
}

list _getChunksAsVector ( const isis::data::Image &base )
{
	return isis::python::data::_internal::stdIter2PyList<std::vector<Chunk> >( base.copyChunksToVector() );
}

Chunk _getChunk ( const isis::data::Image &base, const util::ivector4 &coord, bool copy_metadata )
{
	return base.getChunk ( coord[0], coord[1], coord[2], coord[3], copy_metadata );
}

Chunk _getChunkAs ( const isis::data::Image &base, const util::ivector4 &coord, const image_types &type )
{
	return _getChunkAs ( base, coord[0], coord[1], coord[2], coord[3], type );
}

Chunk _getChunkAs ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const isis::python::data::image_types &type )
{
	Chunk ret = base.getChunk ( first, second, third, fourth ); // get a cheap copy
	ret.convertToType ( type );
	return ret;
}

object _getMin ( const isis::data::Image &base )
{
	const util::ValueReference min = base.getMinMax().first;
	return  util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				min->getTypeID() )->convert ( *min );
}

object _getMax ( const isis::data::Image &base )
{
	const util::ValueReference max = base.getMinMax().second;
	return  util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				max->getTypeID() )->convert ( *max );
}

std::string _getMainOrientationAsString( const isis::data::Image &base )
{
	switch ( base.getMainOrientation() ) {
	case isis::data::Image::sagittal:
		return std::string ( "sagittal" );
		break;
	case isis::data::Image::reversed_sagittal:
		return std::string ( "reversed_sagittal" );
		break;
	case isis::data::Image::axial:
		return std::string ( "axial" );
		break;
	case isis::data::Image::reversed_axial:
		return std::string ( "reversed_axial" );
		break;
	case isis::data::Image::coronal:
		return std::string ( "coronal" );
		break;
	case isis::data::Image::reversed_coronal:
		return std::string ( "reversed_coronal" );
		break;
	default:
		return std::string ( "unknown" );
		break;
	}
}


void _transformCoords ( isis::data::Image &base, boost::python::list matrix, const bool &center )
{
	std::vector< boost::python::list > rows;

	for ( boost::python::ssize_t i = 0; i < boost::python::len ( matrix ); ++i ) {
		rows.push_back ( boost::python::extract< boost::python::list > ( matrix[i] ) );
	}

	boost::numeric::ublas::matrix<float> boostMatrix ( 3, 3 );

	for ( unsigned short i = 0; i < 3; i++ ) {
		for ( unsigned short j = 0; j < 3; j++ ) {
			boostMatrix ( i, j ) = boost::python::extract<float> ( rows[i][j] );
		}
	}

	base.transformCoords ( boostMatrix, center );
}

bool _convertToType ( isis::data::Image &base, image_types type )
{
	return base.convertToType ( static_cast<unsigned short> ( type ) );
}

size_t _spliceDownTo ( isis::data::Image &base, const isis::data::dimensions dims )
{
	return base.spliceDownTo ( dims );
}

isis::data::Image _deepCopy( const isis::data::Image &base )
{
	switch ( base.getMajorTypeID() ) {
	case ValueArray<int8_t>::staticID:
		return MemImage<int8_t> ( base );
		break;
	case ValueArray<uint8_t>::staticID:
		return MemImage<uint8_t> ( base );
		break;
	case ValueArray<int16_t>::staticID:
		return MemImage<int16_t> ( base );
		break;
	case ValueArray<uint16_t>::staticID:
		return MemImage<uint16_t> ( base );
		break;
	case ValueArray<int32_t>::staticID:
		return MemImage<int32_t> ( base );
		break;
	case ValueArray<uint32_t>::staticID:
		return MemImage<uint32_t> ( base );
		break;
	case ValueArray<float>::staticID:
		return MemImage<float> ( base );
		break;
	case ValueArray<double>::staticID:
		return MemImage<double> ( base );
		break;
	default:
		LOG ( Runtime, error ) << "Unregistered pixel type " << util::getTypeMap() [base.getMajorTypeID()] << ".";
		return MemImage<int8_t> ( base );
	}
}

isis::data::Image _deepCopyAs ( const isis::data::Image &base, image_types type )
{
	isis::data::Image retImage = Image::_deepCopy( base );
	retImage.convertToType ( static_cast<unsigned short> ( type ) );

	return retImage;
}


isis::data::Image _createImage ( image_types type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	switch ( type ) {
	case BOOL:
		return _internal::_internCreateImage<bool> ( first, second, third, fourth ) ;
		break;
	case INT8_T:
		return _internal::_internCreateImage<int8_t> ( first, second, third, fourth ) ;
		break;
	case UINT8_T:
		return _internal::_internCreateImage<uint8_t> ( first, second, third, fourth ) ;
		break;
	case INT16_T:
		return _internal::_internCreateImage<int16_t> ( first, second, third, fourth );
		break;
	case UINT16_T:
		return _internal::_internCreateImage<uint16_t> ( first, second, third, fourth );
		break;
	case INT32_T:
		return _internal::_internCreateImage<int32_t> ( first, second, third, fourth );
		break;
	case UINT32_T:
		return _internal::_internCreateImage<uint32_t> ( first, second, third, fourth );
		break;
	case INT64_T:
		return _internal::_internCreateImage<int64_t> ( first, second, third, fourth );
		break;
	case UINT64_T:
		return _internal::_internCreateImage<uint64_t> ( first, second, third, fourth );
		break;
	case FLOAT:
		return _internal::_internCreateImage<float> ( first, second, third, fourth );
		break;
	case DOUBLE:
		return _internal::_internCreateImage<double> ( first, second, third, fourth );
		break;
	default:
		LOG ( Runtime, error ) << "Unregistered pixel type ";
		break;
	}
	return isis::data::Image ( isis::data::MemChunk<bool> ( 0, 0, 0, 0 ) );
}

isis::data::Image _cheapCopy ( const isis::data::Image &base )
{
	return base;
}

isis::data::Image _createImageFromChunks ( const list& chunks )
{
	std::list<isis::data::Chunk> chunkList = isis::python::data::_internal::pyList2StdList<isis::data::Chunk>( chunks );
	return isis::data::Image( chunkList );
}

numeric::array _getArray()
{
	
}




}
}
}
}
