VERSION = '0.10.0'
VERSION_AS_LIST = tuple(map(int, VERSION.split('.')))

__all__=['util','data','tools']

def getVersion():
	return VERSION_AS_LIST