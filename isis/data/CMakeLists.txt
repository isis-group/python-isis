
include_directories(${CMAKE_SOURCE_DIR}/isis)

############################################################
# configure targets
############################################################

set(DATA_FILES	 data.cpp
				_image.cpp
				_chunk.hpp
				_ioapplication.cpp
				_ndimensional.cpp
				_iofactory.hpp
				_writingvalueadapter.cpp )

add_library(_data SHARED ${DATA_FILES})
set_target_properties(_data PROPERTIES PREFIX "")
target_link_libraries( _data _core ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${ISIS_LIBRARY})

configure_file(__init__.py 
  ${CMAKE_BINARY_DIR}/python/isis/data/__init__.py COPYONLY)

############################################################
# configure installation
############################################################
foreach(pv ${PYTHON_VERSIONS})
execute_process ( COMMAND ${pv} -c "from distutils.sysconfig import get_python_lib; print get_python_lib().lstrip('${PYTHON_PACKAGE_PATH_PREFIX}')" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
set(PYTHON_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}")

install(FILES __init__.py 
  DESTINATION  ${PYTHON_INSTALL_PATH}/isis/data)

install(TARGETS _data
  LIBRARY DESTINATION  ${PYTHON_INSTALL_PATH}/isis/data 
  COMPONENT RuntimeLibraries)
endforeach(pv)
