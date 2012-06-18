from . import util
import logging

def log( lvl, mesg ):
	if( not util.hasLogger() ):
		logger = logging.getLogger('isis-logger')
		formatter = logging.Formatter('%(asctime)s %(name)-12s %(levelname)-8s %(message)s')
		stream_handler = logging.StreamHandler()
		stream_handler.setFormatter( formatter )
		logger.addHandler( stream_handler )
		util.setLogger( logger )
	logger = util.getLogger()
	logger.log(lvl, mesg )