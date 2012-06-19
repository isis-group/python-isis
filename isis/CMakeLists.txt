############################################################
# configure python module
############################################################
#this is the string that will be lstripped from the python 
#package install path in order to replace it with the cmake install prefix
set(PYTHON_PACKAGE_PATH_PREFIX "/usr/")

foreach(pv ${PYTHON_VERSIONS})
	execute_process ( COMMAND ${pv} -c "from distutils.sysconfig import get_python_lib; print get_python_lib().lstrip('${PYTHON_PACKAGE_PATH_PREFIX}')" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
	set(PYTHON_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}")
	configure_file(__init__.py ${CMAKE_BINARY_DIR}/python/isis/__init__.py COPYONLY)

############################################################
# installation
############################################################
set( INSTALL_FILES 	__init__.py
					log.py
					)

message(STATUS "Installing python modules to ${PYTHON_INSTALL_PATH}")
install(FILES ${INSTALL_FILES} DESTINATION "${PYTHON_INSTALL_PATH}/isis")
endforeach(pv)

add_subdirectory(util)
add_subdirectory(data)
add_subdirectory(tools)