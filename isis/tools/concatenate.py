__author__ = 'tuerke'
from isis import data

def concatenateTimeDim( imageList ):
    if( len( imageList ) <= 1 ):
        print 'Trying to concatenate a list of 0 or 1 image. How should i do this?'
        return imageList

    allChunks = []
    acquisitionNumber = 0
    for i in imageList:
        chunks = i.getChunksAsList()
        for c in chunks:
            c.removeProperty('acquisitionTime')
            c.setProperty('acquisitionNumber', acquisitionNumber)
            acquisitionNumber+=1
        allChunks.extend(chunks)

    return data.Image.createFromChunks( allChunks )
