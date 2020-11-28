from skbuild import setup

long_description = open('README.md').read()

setup(
    name="py_cpu",
    version="0.1.0",
    author="Narasimha Prasanna HN",
    author_email="narasimhaprasannahn@gmail.com",
    description="Python bindings for Google's cpu_features library.",
    url="https://github.com/Narasimha1997/py_cpu.git",
    license="Apache 2.0 License",
    has_package_data=False,
    package_dir={"": "src"},
    packages = ["py_cpu"],
    cmake_install_dir = "src/py_cpu",
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'Topic :: System :: Hardware',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.9',      
    ],
    python_requires='>=3',
    long_description = long_description,
    long_description_content_type = 'text/markdown'
)