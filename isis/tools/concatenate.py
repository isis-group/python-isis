__author__ = 'tuerke'

from .. import data

def _concatenate_time_dim( imageList ):
    allChunks = []
    acquisitionNumber = 0
    for i in imageList:
        chunks = i.getChunksAsList()
        for c in chunks:
            if( c.hasProperty('acquisitionTime') ):
                c.removeProperty('acquisitionTime')
            c.setProperty('acquisitionNumber', acquisitionNumber)
            acquisitionNumber+=1
        allChunks.extend(chunks)
    return data.Image.createFromChunks( allChunks )



def concatenate( imageList, dimension ):
    if( len( imageList ) <= 1 ):
        print 'Trying to concatenate a list of 0 or 1 entries ... how should i do this?'
        return imageList
    if( dimension == data.dimensions.TIME_DIM ):
        return _concatenate_time_dim( imageList )
    else:
        print 'Sorry, there are no implementations for that dimension yet!'

