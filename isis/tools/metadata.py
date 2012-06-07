__author__ = 'tuerke'

from .. import data

def get_missing_properties( propmap, properties ):
	"""Returns a list of properties that are not in 'propmap'.

	Note that 'propmap' can be an instance of 'Image', 'Chunk' or 'PropertyMap'.
	"""
	return [property for property in properties if not image.hasProperty(property)]

def check_properties( propmap, properties ):
	"""Checks if the entries in 'properties' are all contained in 'propmap'.
	Returns 'True' if all entries are found. Otherwise returns 'False'.

	Note that 'propmap' can be an instance of 'Image', 'Chunk' or 'PropertyMap'.
	"""
	return len( get_missing_properties( image, properties ) ) == 0

