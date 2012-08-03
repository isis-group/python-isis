__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def center_of_mass(image):
	return ndimage.measurements.center_of_mass(image.getArray())