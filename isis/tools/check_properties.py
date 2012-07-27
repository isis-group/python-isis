__author__ = 'tuerke'

from .. import data

from get_missing_properties import get_missing_properties

def check_properties( propmap, properties ):
	"""Checks if the entries in 'properties' are all contained in 'propmap'.
	Returns 'True' if all entries are found. Otherwise returns 'False'.

	Note that 'propmap' can be an instance of 'Image', 'Chunk' or 'PropertyMap'.
	"""
	return len( get_missing_properties( image, properties ) ) == 0