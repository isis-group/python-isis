set(DATA_FILES	__init__.py
                concatenate.py
                split.py)

install(FILES ${DATA_FILES}
  DESTINATION  ${PYTHON_INSTALL_PATH}/isis/tools)
