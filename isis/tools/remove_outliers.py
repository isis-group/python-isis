__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage
import mean
import standard_deviation
import normalize_values

def remove_outliers(image):
	mean_value = mean.mean(image)
	min_max = image.getMinMax()
	stdev = standard_deviation.standard_deviation(image)
	min_value = mean_value - stdev
	max_value = mean_value + stdev
	if(min_value < min_max[0]):
		min_value = min_max[0]
	if( max_value > min_max[1]):
		max_value = min_max[1]
	return normalize_values.normalize_values(image, min_value, max_value )