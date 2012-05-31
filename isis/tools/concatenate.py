__author__ = 'tuerke'
from isis import data

def _concatenateTimeDim( imageList ):
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
        return _concatenateTimeDim( imageList )
    else:
        print 'Sorry, there are no implementations for that dimension yet!'

