import os
from distutils.core import setup
from distutils.extension import Extension

from Cython.Distutils import build_ext

import settings

###########################################
# Get the third-party include directories #
###########################################
include_dirs = [str(settings.CPP_SOURCE_DIRECTORY), str(settings.CONDA_ENVIRONMENT_INCLUDE)]

############################
# Get the static libraries #
############################
# Find current project static library
project_shared_libraries = settings.BUILD_DIRECTORY / settings.CPP_SOURCE_SUBDIRECTORY / f"lib{settings.PROJECT_NAME}.so"
shared_libraries = [str(project_shared_libraries.resolve())]
print("shared_libraries: ", shared_libraries)

# Define the build configuration
ext_modules = [Extension(settings.PROJECT_NAME,
                     sources=[f"{settings.PROJECT_NAME}_python.pyx"],
                     language='c++',
                     extra_objects=shared_libraries,
                     include_dirs=include_dirs,
                     extra_compile_args=[f"-std=c++{settings.CXX_STANDARD}"],
                     extra_link_args=[f"-std=c++{settings.CXX_STANDARD}"]
                     )]

setup(
  name = settings.PROJECT_NAME,
  cmdclass = {'build_ext': build_ext},
  ext_modules = ext_modules
)
