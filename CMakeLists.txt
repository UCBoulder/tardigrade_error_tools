#===================================================================================================== PROJECT SETUP ===
cmake_minimum_required(VERSION 3.14)
project(tardigrade_error_tools LANGUAGES CXX)

# Set common project paths relative to project root directory
set(CPP_SRC_PATH "src/cpp")
set(PYTHON_SRC_PATH "src/python")
set(PYTHON_TARGET ${PROJECT_NAME}_PYTHON)
set(CYTHON_SRC_PATH "src/cython")
set(CYTHON_TARGET ${PROJECT_NAME}_CYTHON)
set(CMAKE_SRC_PATH "src/cmake")

# Add a cached variable to build the python interface
set(TARDIGRADE_ERROR_TOOLS_BUILD_PYTHON_BINDINGS ON CACHE BOOL "Boolean flag for whether the python bindings should be built")

set(TARDIGRADE_HEADER_ONLY "Set this to true to build the library as a header-only project" CACHE BOOL False)

if(${TARDIGRADE_HEADER_ONLY})
  add_compile_definitions(TARDIGRADE_HEADER_ONLY)
  message("BUILDING IN HEADER ONLY MODE")
endif()

if(${TARDIGRADE_ERROR_TOOLS_OPT})
  add_compile_definitions(TARDIGRADE_ERROR_TOOLS_OPT)
  message(WARNING "BUILDING OPTIMIZED ERROR TOOLS. NO ERRORS WILL BE CAUGHT")
endif()

# Add the cmake folder to locate project CMake module(s)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}" ${CMAKE_MODULE_PATH})

# Set build type checks
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_lower)
set(not_conda_test "true")
if(cmake_build_type_lower STREQUAL "conda-test")
    set(not_conda_test "false")
endif()

if(NOT ${TARDIGRADE_HEADER_ONLY})
    set(project_link_string ${PROJECT_NAME})
endif()
if(cmake_build_type_lower STREQUAL "release")
    set(upstream_required "REQUIRED")
elseif(cmake_build_type_lower STREQUAL "conda-test")
    set(upstream_required "REQUIRED")
    set(not_conda_test "false")
    if (NOT ${TARDIGRADE_HEADER_ONLY})
        # Find the installed project library
        find_file(installed_linked_library
                  "lib${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}"
                  PATHS "$ENV{CONDA_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
                  NO_CACHE
                  REQUIRED)
        set(project_link_string ${installed_linked_library})
    endif()
endif()

# Get version number from Git
set(VERSION_UPDATE_FROM_GIT True)
if(${not_conda_test} STREQUAL "true")
    if (DEFINED ENV{PREFIX})
        set(Python_ROOT_DIR "$ENV{PREFIX}/bin")
    endif()
    set(Python_FIND_STRATEGY LOCATION)
    find_package(Python COMPONENTS Interpreter REQUIRED)
    execute_process(COMMAND ${Python_EXECUTABLE} -m setuptools_scm
                            OUTPUT_VARIABLE ${PROJECT_NAME}_VERSION_STRING_FULL
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX MATCH "[0-9]+\.[0-9]+\.[0-9]+" ${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_STRING_FULL})
    if(${${PROJECT_NAME}_VERSION} STREQUAL "")
        set(${PROJECT_NAME}_VERSION 0.0.0)
    endif()
    project(${PROJECT_NAME} VERSION ${${PROJECT_NAME}_VERSION} LANGUAGES CXX)
endif()

# Add installation directory variables
include(GNUInstallDirs)

# Make the code position independent
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lrt -O3")
endif()

# Enable CTest
enable_testing()

#================================================================================================= FIND DEPENDENCIES ===
# Set build type checks
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_lower)

#=============================================================================================== ADD PROJECT TARGETS ===
# MUST COME AFTER DEPENDENCY LOCATING
# Add project source directories
if(${not_conda_test} STREQUAL "true")
    include_directories("${CPP_SRC_PATH}")
    add_subdirectory("${CPP_SRC_PATH}")
    if(TARDIGRADE_ERROR_TOOLS_BUILD_PYTHON_BINDINGS)
        add_subdirectory(${PYTHON_SRC_PATH})
        add_subdirectory(${CYTHON_SRC_PATH})
    endif()
endif()

# Only add tests and documentation for current project builds. Protects downstream project builds.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Find Boost. Required for tests
    find_package(Boost 1.53.0 REQUIRED COMPONENTS unit_test_framework)
    # Add c++ tests and docs
    add_subdirectory("${CPP_SRC_PATH}/tests")
    if(${not_conda_test} STREQUAL "true")
        add_subdirectory("docs")
    endif()
endif()

#==================================================================================== SETUP INSTALLATION CMAKE FILES ===
if(${not_conda_test} STREQUAL "true")
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                     VERSION ${PROJECT_VERSION}
                                     COMPATIBILITY SameMajorVersion)
    configure_package_config_file(
      "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}/Config.cmake.in"
      "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
      INSTALL_DESTINATION
      ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

    # CMake won't build the targets for local builds of upstream projects
    if(cmake_build_type_lower STREQUAL release)
        install(EXPORT ${PROJECT_NAME}_Targets
                FILE ${PROJECT_NAME}Targets.cmake
                DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
    endif()

    install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
endif()
