from importlib.metadata import version, PackageNotFoundError

from tardigrade_error_tools import tardigrade_error_tools

try:
    __version__ = version("tardigrade_error_tools")
except PackageNotFoundError:
    try:
        from tardigrade_error_tools import _version
        __version__ = _version.version
    except ImportError:
        import pathlib
        import warnings
        warnings.filterwarnings(action='ignore', message='tag', category=UserWarning, module='setuptools_scm')
        import setuptools_Scm
        __version__ = setuptools_scm.get_version(root=pathlib.Path(__file__).parent.parent.parent.parent.parent)

