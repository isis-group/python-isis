set(DATA_FILES	__init__.py
                concatenate.py
                split.py
                convenience.py
                metadata.py
                swap_axes.py
                normalize_values.py)

install(FILES ${DATA_FILES}
  DESTINATION  ${PYTHON_INSTALL_PATH}/isis/tools)
