VERSION = '0.9.0'
VERSION_AS_LIST = tuple(map(int, VERSION.split('.')))

__all__=['util','data','tools']

def getVersion():
	return VERSION_AS_LIST

NOTICE = 0
INFO = 1
WARNING = 2
ERROR = 3