__author__ = 'tuerke'

from .. import data

def get_missing_properties( propmap, properties ):
	"""Returns a list of properties that are not in 'propmap'.

	Note that 'propmap' can be an instance of 'Image', 'Chunk' or 'PropertyMap'.
	"""
	return [property for property in properties if not propmap.hasProperty(property)]