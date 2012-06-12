#include "common.hpp"

void isis::python::data::setInitialProperties ( isis::data::Chunk& ch )
{
	const isis::util::ivector4 size = ch.getSizeAsVector();
	ch.setPropertyAs<uint32_t> ( "acquisitionNumber", 0 );
	ch.setPropertyAs<uint16_t> ( "sequenceNumber", 0 );
	ch.setPropertyAs<isis::util::fvector4> ( "rowVec", isis::util::fvector4 ( 1, 0, 0, 0 ) );
	ch.setPropertyAs<isis::util::fvector4> ( "columnVec", isis::util::fvector4 ( 0, 1, 0, 0 ) );
	ch.setPropertyAs<isis::util::fvector4> ( "sliceVec", isis::util::fvector4 ( 0, 0, 1, 0 ) );
	ch.setPropertyAs<isis::util::fvector4> ( "voxelSize", isis::util::fvector4 ( 1, 1, 1, 1 ) );
	ch.setPropertyAs<isis::util::fvector4> ( "indexOrigin", isis::util::fvector4 ( -size[0] / 2. + 0.5, -size[1] / 2. + 0.5, size[2] / 2. + 0.5, 0 ) );
}