import setuptools
from pybind11.setup_helpers import Pybind11Extension, build_ext
from subprocess import call
import os


def setpu_cpu_features():
    args = [ os.curdir ]
    if not os.path.exists("cpu_features"):
        args.append("--download")
    call(["./scripts/get_cpu_features.sh", *args])

