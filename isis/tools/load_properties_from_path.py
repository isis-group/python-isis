__author__ = 'tuerke'

import os
from .. import data

def load_properties_from_path(path):
	image = data.IOFactory.load(path)[0]
	return image.getProperties()