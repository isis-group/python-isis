############################################################
# configure targets
############################################################

set( CORE_FILES core.cpp
				_vector.hpp
				_application.cpp
				_propmap.cpp
				_convertFromPython.cpp
				_convertToPython.hpp )


add_library(_core SHARED ${CORE_FILES} )
set_target_properties(_core PROPERTIES PREFIX "")
target_link_libraries( _core ${ISIS_LIB} ${ISIS_LIB_DEPENDS} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})

configure_file(__init__.py 
  ${CMAKE_BINARY_DIR}/python/isis/core/__init__.py COPYONLY)

############################################################
# configure installation
############################################################
foreach(pv ${PYTHON_VERSIONS})
execute_process ( COMMAND ${pv} -c "from distutils.sysconfig import get_python_lib; print get_python_lib().lstrip('${PYTHON_PACKAGE_PATH_PREFIX}')" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
set(PYTHON_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${PYTHON_SITE_PACKAGES}")

install(FILES __init__.py 
  DESTINATION  ${PYTHON_INSTALL_PATH}/isis/core)

install(TARGETS _core
     LIBRARY DESTINATION  ${PYTHON_INSTALL_PATH}/isis/core
     COMPONENT RuntimeLibraries)
endforeach(pv)
