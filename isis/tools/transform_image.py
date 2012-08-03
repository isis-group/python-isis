__author__ = 'tuerke'

from .. import data
from .. import util
from scipy import ndimage
import numpy

def transform_image(image,transform,offset=None,output_size=None,adapt_orientation=True,adapt_size=True,order=3):
	array = image.getArray()
	props = image.getProperties()
	if( output_size == None and adapt_size==True ):
		transform_abs = numpy.array([[abs(i) for i in transform[0]],[abs(i) for i in transform[1]],[abs(i) for i in transform[2]]])
		output_size = transform_abs.dot(array.shape)
	if( output_size == None and adapt_size==False ):
		output_size = array.shape
	if(offset == None):
		half_size=[i/2 for i in output_size]
		half_size_=[i/2 for i in array.shape]
		offset = half_size_ - numpy.array(transform).dot( numpy.array(half_size) )
	if(adapt_orientation):
		orientation_matrix = numpy.array( [[i for i in image.getProperty("rowVec")],[i for i in image.getProperty("columnVec")],[i for i in image.getProperty("sliceVec")]] )
		corrected_matrix = orientation_matrix.transpose().dot(transform)
		props.setProperty("rowVec",util.fvector3(corrected_matrix[0][0], corrected_matrix[1][0], corrected_matrix[2][0]))
		props.setProperty("columnVec",util.fvector3(corrected_matrix[0][1], corrected_matrix[1][1], corrected_matrix[2][1]))
		props.setProperty("sliceVec",util.fvector3(corrected_matrix[0][2], corrected_matrix[1][2], corrected_matrix[2][2]))
	transformed = ndimage.interpolation.affine_transform(array,transform,offset=[i for i in offset],output_shape=[i for i in output_size],order=order)
	return data.Image(transformed, props)
	