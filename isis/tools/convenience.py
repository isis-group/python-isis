__author__ = 'tuerke'

from .. import data
import os

def load_from_path_list( path_list, warning = True ):
	'''Load images from a list of paths 'path_list'.
	
	If 'warning' is set to 'True' a message will be prompted
	if a path in the list does not exist.
	
	Returns a list of images
	'''
	images = []
	for path in pathList:
		if( os.path.exists( path ) ):
			images.extend( data.IOFactory.load( path ) )
		else:
			if( warning ):
				print "Path " + path + " does not exist. Omitting it."
	return images
		