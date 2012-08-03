__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def standard_deviation(image):
	return ndimage.measurements.standard_deviation(image.getArray())