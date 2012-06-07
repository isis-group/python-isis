#include "_image.hpp"
#include <numpy/oldnumeric.h>

#ifdef ISIS_PYTHON_MUPARSER_SUPPORT
#include <muParser.h>
#endif
namespace isis
{
namespace python
{
namespace data
{

_Image::_Image ( PyObject *p, const isis::data::Image &base )
	: Image ( base ), boost::python::wrapper< Image >(), self ( p )
{
	updateOrientationMatrices();
}

_Image::_Image ( PyObject* p, const boost::python::numeric::array& array )
	:boost::python::wrapper< Image >(), self( p )
{
	*this = _Image( p, isis::python::data::Image::_createFromArray( array ) );
	updateOrientationMatrices();

}

_Image::_Image ( PyObject* p, const numeric::array& array, const isis::data::Image& image )
	:boost::python::wrapper< Image >(), self( p )
{
	*this = _Image( p, isis::python::data::Image::_createFromArray( array, image ) );
	updateOrientationMatrices();
}


namespace Image
{

#ifdef ISIS_PYTHON_MUPARSER_SUPPORT
class VoxelOp : public isis::data::VoxelOp<double>
{
	mu::Parser parser;
	double voxBuff;
	isis::util::FixedVector<double, 4> posBuff;
public:
	VoxelOp( std::string expr ) {
		parser.SetExpr( expr );
		parser.DefineVar( std::string( "vox" ), &voxBuff );
		parser.DefineVar( std::string( "pos_x" ), &posBuff[data::rowDim] );
		parser.DefineVar( std::string( "pos_y" ), &posBuff[data::columnDim] );
		parser.DefineVar( std::string( "pos_z" ), &posBuff[data::sliceDim] );
		parser.DefineVar( std::string( "pos_t" ), &posBuff[data::timeDim] );
	}
	bool operator()( double &vox, const isis::util::vector4<size_t>& pos ) {
		voxBuff = vox; //using parser.DefineVar every time would slow down the evaluation
		posBuff = pos;
		vox = parser.Eval();
		return true;
	}

};

bool _applyOperation( isis::data::Image &base, const std::string &operation ) {
	try {
		VoxelOp vop( operation );
		base.foreachVoxel<double>( vop );
	} catch( mu::Parser::exception_type &e ) {
		std::cerr << e.GetMsg() << std::endl;
		return false;
	}
	return true;
}

#endif
	
api::object _voxel ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	const unsigned int typeID = base.getChunk ( first, second, third, fourth, false ).getTypeID();
	return isis::python::data::_internal::VoxelOp::getVoxelAsPyObject( base, typeID, first, second, third, fourth );
}

object _voxel ( const isis::data::Image &base, const util::ivector4 &coord )
{
	return _voxel ( base, coord[0], coord[1], coord[2], coord[3] );
}

object _voxelAs ( const isis::data::Image& base, const image_types& type, const isis::util::ivector4& coord )
{
	return isis::python::data::_internal::VoxelOp::getVoxelAsPyObject( base, static_cast<unsigned int>( type ), coord[0], coord[1], coord[2], coord[3] );
}

object _voxelAs ( const isis::data::Image& base, const image_types& type, const size_t& first, const size_t& second, const size_t& third, const size_t& fourth )
{
	return isis::python::data::_internal::VoxelOp::getVoxelAsPyObject( base, static_cast<unsigned int>( type ), first, second, third, fourth );
}

object _voxelAs ( const isis::data::Image& base, const int& type, const util::ivector4& coord )
{
	return _voxelAs( base, static_cast<isis::python::data::image_types>( type ), coord );
}

object _voxelAs ( const isis::data::Image& base, const int& type, const size_t& first, const size_t& second, const size_t& third, const size_t& fourth )
{
	return isis::python::data::_internal::VoxelOp::getVoxelAsPyObject( base, type, first, second, third, fourth );
}

bool _setVoxel ( isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value )
{
	const unsigned int typeID = base.getChunk ( first, second, third, fourth, false ).getTypeID();
	return isis::python::data::_internal::VoxelOp::setVoxelAsPyObject( base, typeID, first, second, third, fourth, value );
}

bool _setVoxel ( isis::data::Image &base, const util::ivector4 &coord, const object &value )
{
	return _setVoxel ( base, coord[0], coord[1], coord[2], coord[3], value );
}

bool _setVoxelAs ( isis::data::Image& base, const isis::python::data::image_types& type, const size_t& first, const size_t& second, const size_t& third, const size_t& fourth, const object& value )
{
	return isis::python::data::_internal::VoxelOp::setVoxelAsPyObject( base, static_cast<unsigned int>( type ), first, second, third, fourth, value );
}

bool _setVoxelAs ( isis::data::Image& base, const isis::python::data::image_types& type, const util::ivector4& coord, const object& value )
{
	return isis::python::data::_internal::VoxelOp::setVoxelAsPyObject( base, static_cast<unsigned int>( type ), coord[0], coord[1], coord[2], coord[3], value );
}

bool _setVoxelAs ( isis::data::Image& base, const int& type, const util::ivector4& coord, const object& value )
{
	return _setVoxelAs( base, static_cast<isis::python::data::image_types>( type ), coord, value );
}

bool _setVoxelAs ( isis::data::Image& base, const int& type, const size_t& first, const size_t& second, const size_t& third, const size_t& fourth, const object& value )
{
	return _setVoxelAs( base, static_cast<isis::python::data::image_types>( type ), first, second, third, fourth, value );
}


list _getChunksAsVector ( const isis::data::Image &base )
{
	return isis::python::data::_internal::stdIter2PyList<std::vector<isis::data::Chunk> >( base.copyChunksToVector() );
}

isis::data::Chunk _getChunk ( const isis::data::Image &base, const util::ivector4 &coord, bool copy_metadata )
{
	return base.getChunk ( coord[0], coord[1], coord[2], coord[3], copy_metadata );
}

isis::data::Chunk _getChunkAs ( const isis::data::Image &base, const util::ivector4 &coord, const image_types &type )
{
	return _getChunkAs ( base, coord[0], coord[1], coord[2], coord[3], type );
}

isis::data::Chunk _getChunkAs ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const isis::python::data::image_types &type )
{
	isis::data::Chunk ret = base.getChunk ( first, second, third, fourth ); // get a cheap copy
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

object _getMinMax ( const isis::data::Image& base )
{
	const std::pair< isis::util::ValueReference, isis::util::ValueReference> minMax = base.getMinMax();
	object min = isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				minMax.first->getTypeID() )->convert ( *minMax.first );
	object max = isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				minMax.second->getTypeID() )->convert ( *minMax.second );
				
	return boost::python::make_tuple(min, max);
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
	case ValueArray<bool>::staticID:
		return MemImage<bool> ( base );
		break;
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
	case ValueArray<int64_t>::staticID:
		return MemImage<int64_t> ( base );
		break;
	case ValueArray<uint64_t>::staticID:
		return MemImage<uint64_t> ( base );
		break;
	case ValueArray<float>::staticID:
		return MemImage<float> ( base );
		break;
	case ValueArray<double>::staticID:
		return MemImage<double> ( base );
		break;
	case ValueArray<std::complex<float> >::staticID:
		return MemImage<std::complex<float> > ( base );
		break;
	case ValueArray<std::complex<double> >::staticID:
		return MemImage<std::complex<double> > ( base );
		break;
	case ValueArray<isis::util::color24>::staticID:
		return MemImage<isis::util::color24> ( base );
		break;
	case ValueArray<isis::util::color48>::staticID:
		return MemImage<isis::util::color48> ( base );
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
	case CFLOAT:
		return _internal::_internCreateImage<std::complex<float> > ( first, second, third, fourth );
		break;
	case CDOUBLE:
		return _internal::_internCreateImage<std::complex<double> > ( first, second, third, fourth );
		break;
	case COLOR_24:
		return _internal::_internCreateImage< isis::util::color24 > ( first, second, third, fourth );
		break;
	case COLOR_48:
		return _internal::_internCreateImage< isis::util::color48 > ( first, second, third, fourth );
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

isis::data::Image _createImageFromChunks ( const list &chunks )
{
	std::list<isis::data::Chunk> chunkList = isis::python::data::_internal::pyList2StdList<isis::data::Chunk>( chunks );
	return isis::data::Image( chunkList );
}

numeric::array _getArray ( _Image &base )
{
	return _getArray( base, static_cast<isis::python::data::image_types>( base.getMajorTypeID() ) );
}


numeric::array _getArray( isis::python::data::_Image &base, isis::python::data::image_types image_type )
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


isis::data::Image _createFromArray( const boost::python::numeric::array &arr )
{
	import_array();
	const boost::python::object shape = arr.attr( "shape" );
	const boost::python::ssize_t len = boost::python::len( shape );
	util::ivector4 size( 1, 1, 1, 1 );
	unsigned short count = len;
	for ( boost::python::ssize_t i = 0; i < len; i++ ) {
		size[i] = boost::python::extract<int32_t>( shape[i] );
	}

	switch( PyArray_TYPE( arr.ptr() ) ) {
	case NPY_FLOAT: {
		isis::data::MemChunk<float>ch( ( float * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<float>(ch);
		break;
	}
	case NPY_DOUBLE: {
		isis::data::MemChunk<double>ch( ( double * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<double>(ch);
		break;
	}
	case NPY_INT8: {
		isis::data::MemChunk<int8_t>ch( ( int8_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<int8_t>(ch);
		break;
	}
	case NPY_UINT8: {
		isis::data::MemChunk<uint8_t>ch( ( uint8_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<uint8_t>(ch);
		break;
	}
	case NPY_INT16: {
		isis::data::MemChunk<int16_t>ch( ( int16_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<int16_t>(ch);
		break;
	}
	case NPY_UINT16: {
		isis::data::MemChunk<uint16_t>ch( ( uint16_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<uint16_t>(ch);
		break;
	}
	case NPY_INT32: {
		isis::data::MemChunk<int32_t>ch( ( int32_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<int32_t>(ch);
		break;
	}
	case NPY_UINT32: {
		isis::data::MemChunk<uint32_t>ch( ( uint32_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<uint32_t>(ch);
		break;
	}
	case NPY_INT64: {
		isis::data::MemChunk<int64_t>ch( ( int64_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<int64_t>(ch);
		break;
	}
	case NPY_UINT64: {
		isis::data::MemChunk<uint64_t>ch( ( uint64_t * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<uint64_t>(ch);
		break;
	}
	case NPY_BOOL: {
		isis::data::MemChunk<bool>ch( ( bool * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<bool>(ch);
		break;
	}
	case NPY_CFLOAT: {
		isis::data::MemChunk<std::complex< float > >ch( ( std::complex< float > * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<std::complex< float > >(ch);
		break;
	}
	case NPY_CDOUBLE: {
		isis::data::MemChunk<std::complex< double > >ch( ( std::complex< double > * )PyArray_DATA( arr.ptr() ), size[3], size[2], size[1], size[0] );
		return isis::python::data::_Image::swappedChunk2Image<std::complex< double > >(ch);
		break;
	}
	default:
		LOG( isis::python::Runtime, error ) << "Unregistered datatype: " << PyArray_TYPE( arr.ptr() ) << ". Returning empty image of type double.";
		return _createImage( DOUBLE, size[3], size[2], size[1], size[0] );
	}
}


isis::data::Image _createFromArray ( const numeric::array &arr, const isis::data::Image &image )
{
	isis::data::Image retImage = _createFromArray( arr );
	retImage.join( image, true );
	return retImage;
}


} // end namespace Image
void _internal::setInitialProperties ( isis::data::Chunk &ch )
{
	const util::ivector4 size = ch.getSizeAsVector();
	ch.setPropertyAs<uint32_t> ( "acquisitionNumber", 0 );
	ch.setPropertyAs<uint16_t> ( "sequenceNumber", 0 );
	ch.setPropertyAs<util::fvector4> ( "rowVec", util::fvector4 ( 1, 0, 0, 0 ) );
	ch.setPropertyAs<util::fvector4> ( "columnVec", util::fvector4 ( 0, 1, 0, 0 ) );
	ch.setPropertyAs<util::fvector4> ( "sliceVec", util::fvector4 ( 0, 0, 1, 0 ) );
	ch.setPropertyAs<util::fvector4> ( "voxelSize", util::fvector4 ( 1, 1, 1, 1 ) );
	ch.setPropertyAs<util::fvector4> ( "indexOrigin", util::fvector4 ( size[0] / 2 - 0.5, size[1] / 2 - 0.5, size[2] / 2 - 0.5, 0 ) );
}

}
}
}
