#include "_chunk.hpp"
#include "common.hpp"

namespace isis {
namespace python {
namespace data {

_Chunk::_Chunk ( PyObject* p, const Chunk& base )
	: Chunk( base ), self( p )
{
	typeID_ = getTypeID();
}

namespace Chunk {

object _voxel ( const isis::python::data::_Chunk& base, const size_t& first, const size_t& second, const size_t& third, const size_t& fourth )
{
	const unsigned int typeID = base.getTypeID();
	return isis::python::data::_internal::VoxelOp::getVoxelAsPyObject( base, typeID, first, second, third, fourth );
}

object _voxel ( const isis::python::data::_Chunk& base, const isis::util::ivector4& coord )
{
	return _voxel( base, coord[0], coord[1], coord[2], coord[3] );
}

bool _setVoxel( isis::python::data::_Chunk& base, const size_t &first, const size_t &second, const size_t &third, const size_t &fourth, const api::object &value )
{
	const unsigned int typeID = base.getTypeID();
	return isis::python::data::_internal::VoxelOp::setVoxelAsPyObject( base, typeID, first, second, third, fourth, value );
}

bool _setVoxel ( isis::python::data::_Chunk& base, const isis::util::ivector4& coord, const object& value )
{
	return _setVoxel( base, coord[0], coord[1], coord[2], coord[3], value );
}

bool _convertToType( isis::data::Chunk &base, const unsigned short ID )
{
	return base.convertToType( ID );
}

bool _convertToType ( isis::data::Chunk& base, const short unsigned int ID, float scaling, size_t offset )
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

object _getMinMax ( const isis::data::Chunk& base )
{
	const std::pair< isis::util::ValueReference, isis::util::ValueReference> minMax = base.getMinMax();
	object min = isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				minMax.first->getTypeID() )->convert ( *minMax.first );
	object max = isis::util::Singletons::get<isis::python::util::_internal::TypesMap, 10>().at (
				minMax.second->getTypeID() )->convert ( *minMax.second );

	return boost::python::make_tuple(min, max);
}


}

}}}