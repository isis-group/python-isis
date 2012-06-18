from log import log

__all__=['util','data','tools', 'log', 'getVersion']

VERSION = '0.10.0'
VERSION_AS_LIST = tuple(map(int, VERSION.split('.')))

def getVersion():
	return VERSION_AS_LIST
