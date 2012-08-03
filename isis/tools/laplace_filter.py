__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def laplace_filter(image):
	array = image.getArray()
	return data.Image(ndimage.filters.laplace(array), image)