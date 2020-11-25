from setuptools import setup, find_packages
from cmake_setup import *

setup(name='pycpu',
      description='',
      version='0.0.0.dev0',
      ext_modules=[CMakeExtension('pycpu', sourcedir = "src")],
      cmdclass={'build_ext': CMakeBuildExt},
    )