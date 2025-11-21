set(PYTHON_SOURCE_FILES
    pyproject.toml.in
    tardigrade_error_tools/_settings.py.in
    tardigrade_error_tools/__init__.py
    tardigrade_error_tools/conftest.py
    tardigrade_error_tools/tests/test_tardigrade_error_tools.py
)
configure_file(tardigrade_error_tools/_settings.py.in tardigrade_error_tools/_settings.py)
configure_file(pyproject.toml.in pyproject.toml)

add_custom_target(${PYTHON_TARGET} ALL
                  DEPENDS ${CYTHON_TARGET})
add_custom_command(TARGET ${PYTHON_TARGET} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${PROJECT_SOURCE_DIR}/${PYTHON_SRC_PATH}" "${PROJECT_BINARY_DIR}/${PYTHON_SRC_PATH}"
                   COMMAND ${Python_EXECUTABLE} -m build --no-isolation
                   DEPENDS ${PYTHON_SOURCE_FILES} ${CYTHON_TARGET}
                   COMMENT "Building the ${PROJECT_NAME} Cython extension - python target"
                  )
# Add pytests as a ctest function for automated testing under unified CMake/CTest tools
if(${APPLE})
    add_test(
        NAME pytest
        COMMAND
            ${CMAKE_COMMAND} -E env DYLD_FALLBACK_LIBRARY_PATH=${CMAKE_BINARY_DIR}/${CPP_SRC_PATH} pytest
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/${PYTHON_SRC_PATH}
    )
else()
    add_test(
        NAME pytest
        COMMAND
            ${CMAKE_COMMAND} -E env LD_LIBRARY_PATH=ENV{LD_LIBRARY_PATH}:${CMAKE_BINARY_DIR}/${CPP_SRC_PATH} pytest
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/${PYTHON_SRC_PATH}
    )
endif()
