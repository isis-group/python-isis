__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage
import numpy

def gaussian_filter(image,sigma,derivative_sequence=None):
	if( derivative_sequence != None and numpy.array(derivative_sequence).any() ):
		array = image.getArray(data.image_types.FLOAT)
		return data.Image(ndimage.gaussian_filter(array,sigma,order=derivative_sequence),image)
	else:
		array = image.getArray()
		return data.Image(ndimage.gaussian_filter(array,sigma,order=derivative_sequence),image)
		
