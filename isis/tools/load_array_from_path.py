__author__ = 'tuerke'

import os
from .. import data

def load_array_from_path(path, with_properties=False, data_type = 0 ):
	image = data.IOFactory.load(path)[0]
	if (data_type != 0):
		array = image.getArray( data_type ).copy()
	else:
		array = image.getArray().copy()
	if(with_properties):
		return array, image.getProperties()
	else:
		return array