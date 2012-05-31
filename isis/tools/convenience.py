__author__ = 'tuerke'
from isis import data
import os

def loadFromPathList( pathList ):
	images = []
	for path in pathList:
		if( os.path.exists( path ) ):
			images.extend( data.IOFactory.load( path ) )
		else:
			print "Path " + path + " does not exist. Omitting it."
	return images
		