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

class _Image : public Image, public boost::python::wrapper<Image>
{

public:

	_Image ( PyObject *p );
	_Image ( PyObject *p, const Image &base );

	boost::shared_ptr<data::Chunk> contiguousChunk_;

	template<typename TYPE>
	void makeContiguousChunk() {
		contiguousChunk_ = boost::shared_ptr<data::Chunk>( new data::Chunk( copyAsMemChunk<TYPE>() ) );
	}
	
private:
	PyObject *self;
};

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
namespace Image
{

api::object _voxel ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );
api::object _voxel ( const isis::data::Image &base, const isis::util::ivector4 &coord );

bool _setVoxel ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );
bool _setVoxel ( const isis::data::Image &base, const isis::util::ivector4 &coord, const api::object &value );

list _getChunksAsVector ( const isis::data::Image &base );


Chunk _getChunk ( const isis::data::Image &base, const isis::util::ivector4 &coord, bool copy_metadata );

Chunk _getChunkAs ( const isis::data::Image &base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const isis::python::data::image_types &type );
Chunk _getChunkAs ( const isis::data::Image &base, const isis::util::ivector4 &coord, const isis::python::data::image_types &type  );

api::object _getMin( const isis::data::Image &base );
api::object _getMax( const isis::data::Image &base );

std::string _getMainOrientationAsString( const isis::data::Image &base );

void _transformCoords ( isis::data::Image &base, boost::python::list matrix, const bool &center );

bool _convertToType ( isis::data::Image &base, isis::python::data::image_types type );

size_t _spliceDownTo ( isis::data::Image &base, const isis::data::dimensions dims );

isis::data::Image _deepCopy( const isis::data::Image &base );

isis::data::Image _deepCopyAs ( const isis::data::Image &base, isis::python::data::image_types type );

isis::data::Image _cheapCopy ( const isis::data::Image &base );

numeric::array _getArray ( isis::python::data::_Image& base );
numeric::array _getArray( isis::python::data::_Image &base, isis::python::data::image_types image_type = isis::python::data::DOUBLE );

isis::data::Image _createImage ( isis::python::data::image_types type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );
isis::data::Image _createImageFromChunks( const list &chunks );

isis::data::Image _createFromArray( const boost::python::numeric::array &arr);
isis::data::Image _createFromArray(  const boost::python::numeric::array &arr, const isis::data::Image &image );



}


}
}
}

#endif /* _IMAGE_HPP_ */
