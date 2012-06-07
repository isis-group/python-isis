/*
 * _chunk.hpp
 *
 *  Created on: Oct 21, 2010
 *      Author: tuerke
 */

#ifndef ISIS_PYTHON_CHUNK_HPP_
#define ISIS_PYTHON_CHUNK_HPP_

#include "DataStorage/chunk.hpp"
#include <boost/python.hpp>
#include "util/_convertToPython.hpp"
#include "_types.hpp"

using namespace isis::data;

namespace isis
{
namespace python
{
namespace data
{

class _Chunk : public Chunk, boost::python::wrapper<Chunk>
{
public:
	_Chunk ( PyObject *p, const Chunk &base );
	_Chunk ( PyObject *p, const boost::python::numeric::array &array );
	_Chunk ( PyObject *p, const boost::python::numeric::array &array, const isis::data::Chunk &chunk );
	
	std::list<boost::shared_ptr<isis::data::Chunk> > contiguousChunkList_;

	template<typename TYPE>
	void makeContiguousChunk() {
		isis::data::Chunk tChunk = *this;
		tChunk.convertToType( isis::data::ValueArray<TYPE>::staticID );
		const isis::util::ivector4 size = getSizeAsVector();
		isis::data::MemChunk<TYPE> mChunk( size[3], size[2], size[1], size[0] );
		typedef isis::util::ivector4::value_type value_type;
		for ( value_type t = 0; t < size[3]; t++ ) {
			for ( value_type z = 0; z < size[2]; z++ ) {
				for ( value_type y = 0; y < size[1]; y++ ) {
					for ( value_type x = 0; x < size[0]; x++ ) {
						static_cast<isis::data::Chunk&>( mChunk ).voxel<TYPE>(t,z,y,x) =
							tChunk.voxel<TYPE>(x,y,z,t);
					}
				}
			}
		}
		contiguousChunkList_.push_back( boost::shared_ptr<isis::data::Chunk>( new isis::data::Chunk( mChunk ) ) );
	}
private:
	PyObject *self;

};

namespace Chunk {

boost::python::api::object _voxel( const isis::data::Chunk& base, const isis::util::ivector4 &coord );
boost::python::api::object _voxel( const isis::data::Chunk& base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );

api::object _voxelAs ( const isis::data::Chunk &base, const isis::python::data::image_types &type, const isis::util::ivector4 &coord );
api::object _voxelAs ( const isis::data::Chunk &base, const isis::python::data::image_types &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );
api::object _voxelAs ( const isis::data::Chunk &base, const int &type, const isis::util::ivector4 &coord );
api::object _voxelAs ( const isis::data::Chunk &base, const int &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth );

bool _setVoxel( isis::data::Chunk& base, const isis::util::ivector4 &coord, const api::object &value );
bool _setVoxel( isis::data::Chunk& base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );

bool _setVoxelAs( isis::data::Chunk &base, const isis::python::data::image_types &type, const isis::util::ivector4 &coord, const api::object &value );
bool _setVoxelAs( isis::data::Chunk &base, const isis::python::data::image_types &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );
bool _setVoxelAs( isis::data::Chunk &base, const int &type, const isis::util::ivector4 &coord, const api::object &value );
bool _setVoxelAs( isis::data::Chunk &base, const int &type, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value );


bool _convertToType( isis::data::Chunk &base, const unsigned short ID );
bool _convertToType( isis::data::Chunk &base, const unsigned short ID, float scaling, size_t offset );

api::object _getMin( const isis::data::Chunk &base );
api::object _getMax( const isis::data::Chunk &base );
api::object _getMinMax( const isis::data::Chunk &base );

numeric::array _getArray ( isis::python::data::_Chunk &base );
numeric::array _getArray( isis::python::data::_Chunk &base, isis::python::data::image_types image_type );

isis::data::Chunk _createFromArray( const boost::python::numeric::array &arr );
isis::data::Chunk _createFromArray( const boost::python::numeric::array &arr, const isis::data::Chunk &chunk );

}
}
}
}
#endif /* CHUNK_HPP_ */
