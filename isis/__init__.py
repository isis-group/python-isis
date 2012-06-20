from log import log
import util
import data
import tools

__all__=['util','data','tools', 'log', 'getVersion']

VERSION = '0.10.2'
VERSION_AS_LIST = tuple(map(int, VERSION.split('.')))

def getVersion():
	return VERSION_AS_LIST
