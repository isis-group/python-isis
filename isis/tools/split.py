__author__ = 'tuerke'

from .. import data

def splitTimeDim( image, size ):
    timeSize = image.getSizeAsVector()[3]

    if( timeSize < size):
        print 'Error! Your size ' + str(size) + ' is bigger than the number of volumes ' \
            + str(timeSize)

    if( timeSize % size != 0):
        print 'Warning! Your size ' + str(size) + ' does not fit n times in the number of volumes ' \
            + str(timeSize)

    image.spliceDownTo( data.dimensions.TIME_DIM )

    allChunks = image.getChunksAsList()
    chunksPerImage = len(allChunks) / ( timeSize / size)

    retList = []
    start = 0
    for i in range(timeSize / size):
        sImage = data.Image.createFromChunks( allChunks[start:start+chunksPerImage] )
        sImage.join(image, False)
        retList.append( sImage )
        start+=chunksPerImage

    return retList

def split( image, size, dimension ):
	if( dimension == data.dimensions.TIME_DIM ):
		return splitTimeDim( image, size )
	else:
		print 'Sorry, there are no implementations for that dimension yet!'
	return []