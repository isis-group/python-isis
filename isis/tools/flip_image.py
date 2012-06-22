__author__ = 'tuerke'

from .. import data

def flip_image( image, dimension ):
	sub_calls = []
	sub_calls.append( _flip_image_row )
	sub_calls.append( _flip_image_column )
	sub_calls.append( _flip_image_slice )
	sub_calls.append( _flip_image_time )
	
	orig_array = image.getArray()
	buffer_array = orig_array.copy()
	size = image.getSizeAsVector()[dimension]

	sub_calls[dimension]( orig_array, buffer_array, size )

	return data.Image( buffer_array, image )

	
def _flip_image_row( orig_array, buffer_array, size ):
	count_rev = size - 1
	for count in range(0, size):
		buffer_array[count] = orig_array[count_rev]
		count_rev = count_rev - 1

def _flip_image_column( orig_array, buffer_array, size ):
	count_rev = size - 1
	for count in range(0, size):
		buffer_array[:,count] = orig_array[:,count_rev]
		count_rev = count_rev - 1

def _flip_image_slice( orig_array, buffer_array, size ):
	count_rev = size - 1
	for count in range(0, size):
		buffer_array[:,:,count] = orig_array[:,:,count_rev]
		count_rev = count_rev - 1

def _flip_image_time( orig_array, buffer_array, size ):
	count_rev = size - 1
	for count in range(0, size):
		buffer_array[:,:,:,count] = orig_array[:,:,:,count_rev]
		count_rev = count_rev - 1

