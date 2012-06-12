__author__ = 'tuerke'

from .. import data

def normalize_values( image, min_val, max_val, image_type = 0 ):
	min_max = image.getMinMax()
	offset = min_max[0] + min_val
	scaling = float( max_val - min_val ) / float( min_max[1] - min_max[0] )
	if( not image_type ):
		image_type = data.image_types( image.getMajorTypeID() )
	arr = image.getArray( image_type )
	arr *= scaling
	arr += offset
	return data.Image( arr, image )