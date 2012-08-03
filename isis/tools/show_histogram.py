__author__ = 'tuerke'

from .. import data
from .. import util
import numpy
import matplotlib.pyplot as plt

def show_histogram(image,bins=256,normed=False):
	extent = abs(image.getMax() - image.getMin())
	plt.hist(image.getArray().flatten(),extent,histtype='stepfilled',normed=normed)
	plt.title("Histogram for image " + image.getProperty("source"))
	plt.xlabel("Value")
	plt.ylabel("Frequency")
	plt.grid(True)
	plt.show()
