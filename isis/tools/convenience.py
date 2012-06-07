__author__ = 'tuerke'

from .. import data
import os

def load_from_path_list( pathList ):
	images = []
	for path in pathList:
		if( os.path.exists( path ) ):
			images.extend( data.IOFactory.load( path ) )
		else:
			print "Path " + path + " does not exist. Omitting it."
	return images
		