__author__ = 'tuerke'

from .. import data

def swap_byteorder(image):
	array = image.getArray()
	return data.Image(array.byteswap(False),image)