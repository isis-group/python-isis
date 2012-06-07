/*
 * VoxelOp.hpp
 *
 *  Created on: Jun 7, 2012
 *      Author: tuerke
 */

#ifndef ISIS_PYTHON_VOXEL_OP_
#define ISIS_PYTHON_VOXEL_OP_

#include <DataStorage/valuearray.hpp>
#include <boost/python.hpp>
#include <DataStorage/image.hpp>
#include "common.hpp"

namespace isis
{
namespace python
{
namespace data
{

using namespace isis::data;
using namespace boost::python;
struct VoxelOp {

	static boost::python::api::object getVoxelAsPyObject( const isis::data::Image &ob, const unsigned int &typeID, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth ) {
		switch( typeID ) {
		case ValueArray<int8_t>::staticID:
			return api::object(	ob.voxel<int8_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint8_t>::staticID:
			return api::object( ob.voxel<uint8_t>( first, second, third, fourth ) );
			break;
		case ValueArray<int16_t>::staticID:
			return api::object( ob.voxel<int16_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint16_t>::staticID:
			return api::object( ob.voxel<uint16_t>( first, second, third, fourth ) );
			break;
		case ValueArray<int32_t>::staticID:
			return api::object( ob.voxel<int32_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint32_t>::staticID:
			return api::object( ob.voxel<uint32_t>( first, second, third, fourth ) );
			break;
		case ValueArray<int64_t>::staticID:
			return api::object( ob.voxel<int64_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint64_t>::staticID:
			return api::object( ob.voxel<uint64_t>( first, second, third, fourth ) );
			break;
		case ValueArray<float>::staticID:
			return api::object( ob.voxel<float>( first, second, third, fourth ) );
			break;
		case ValueArray<double>::staticID:
			return api::object( ob.voxel<double>( first, second, third, fourth ) );
			break;
		case ValueArray<std::complex<float> >::staticID:
			return api::object( ob.voxel<std::complex<float> >( first, second, third, fourth ) );
			break;
		case ValueArray<std::complex<double> >::staticID:
			return api::object( ob.voxel<std::complex<double> >( first, second, third, fourth ) );
			break;
		case ValueArray<isis::util::color24>::staticID:
			return api::object( ob.voxel<isis::util::color24>( first, second, third, fourth ) );
			break;
		case ValueArray<isis::util::color48>::staticID:
			return api::object( ob.voxel<isis::util::color48>( first, second, third, fourth ) );
			break;

		}

		return api::object( 0 ); // prevent warnings
	}

	static boost::python::api::object getVoxelAsPyObject( const isis::data::Chunk &ob, const unsigned int &typeID, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth ) {
		switch( typeID ) {
		case ValueArray<int8_t>::staticID:
			return api::object(	ob.voxel<int8_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint8_t>::staticID:
			return api::object( ob.voxel<uint8_t>( first, second, third, fourth ) );
			break;
		case ValueArray<int16_t>::staticID:
			return api::object( ob.voxel<int16_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint16_t>::staticID:
			return api::object( ob.voxel<uint16_t>( first, second, third, fourth ) );
			break;
		case ValueArray<int32_t>::staticID:
			return api::object( ob.voxel<int32_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint32_t>::staticID:
			return api::object( ob.voxel<uint32_t>( first, second, third, fourth ) );
			break;
		case ValueArray<int64_t>::staticID:
			return api::object( ob.voxel<int64_t>( first, second, third, fourth ) );
			break;
		case ValueArray<uint64_t>::staticID:
			return api::object( ob.voxel<uint64_t>( first, second, third, fourth ) );
			break;
		case ValueArray<float>::staticID:
			return api::object( ob.voxel<float>( first, second, third, fourth ) );
			break;
		case ValueArray<double>::staticID:
			return api::object( ob.voxel<double>( first, second, third, fourth ) );
			break;
		case ValueArray<std::complex<float> >::staticID:
			return api::object( ob.voxel<std::complex<float> >( first, second, third, fourth ) );
			break;
		case ValueArray<std::complex<double> >::staticID:
			return api::object( ob.voxel<std::complex<double> >( first, second, third, fourth ) );
			break;
		case ValueArray<isis::util::color24>::staticID:
			return api::object( ob.voxel<isis::util::color24>( first, second, third, fourth ) );
			break;
		case ValueArray<isis::util::color48>::staticID:
			return api::object( ob.voxel<isis::util::color48>( first, second, third, fourth ) );
			break;
		}

		return api::object( 0 ); // prevent warnings
	}

	static bool setVoxelAsPyObject( isis::data::Image &ob, const unsigned int &typeID, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const boost::python::api::object &value ) {
		switch( typeID ) {
		case ValueArray<int8_t>::staticID:
			ob.voxel<int8_t>( first, second, third, fourth ) = extract<int8_t>( value );
			return true;
			break;
		case ValueArray<uint8_t>::staticID:
			ob.voxel<uint8_t>( first, second, third, fourth ) = extract<uint8_t>( value );
			return true;
			break;
		case ValueArray<int16_t>::staticID:
			ob.voxel<int16_t>( first, second, third, fourth ) = extract<int16_t>( value );
			return true;
			break;
		case ValueArray<uint16_t>::staticID:
			ob.voxel<uint16_t>( first, second, third, fourth ) = extract<uint16_t>( value );
			return true;
			break;
		case ValueArray<int32_t>::staticID:
			ob.voxel<int32_t>( first, second, third, fourth ) = extract<int32_t>( value );
			return true;
			break;
		case ValueArray<uint32_t>::staticID:
			ob.voxel<uint32_t>( first, second, third, fourth ) = extract<uint32_t>( value );
			return true;
			break;
		case ValueArray<int64_t>::staticID:
			ob.voxel<int64_t>( first, second, third, fourth ) = extract<int64_t>( value );
			return true;
			break;
		case ValueArray<uint64_t>::staticID:
			ob.voxel<uint64_t>( first, second, third, fourth ) = extract<uint64_t>( value );
			return true;
			break;
		case ValueArray<float>::staticID:
			ob.voxel<float>( first, second, third, fourth ) = extract<float>( value );
			return true;
			break;
		case ValueArray<double>::staticID:
			ob.voxel<double>( first, second, third, fourth ) = extract<double>( value );
			return true;
			break;
		case ValueArray<std::complex<float> >::staticID:
			ob.voxel<std::complex<float> >( first, second, third, fourth ) = extract<std::complex<float> >( value );
			return true;
			break;
		case ValueArray<std::complex<double> >::staticID:
			ob.voxel<std::complex<double> >( first, second, third, fourth ) = extract<std::complex<double> >( value );
			return true;
			break;
		case ValueArray<isis::util::color24>::staticID:
			ob.voxel<isis::util::color24>( first, second, third, fourth ) = extract<isis::util::color24>( value );
			return true;
			break;
		case ValueArray<isis::util::color48>::staticID:
			ob.voxel<isis::util::color48>( first, second, third, fourth ) = extract<isis::util::color48>( value );
			return true;
			break;
		}

		return false;
	}

	static bool setVoxelAsPyObject( isis::data::Chunk &ob, const unsigned int &typeID, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const boost::python::api::object &value ) {
		switch( typeID ) {
		case ValueArray<int8_t>::staticID:
			ob.voxel<int8_t>( first, second, third, fourth ) = extract<int8_t>( value );
			return true;
			break;
		case ValueArray<uint8_t>::staticID:
			ob.voxel<uint8_t>( first, second, third, fourth ) = extract<uint8_t>( value );
			return true;
			break;
		case ValueArray<int16_t>::staticID:
			ob.voxel<int16_t>( first, second, third, fourth ) = extract<int16_t>( value );
			return true;
			break;
		case ValueArray<uint16_t>::staticID:
			ob.voxel<uint16_t>( first, second, third, fourth ) = extract<uint16_t>( value );
			return true;
			break;
		case ValueArray<int32_t>::staticID:
			ob.voxel<int32_t>( first, second, third, fourth ) = extract<int32_t>( value );
			return true;
			break;
		case ValueArray<uint32_t>::staticID:
			ob.voxel<uint32_t>( first, second, third, fourth ) = extract<uint32_t>( value );
			return true;
			break;
		case ValueArray<int64_t>::staticID:
			ob.voxel<int64_t>( first, second, third, fourth ) = extract<int64_t>( value );
			return true;
			break;
		case ValueArray<uint64_t>::staticID:
			ob.voxel<uint64_t>( first, second, third, fourth ) = extract<uint64_t>( value );
			return true;
			break;
		case ValueArray<float>::staticID:
			ob.voxel<float>( first, second, third, fourth ) = extract<float>( value );
			return true;
			break;
		case ValueArray<double>::staticID:
			ob.voxel<double>( first, second, third, fourth ) = extract<double>( value );
			return true;
			break;
		}

		return false;
	}
	template<typename TYPE>
	static isis::data::Chunk getSwappedChunk( const isis::data::Chunk &ch, const bool setInitial = true ) {
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
		if ( setInitial ) {
			isis::python::data::_internal::setInitialProperties(mChunk);
		}
		return mChunk;
	}
};

	
}}}

#endif