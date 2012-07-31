__author__ = 'tuerke'

from .. import data
import os

def load_array_from_path(path, data_type = 0):
	image = data.IOFactory.load(path)[0]
	if (data_type != 0):
		array = image.getArray( data_type ).copy()
	else:
		array = image.getArray().copy()
	return array, image.getProperties()