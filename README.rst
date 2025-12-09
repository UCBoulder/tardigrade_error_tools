.. targets-start-do-not-remove

.. _Doxygen: https://www.doxygen.nl/manual/docblocks.html
.. _Sphinx: https://www.sphinx-doc.org/en/master/
.. _PEP-8: https://www.python.org/dev/peps/pep-0008/
.. _`gersemi`: https://github.com/BlankSpruce/gersemi
.. _`clang-tidy`: https://clang.llvm.org/extra/clang-tidy/
.. _`clang-format`: https://clang.llvm.org/docs/ClangFormat.html

.. targets-end-do-not-remove

########################
tardigrade\_error\_tools
########################

*******************
Project Description
*******************

A collection of tools used for error handling. These tools provide a linked
list class which can help a user both understand where an error happened
and also help the developer to correct for the errors.

Information
===========

* Documentation:
* Wiki:

Developers
==========

* Nathan Miller Nathan.A.Miller@colorado.edu
* Kyle Brindley kbrindley@lanl.gov

************
Dependencies
************

The developer dependencies are found in ``environment.txt``.

.. code-block:: bash

   $ conda create --name tardigrade_error_tools-dev --file environment.txt

**************************
Building the documentation
**************************

.. warning::

   **API Health Note**: The Sphinx API docs are a work-in-progress. The doxygen
   API is much more useful

.. code-block:: bash

   $ pwd
   /path/to/tardigrade_error_tools
   $ cmake -S . -B build
   $ cmake --build build --target Doxygen Sphinx

*****************
Build the library
*****************

Follow the steps for building the documentation and pick up below.

1) Build just the library

   .. code-block:: bash

      $ pwd
      /path/to/tardigrade_error_tools
      $ cmake -S . -B build
      $ cmake --build build --target tardigrade_error_tools

The library can be used as a header-only library by defining the pre-processor
variable ``TARDIGRADE_HEADER_ONLY``. This can be helpful for code optimization
purposes or if in-lining the code is otherwise important. Additionally, the error
handling can be turned off by defining the pre-processor variable ``TARDIGRADE_ERROR_TOOLS_OPT``.
Both of these variable can be independently accessed through cmake via

   .. code-block:: bash

      $ pwd
      /path/to/tardigrade_error_tools
      $ cmake -S . -B build
      $ cmake --build build --target tardigrade_error_tools -DTARDIGRADE_HEADER_ONLY=ON -DTARDIGRADE_ERROR_TOOLS_OPT=ON

****************
Test the library
****************

.. code-block:: bash

   $ pwd
   /path/to/tardigrade_error_tools
   $ cmake -S . -B build
   $ cmake --build build --target tardigrade_error_tools test_tardigrade_error_tools
   $ ctest --test-dir build

*******************
Install the library
*******************

Build the entire project before performing the installation.

4) Build the entire project

   .. code-block:: bash

      $ pwd
      /path/to/tardigrade_error_tools
      $ cmake -S . -B build
      $ cmake --build build --target all

5) Install the library

   .. code-block:: bash

      $ pwd
      /path/to/tardigrade_error_tools
      $ cmake --install build --prefix path/to/root/install

      # Example local user (non-admin) Linux install
      $ cmake --install build --prefix /home/$USER/.local

      # Example install to an active conda environment
      $ cmake --install build --prefix $CONDA_PREFIX

***********************
Build the Conda package
***********************

.. code-block:: bash

   $ VERSION=$(python -m setuptools_scm) conda mambabuild recipe --no-anaconda-upload -c conda-forge --output-folder conda-bld

*****************************
Building the python interface
*****************************

A python interface to the ``tardigrade_error_tools`` C++ routines is provided. After the
libraries have been built, they can be linked so that they can be called with
python.

TODO

*********
Use cases
*********

The error tools interfaces can be used in a number of ways that automate try-catch exception handling. The three
major macros are ``TARDIGRADE_ERROR_TOOLS_CATCH``, ``TARDIGRADE_ERROR_TOOLS_CHECK``, and ``TARDIGRADE_ERROR_TOOLS_EVAL``.

1) ``TARDIGRADE_ERROR_TOOLS_CATCH``

This macro evaluates the provided function or expression and, if it throws an exception, creates a nested
exception stack trace. If ``TARDIGRADE_ERROR_TOOLS_OPT`` is defined, the expression will still be evaluated.

   .. code-block:: c++

      TARDIGRADE_ERROR_TOOLS( myFunction( first_parameter, second_parameter, ... ) )

2) ``TARDIGRADE_ERROR_TOOLS_CHECK``

This macro evaluates a provided expression and throws an exception if the expression is false. This is useful
as the root error handling object. If ``TARDIGRADE_ERROR_TOOLS_OPT`` is defined, the expression will not be
evaluated.

   .. code-block:: c++

      TARDIGRADE_ERROR_TOOLS_CHECK( myExpression, "My error message" )

3) ``TARDIGRADE_ERROR_TOOLS_EVAL``

This macro evaluates the provided expression and will not be evaluated if ``TARDIGRADE_ERROR_TOOLS_OPT`` is defined.

   .. code-block:: c++

      TARDIGRADE_ERROR_TOOLS_EVAL( myFirstExpression; mySecondExpression; )

***********************
Contribution Guidelines
***********************

.. contribution-start-do-not-remove

Git Commit Message
==================

Begin Git commit messages with one of the following headings:

* BUG: bug fix
* DOC: documentation
* FEAT: feature
* MAINT: maintenance
* TST: tests
* REL: release
* WIP: work in progress

For example:

.. code-block:: bash

   git commit -m "DOC: adds documentation for feature"

Git Branch Names
================

When creating branches use one of the following naming conventions. When in doubt use ``feature/<description>``.

* ``bugfix/\<description>``
* ``feature/\<description>``
* ``release/\<description>``

reStructured Text
=================
`Sphinx`_ reads in docstrings and other special portions of the code as reStructured text. Developers should follow
styles in this `Sphinx style guide
<https://documentation-style-guide-sphinx.readthedocs.io/en/latest/style-guide.html#>`_.

Style Guide
===========

This project uses the `gersemi`_ CMake linter. The CI style guide check runs the following command

.. code-block:

   $ gersemi CMakeLists.txt src/ docs/ --check

and any automatic fixes may be reviewed and then applied by developers with the following commands

.. code-block:

   $ gersemi CMakeLists.txt src/ docs/ --diff
   $ gersemi CMakeLists.txt src/ docs/ --in-place

This project enforces its style using `clang-tidy`_ and `clang-format`_ as configured with the
`.clang-format` and `.clang-tidy` files in the root directory. The formatting of the project can be
checked using `clang-tidy`_ by first configuring the project using

.. code-block:

   $ cmake -S . -B build ... -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

where `...` are the other configuration flags specified. After this clang-tidy can be run on the
full project from the source directory via

.. code-block:

   $ run-clang-tidy -config-file=.clang-tidy -header-filter=*.h -p build

.. CAUTION::
    Commit all changes prior to running the clang tidy command. This will edit all source files.

The formatting can be checked using `clang-format`_ by running

.. code-block:

   $ cmake -S . -B build ...
   $ cmake --build build --target check-cpp-format

which will indicate if the formatting is correct. The c++ files can be re-formatted to match the
style guidance by running

.. code-block

   $ cmake --build build --target format-cpp

.. CAUTION::
    Commit all changes prior to running the format command. This will edit all source files.

If the style is not constrained by the above, it should be inferred by the surrounding code.
Wherever a style can't be inferred from surrounding code this project falls back to `PEP-8`_-like
styles. There are two notable exceptions to the notional PEP-8 fall back:

1. `Doxygen`_ style docstrings are required for automated, API from source documentation.
2. This project prefers expansive whitespace surrounding parentheses, braces, and
   brackets.

   * No leading space between a function and the argument list.
   * One space following an open paranthesis ``(``, brace ``{``, or bracket
     ``[``
   * One space leading a close paranthesis ``)``, brace ``}``, or bracket ``]``

An example of the whitespace style:

.. code-block:: bash

   my_function( arg1, { arg2, arg3 }, arg4 );

The following ``sed`` commands may be useful for updating white space, but must
be used with care. The developer is recommended to use a unique git commit
between each command with a corresponding review of the changes and a unit test
run.

* Trailing space for open paren/brace/bracket

  .. code-block:: bash

     sed -i 's/\([({[]\)\([^ ]\)/\1 \2/g' <list of files to update>

* Leading space for close paren/brace/bracket

  .. code-block:: bash

     sed -i 's/\([^ ]\)\([)}\]]\)/\1 \2/g' <list of files to update>

* White space between adjacent paren/brace/bracket

  .. code-block:: bash

     sed -i 's/\([)}\]]\)\([)}\]]\)/\1 \2/g' <list of files to update>

.. contribution-end-do-not-remove
