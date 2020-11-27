from skbuild import setup

setup(
    name="pycpu",
    version="0.0.1",
    author="Narasimha Prasanna HN",
    author_email="narasimhaprasannahn@gmail.com",
    description="Python bindings for Google's cpu_features library.",
    url="https://github.com/Narasimha1997/py_cpu.git",
    license="Apache 2.0 License",
    has_package_data=False,
    package_dir={"": "src"},
    packages = ["pycpu"],
    cmake_install_dir = "src/pycpu"
)