__author__ = 'tuerke'

from .. import data
import os

def write_array_to_path(array, path, propmap = 0 ):
	if( propmap != 0 ):
		image = data.Image( array, propmap )
	else:
		image = data.Image(array)
	data.IOFactory.write(image, path)