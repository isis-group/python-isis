/*
 * _image.hpp
 *
 *  Created on: Oct 19, 2010
 *      Author: tuerke
 */

#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include "_types.hpp"
#include "DataStorage/image.hpp"
#include "CoreUtils/vector.hpp"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/python/numeric.hpp>
#include "util/common.hpp"
#include "common.hpp"
#include "util/_convertToPython.hpp"

#include "util/_propmap.hpp"
#include "DataStorage/chunk.hpp"
#include "CoreUtils/singletons.hpp"


namespace isis
{
namespace python
{
namespace data
{
namespace _internal
{
void setInitialProperties( isis::data::Chunk &chunk );

template<typename TYPE>
static isis::data::Image _internCreateImage ( const size_t &first, const size_t &second, const size_t &third, const size_t &fourth )
{
	isis::data::MemChunk<TYPE> chunk ( first, second, third, fourth );
	setInitialProperties ( chunk );
	return isis::data::Image ( chunk );
}
}
class _Image : public Image, public boost::python::wrapper<Image>
{

public:

	_Image ( PyObject *p, const Image &base );
    _Image ( PyObject *p, const boost::python::numeric::array &array );
	_Image ( PyObject *p, const boost::python::numeric::array &array, const isis::data::Image &image );

	std::list<boost::shared_ptr<isis::data::Chunk> > contiguousChunkList_;

	template<typename TYPE>
	void makeContiguousChunk() {
		const isis::data::TypedImage<TYPE> tImage( *this );
		const util::ivector4 size = getSizeAsVector();
		isis::data::MemChunk<TYPE> mChunk( size[3], size[2], size[1], size[0] );
		typedef util::ivector4::value_type value_type;
		for ( value_type t = 0; t < size[3]; t++ ) {
			for ( value_type z = 0; z < size[2]; z++ ) {
				for ( value_type y = 0; y < size[1]; y++ ) {
					for ( value_type x = 0; x < size[0]; x++ ) {
						static_cast<isis::data::Chunk&>( mChunk ).voxel<TYPE>(t,z,y,x) =
							static_cast<const isis::data::Image&>( tImage ).voxel<TYPE>(x,y,z,t);
						
					}
				}
			}
		}
		contiguousChunkList_.push_back( boost::shared_ptr<isis::data::Chunk>( new isis::data::Chunk( mChunk ) ) );
	}

	template<typename TYPE>
	static isis::data::Image swappedChunk2Image( const isis::data::Chunk &ch ) {
		const isis::util::ivector4 size = ch.getSizeAsVector();
		isis::data::MemChunk<TYPE> mChunk ( size[3], size[2], size[1], size[0] );
		typedef isis::util::ivector4::value_type value_type;
		for ( value_type t = 0; t < size[3]; t++ ) {
			for ( value_type z = 0; z < size[2]; z++ ) {
				for ( value_type y = 0; y < size[1]; y++ ) {
					for ( value_type x = 0; x < size[0]; x++ ) {
						static_cast<isis::data::Chunk&>( mChunk ).voxel<TYPE>(t,z,y,x) =
							ch.voxel<TYPE>(x,y,z,t);
					}
				}
			}
		}
		isis::python::data::_internal::setInitialProperties( mChunk );
		return isis::data::Image( mChunk );
	}
	
private:
	PyObject *self;
};


namespace Image
{

#ifdef ISIS_PYTHON_MUPARSER_SUPPORT
bool _applyOperation( isis::data::Image &base, const std::string &operation );
#endif

	
api::object _voxel ( const isis::data::Image &base, const isis::util::ivector4 &coord );
api::object _voxel ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );

api::object _voxelAs ( const isis::data::Image &base, const isis::python::data::image_types &type, const isis::util::ivector4 &coord );
api::object _voxelAs ( const isis::data::Image &base, const isis::python::data::image_types &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );
api::object _voxelAs ( const isis::data::Image &base, const int &type, const isis::util::ivector4 &coord );
api::object _voxelAs ( const isis::data::Image &base, const int &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );


bool _setVoxel ( isis::data::Image &base, const isis::util::ivector4 &coord, const api::object &value );
bool _setVoxel ( isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );

bool _setVoxelAs( isis::data::Image &base, const isis::python::data::image_types &type, const isis::util::ivector4 &coord, const api::object &value );
bool _setVoxelAs( isis::data::Image &base, const isis::python::data::image_types &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );
bool _setVoxelAs( isis::data::Image &base, const int &type, const isis::util::ivector4 &coord, const api::object &value );
bool _setVoxelAs( isis::data::Image &base, const int &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );

list _getChunksAsVector ( const isis::data::Image &base );


isis::data::Chunk _getChunk ( const isis::data::Image &base, const isis::util::ivector4 &coord, bool copy_metadata );

isis::data::Chunk _getChunkAs ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const isis::python::data::image_types &type );
isis::data::Chunk _getChunkAs ( const isis::data::Image &base, const isis::util::ivector4 &coord, const isis::python::data::image_types &type  );

api::object _getMin( const isis::data::Image &base );
api::object _getMax( const isis::data::Image &base );

api::object _getMinMax( const isis::data::Image &base );

std::string _getMainOrientationAsString( const isis::data::Image &base );

void _transformCoords ( isis::data::Image &base, boost::python::list matrix, const bool &center );

bool _convertToType ( isis::data::Image &base, isis::python::data::image_types type );

size_t _spliceDownTo ( isis::data::Image &base, const isis::data::dimensions dims );

isis::data::Image _deepCopy( const isis::data::Image &base );

isis::data::Image _deepCopyAs ( const isis::data::Image &base, isis::python::data::image_types type );

isis::data::Image _cheapCopy ( const isis::data::Image &base );

numeric::array _getArray ( isis::python::data::_Image &base );
numeric::array _getArray( isis::python::data::_Image &base, isis::python::data::image_types image_type = isis::python::data::DOUBLE );

isis::data::Image _createImage ( isis::python::data::image_types type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );
isis::data::Image _createImageFromChunks( const list &chunks );


isis::data::Image _createFromArray( const boost::python::numeric::array &arr );
isis::data::Image _createFromArray(  const boost::python::numeric::array &arr, const isis::data::Image &image );



}


}
}
}

#endif /* _IMAGE_HPP_ */
