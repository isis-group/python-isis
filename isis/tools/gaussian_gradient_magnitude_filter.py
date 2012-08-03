__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def gaussian_gradient_magnitude_filter(image,sigma):
	array = image.getArray(data.image_types.FLOAT)
	return data.Image(ndimage.gaussian_gradient_magnitude(array,sigma),image)