__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def mean(image):
	return ndimage.measurements.mean(image.getArray())