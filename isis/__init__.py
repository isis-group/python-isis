__version__ = '0.6.1'
VERSION = tuple(map(int, __version__.split('.')))

__all__=["util","data"]

def getVersion():
	return VERSION