__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage

def resample_image(image, resolution=None, size=None, order=3):
	if(resolution != None):
		return _resample_image_resolution(image,resolution,order)
	elif( size != None ):
		old_size = image.getSizeAsVector()
		return _resample_image_resolution(image, [float(old_size[i]) / float(size[i]) for i in range(0,3)],order)
		
	
def _resample_image_resolution(image, resolution, order):
	array = image.getArray()
	new_size = [array.shape[i]/resolution[i] for i in range(0,3)]
	res_as_list = [i for i in resolution]
	props = image.getProperties()
	props.setProperty("voxelSize", util.fvector3(resolution[0], resolution[1], resolution[2]))
	return data.Image(ndimage.interpolation.affine_transform(array, res_as_list, output_shape=new_size,order=order), props)