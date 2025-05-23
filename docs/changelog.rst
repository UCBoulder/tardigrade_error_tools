.. _changelog:


#########
Changelog
#########

******************
0.9.6 (unreleased)
******************

Bug Fixes
=========
- Corrected bug in setuptools_scm import in __init__.py for the python interface (:pull:`27`). By `Nathan Miller`_.

Internal Changes
================
- Added the source file to the install (:pull:`28`). By `Nathan Miller`_.

******************
0.9.5 (04-29-2025)
******************

Internal Changes
================
- Changed packaging to reflect newer efforts (:pull:`24`). By `Nathan Miller`_.

Release
=======
- Released version 0.9.5 (:pull:`25`). By `Nathan Miller`_.

******************
0.9.4 (04-28-2025)
******************

Internal Changes
================
- Changed the target name of the python bindings (:pull:`19`). By `Nathan Miller`_.

Bug Fixes
=========
- Re-enabled building the python bindings with the shared object library (:pull:`19`). By `Nathan Miller`_.

Release
=======
- Released version 0.9.4 (:pull:`20`). By `Nathan Miller`_.

******************
0.9.3 (04-28-2025)
******************

Internal Changes
================
- Improved finding the right python interpreter (:pull:`17`). By `Nathan Miller`_.

Release
=======
- Released version 0.9.3 (:pull:`18`). By `Nathan Miller`_.

******************
0.9.2 (04-24-2025)
******************

Internal Changes
================
- Trying to help cmake find the right python interpreter (:pull:`15`). By `Nathan Miller`_.

Release
=======
- Released version 0.9.2 (:pull:`16`). By `Nathan Miller`_.

******************
0.9.1 (04-23-2025)
******************

Internal Changes
================
- Trying to update the conda packaging (:pull:`13`). By `Nathan Miller`_.

Documentation
=============
- Small updates to the ReadMe (:pull:`12`). By `Nathan Miller`_.

Release
=======
- Released version 0.9.1 (:pull:`14`). By `Nathan Miller`_.

******************
0.9.0 (01-07-2025)
******************

New Features
============
- Added header only build (:pull:`8`). By `Nathan Miller`_.
- Added optimized build flag that bypasses the error handling (:pull:`10`). By `Nathan Miller`_.
- Added macro for code that will be evaluated only when errors are being handled (:pull:`10`). By `Nathan Miller`_.

Internal Changes
================
- Changed to use O3 optimization by default (:pull:`7`). By `Nathan Miller`_.

Bug Fixes
=========
- Removed whitespace in add_library call in CMakeLists file (:pull:`6`). By `Nathan Miller`_.

Release
=======
- Released version 0.9.0 (:pull:`11`). By `Nathan Miller`_.

******************
0.8.0 (2024-04-02)
******************

Release
=======
- Released version 0.8.0 (:pull:`5`). By `Nathan Miller`_.

New Features
============
- Added a catch function to replace the if statement pattern (:pull:`2`). By `Nathan Miller`_.
- Added parenthesis to the catch function to try and prevent issues (:pull:`3`). By `Nathan Miller`_.
- Added a function to capture the error message in a standard string (:pull:`4`). By `Nathan Miller`_.

Breaking Changes
================
- Changed the printNestedExceptions interface to only accept the exception and a header message. This will affect almost no-one but it is breaking (:pull:`4`). By `Nathan Miller`_.

******************
0.7.2 (2023-09-27)
******************

Internal Changes
================
- Clean up conda package CI files after conda-build (:issue:`24`, :merge:`56`). By `Sergio Cordova`_.
- Add draft, minimal GitHub release action. Required for future conda-forge recipe (:issue:`25`, :merge:`59`). By `Kyle
  Brindley`_.

******************
0.7.1 (2023-07-21)
******************

Breaking changes
================
- Change project, package, and namespace from 'error tools' to 'tardigrade error tools' (:issue:`23`, :merge:`54`). By
  `Kyle Brindley`_.

Internal Changes
================
- Clean up Conda package recipe to match installed packages/libraries to the correct build-time environments
  (:issue:`22`, :merge:`51`). By `Kyle Brindley`_.
- Remove compiler as a runtime dependency. The OS-correct standard library package is added as a depedency by
  conda-build (:merge:`52`). By `Kyle Brindley`_.
- Build c++ stdlib variants instead of compiler variants (:merge:`53`). By `Kyle Brindley`_.

******************
0.6.1 (2023-06-20)
******************

Breaking changes
================
- Deploy to the Conda environment preferred ``lib`` directory instead of the CMake linux default ``lib64`` (:issue:`20`,
  :merge:`49`). By `Kyle Brindley`_.

******************
0.5.0 (2023-03-27)
******************

Internal Changes
================
- Add GCC 10 conda package build (:issue:`16`, :merge:`42`). By `Sergio Cordova`_.
- Removed GCC 7 conda package build (:issue:`18`, :merge:`43`). By `Sergio Cordova`_.

New Features
============
- Added stacktrace capability using nested exceptions (:merge:`41`). By `Nathan Miller`_.

Documentation
=============
- Added documentation for the new macros, functions, and a quick-start user manual (:merge:`44`). By `Nathan Miller`_.

******************
0.4.1 (2023-03-16)
******************

Internal Changes
================
- Remove upper bound compiler version on shared development environment (:merge:`29`). By `Kyle Brindley`_.
- Project configuration and conda build recipe changes to allow macOS builds and conda-build test stage (:merge:`31`).
  By `Kyle Brindley`_.
- Add mamba to CI environment and switch to mamba builds while troubleshooting conda issues (:issue:`12`, :merge:`33`,
  :merge:`34`). By `Kyle Brindley`_.
- Add GCC 11 conda package build (:issue:`13`, :merge:`35`). By `Kyle Brindley`_.
- Force CI environment to build consistently from conda-forge (:merge:`36`). By `Kyle Brindley`_.
- Prefer project-wide compiler options and remove ``-ansi`` to get consistent application of c++17 (:merge:`37`). By
  `Kyle Brindley`_.
- Force compiler version match in conda-build variants (:merge:`38`). By `Kyle Brindley`_.

******************
0.3.0 (08-24-2022)
******************

Release
=======
- Released version 0.3.0 (:merge:`26`)

Internal Changes
================
- Build, package, and deploy as a Conda package to the AEA Conda channel (:merge:`23`). By `Kyle Brindley`_.
- Fix the expected conda package architecture path (:merge:`24`). By `Kyle Brindley`_.
- Made building the python interface optional (:merge:`25`). By `Nathan Miller`_.


******************
0.2.3 (2022-03-21)
******************

Internal Changes
================
- Update the build configuration to handle conda environments than manage cpp compilers and libraries (:issue:`5`
  :merge:`18`). By `Kyle Brindley`_.
- Add back compiler flags related to code warnings for the project wide compile options (:issue:`6`, :merge:`20`). By
  `Kyle Brindley`_.

******************
0.2.2 (2021-07-12)
******************

Bug fixes
=========
- Fix unbound CD variable (:issue:`3` :merge:`4`). By `Kyle Brindley`_.

Internal Changes
================
- Update minimal Conda environment file (:pull:`48` :jira:`714`). By `Kyle Brindley`_.
- Migrate from ddw-bitcket.lanl.gov to re-git.lanl.gov (:issue:`1` :merge:`1`). By `Kyle Brindley`_.
- Update changelog issue and merge request link creation Sphinx directives (:issue:`2` :merge:`3`). By `Kyle Brindley`_.
- Use a commonly sourced environment activation script for CI/CD pipeline execution (:issue:`2` :merge:`3`). By `Kyle Brindley`_.
- Temporarily comment out Git tag push logic for master branch deploy until Gitlab permissions are resolved (:issue:`3`
  :merge:`4`). By `Kyle Brindley`_.
- Update Gitlab CI/CD job to allow Git tag pushes during production version deployment (:issue:`4` :merge:`6` :merge:`8`
  :merge:`10` :merge:`12`). By `Kyle Brindley`_.


******************
0.2.1 (2021-06-24)
******************

New Features
============
- Auto bump micro/patch version for production release from master branch (:pull:`45` :jira:`695`). By `Kyle Brindley`_.

Bug fixes
=========
- Add CMake build type to CI/CD build scripts to correctly install the protected ``<project>Targets.cmake`` file
  (:pull:`35` :pull:`36`). By `Kyle Brindley`_.

Internal Changes
================
- Build version number from Git tags following the default ``setuptools_scm`` string style and using the predictive
  micro/patch update behavior for development versions (:pull:`44` :jira:`694`). By `Kyle Brindley`_.


******************
0.2.0 (2021-05-28)
******************

New Features
============
- Add deploy CMake files for build, deploy, discovery, and version comparisons (:jira:`623`, :pull:`31`). By `Kyle
  Brindley`_.
- Deploy the entire project (library, headers, cmake files) during CD scripts (:jira:`582`, :pull:`28`). By `Kyle
  Brindley`_.

Bug fixes
=========
- Only print the footer when the header is requested (:jira:`582`, :pull:`28`). By `Kyle Brindley`_.
- Fix the Doxygen/Sphinx dependence order (:jira:`582`, :pull:`28`). By `Kyle Brindley`_.
- Find the local system ``cmake3`` executable in CD scripts (:jira:`625`, :pull:`32`). By `Kyle Brindley`_.
- Remove version templating to help downstream project find the public headers (:jira:`633`, :pull:`33`). By `Kyle
  Brindley`_.

Internal Changes
================
- Consolidate error node print unit tests (:jira:`582`, :pull:`28`). By `Kyle Brindley`_.
- Remove the ``CXX`` compiler variable settings for build scripts (:jira:`665`,
  :pull:`34`. By `Kyle Brindley`_.


******************
0.1.0 (2020-11-30)
******************

Breaking changes
================

New Features
============

Bug fixes
=========

Documentation
=============

Internal Changes
================

Enhancements
============
