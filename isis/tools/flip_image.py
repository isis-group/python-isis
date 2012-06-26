__author__ = 'tuerke'

from .. import data

def flip_image( image, dimension, flip_orientation_matrix = True, center_is_image_center = False ):
	'''Flips the voxels of 'image' at the specified 'dimension'

	If 'flip_orientation_matrix' is 'True' the orientation matrix will be flipped the same way.
	This means orientation will not change in physical space.

	If 'flip_orientation_matrix' is 'False' the orientation matrix will be prevented and
	orientation will change in physical space.
	'''
	sub_calls = []
	sub_calls.append( _flip_image_row )
	sub_calls.append( _flip_image_column )
	sub_calls.append( _flip_image_slice )
	sub_calls.append( _flip_image_time )
	
	orig_array = image.getArray()
	buffer_array = orig_array.copy()
	size = image.getSizeAsVector()[dimension]

	sub_calls[dimension]( orig_array, buffer_array, size )

	flipped_image = data.Image( buffer_array, image )

	if( flip_orientation_matrix ):
		transform = [[1,0,0],[0,1,0],[0,0,1]]
		transform[dimension][dimension] *= -1
		flipped_image.transformCoords( transform, center_is_image_center )
	return flipped_image

	
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

