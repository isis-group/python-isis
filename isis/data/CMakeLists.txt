
include_directories(${CMAKE_SOURCE_DIR}/isis)
############################################################
# muparser support
############################################################

option(ISIS_PYTHON_MUPARSER_SUPPORT "Enable muparser support for isis python. This enables the function Image::applyOperation()" OFF)

if( ISIS_PYTHON_MUPARSER_SUPPORT )
	find_library(LIB_MUPARSER "muparser" REQUIRED)
	find_path(INCPATH_MUPARSER "muParser.h" PATH_SUFFIXES "muParser")
	include_directories(${INCPATH_MUPARSER})
	add_definitions(-DISIS_PYTHON_MUPARSER_SUPPORT=1)
endif( ISIS_PYTHON_MUPARSER_SUPPORT)

############################################################
# configure targets
############################################################

set(DATA_FILES	 data.cpp
				_image.cpp
				_chunk.cpp
				_ioapplication.cpp
				_ndimensional.cpp
				_iofactory.hpp
				_writingvalueadapter.cpp
				common.cpp )

add_library(_data SHARED ${DATA_FILES})
set_target_properties(_data PROPERTIES PREFIX "")
target_link_libraries( _data _util ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${ISIS_LIB} ${ISIS_LIB_DEPENDS} ${LIB_MUPARSER})

############################################################
# configure installation
############################################################

set( DATA_FILES	__init__.py
				)

foreach(pv ${PYTHON_VERSIONS})
execute_process ( COMMAND ${pv} -c "from distutils.sysconfig import get_python_lib; print get_python_lib().lstrip('${PYTHON_PACKAGE_PATH_PREFIX}')" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
set(PYTHON_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}")

install(FILES ${DATA_FILES} 
  DESTINATION  ${PYTHON_INSTALL_PATH}/isis/data)

install(TARGETS _data
  LIBRARY DESTINATION  ${PYTHON_INSTALL_PATH}/isis/data 
  COMPONENT RuntimeLibraries)
endforeach(pv)

