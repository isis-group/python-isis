__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def minimum_filter(image, size=None, footprint=None):
	if( size == None and footprint == None):
		print "You must either specifiy ths 'size'-parameter of the 'footprint'-parameter!"
		return
	array = image.getArray()
	return data.Image(ndimage.filters.minimum_filter(array,size=size,footprint=footprint), image)