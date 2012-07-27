set(DATA_FILES	__init__.py
                concatenate.py
                split.py
                load_from_path_list.py
                get_missing_properties.py
                check_properties.py
                swap_axes.py
                normalize_values.py
                flip_image.py)

install(FILES ${DATA_FILES}
  DESTINATION  ${PYTHON_INSTALL_PATH}/isis/tools)
