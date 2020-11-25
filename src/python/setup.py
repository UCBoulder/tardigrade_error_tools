import os
from distutils.core import setup
from distutils.extension import Extension

from Cython.Distutils import build_ext
import numpy

import settings


# Search the tree for the static libraries and the include directories
static_libraries = []
include_dirs = [settings.CPP_SOURCE_DIRECTORY]

# Search the build directory
for root, dirs, files in os.walk(settings.CPP_BUILD_DIRECTORY):
    for file in files:
        if file.endswith('.a'):
            static_libraries.append(os.path.abspath(os.path.join(root, file)))

    for dir in dirs:
        if ("cpp" in dir) and ("_deps" in dir):
            include_dirs.append(os.path.join(root, dir))

print(static_libraries)
print(include_dirs)

# Define the build configuration
ext_modules = [Extension("error_tools",
                     sources=["error_tools.pyx"],
                     language='c++',
                     extra_objects=static_libraries,
                     include_dirs=include_dirs,
                     )]

setup(
  name = 'error_tools',
  cmdclass = {'build_ext': build_ext},
  ext_modules = ext_modules
)
