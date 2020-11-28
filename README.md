# py_cpu
Python bindings for Google's [cpu_features](https://github.com/google/cpu_features) library. Using this library, Python developers can check for hardware specific features and enable the respective optimizations in their software at runtime. `py_cpu` provides bindings for multiple hardware architectures like `x86`, `ARM`, `AARCH64`, `MIPS` and `PPC`. 

### Quick start
To use py_cpu, You can directly download and install the pre-built wheel file, using the command below:
```
pip install py_cpu
```

(For x86, the pre-built wheel will be installed automatically, on other platforms, the source distribution will be downloaded and the package will be built on the platform natively)

### Building from source:

Requirements:
    1. Python3
    2. CMake
    3. setuptools
    4. wheel
    5. scikit-build

TO build from source, you can just clone this repository, you need not have to clone the submodules, as they will be downloaded by the cmake build system automatically.
```
git clone https://github.com/Narasimha1997/py_cpu.git
```

To directly install the package from the source, use the command below:
```
pip install py_cpu/   #-- the repo root directory
```

If you are using an older version of pip, the build-system packages will not be automatically installed, in that case,
```
pip3 install -r py_cpu/requirements.txt   #manually install the build requirements
pip3 install py_cpu/                      #then install the package
```

To build `sdist` and `bdist_wheel` you can just run `setup.py` as follows:
```
cd py_cpu/
python3 install sdist bdist_wheel
```

### Usage guide:
To use the package in your codebase, just import `py_cpu`.

```
import py_cpu
```

#### 1. Get the CPU info
```python3
import py_cpu

#get cpu info
cpu_info = py_cpu.CPUInfo()
```

#### 2. Check for features:
```python3
import py_cpu


#call this once during the program init, to avoid unnecessary compute unless required.
cpu_info = py_cpu.CPUInfo()

#check if the CPU supports AES instructions
if cpu_info.features.aes :
    print('Yes, it supports, Run the optimized code')
else :
    print('No, run normal code')

```

#### 3. Get the list of supported features :
```python3
import py_cpu
cpu_info = py_cpu.CPUInfo()

#returns a python dictionary, you can check the feature by
# subscripting, example : features_dict['aes'] -> either True or False
features_dict = cpu_info.get_features_as_dict()
print(features_dict['avx'])

# returns a FeatureFalgs object, this is simple to use because you can use . operator instead of subscripting.

features = cpu_info.get_features()
print(features.avx)
```

#### Get the general info about the hardware
Apart from features and SOCs, you can also query the general info - about architecture type, vendor etc.
These fields are different for different hardware. 

```python3
import py_cpu
cpu_info = py_cpu.CPUInfo()

#get list of field names
supported_fields = cpu_info.get_info_fields()

#example, on x86
# ['arch', 'brand', 'family', 'features', 'model', 'stepping', 'uarch', 'vendor']

#query the fields: Because the cpu_info object supports subscripting

brand_name = cup_info['brand']

#if you want the entire object as a dict
info_dict = cpu_info.as_dict()

#if you want the entire object but exclude features
info_dict_without_features = cpu_info.as_dict(include_features = False)

```

#### 5. Print functions
If you just want to print the output, you can use any of these two methods.
These methods will be just for a fancy fun use.

Pretty-Print Dict - This function uses pprint internally.
```python3
import py_cpu
#obtain CPU info
cpu_info = py_cpu.CPUInfo()

#call pprint method
cpu_info.pprint()
```

Print as table - This function uses python formatting/spacings to display the list as a table.
```python3
import py_cpu
#obtain CPU info
cpu_info = py_cpu.CPUInfo()

#call pprint method
cpu_info.print_as_table()
```

### Guide for developers:
If you want to add new features, this section is for you.
The repository depends on `pybind11` and the original `cpu_features` repository by Google. Both of these are includes as submodules under `src/`.  To get the complete codebase, you have to clone the submodules as well. Just run these commands from the project directory :

```
git submodule init 
git submodule update
```
Or you can clone the repo recursively.

#### Under the hood details:
The binding code is written in C++ and uses `pybind11` to build a `Cpython` extension. `binding.cc` implements the binding code for all the five platform which are supported in the original repo. Since most of the C/C++ compiler implementations on any operating system expose the architecture flags as preprocessor definitions, only the target hardware binding code gets retained for compilation. The binding code also declares structures that are python friendly - Like STL maps etc to store the data. 
The entire structure is a read-only object for python and cannot be modified, this makes the implementation much more easy and faster. During the build-phase, `CMake` first compiles Google's cpu_features library as a submodule and builds a Position independent object code (PIC), since the Cpython extension is a shared dynamic library. Then the target is compiled with Pybind11 to create the final cpython extension. `__init__.py` is just like a glue which which provides caching functionality by storing it inside an object, so you can only init once and use it throughout the lifecycle of the application.

**Note** : This python binding is not an offical Google release. The project respects the license and distribution terms of both `cpu_features` and `pybind11` by adding them as sub-modules - this helps us to keep the original implementation as it is.

### Contributing
If you like to contribute code to this repo, you are always welcome. 
I would encourage newbies to take up the tasks, as it would allow them to get into the open source world.
Also, please do test it on variety of platforms. Please do raise issues if you have any problems.