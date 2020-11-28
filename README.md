# py_cpu
Python bindings for Google's [cpu_features](https://github.com/google/cpu_features) library. Using this library, Python developers can check for hardware specific features and enable the respective optimizations in their software at runtime. `pycpu` provides bindings for multiple hardware architectures like `x86`, `ARM`, `AARCH64`, `MIPS` and `PPC`. 

### Quick start
To use pycpu, You can directly download and install the pre-built wheel file, using the command below:
```
pip install pycpu
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
To use the package in your codebase, just import `pycpu`.

```
import pycpu
```

#### 1. Get the CPU info
```python3
import pycpu

#get cpu info
cpu_info = pycpu.CPUInfo()
```

#### 2. Check for features:
```python3
import pycpu


#call this once during the program init, to avoid unnecessary compute unless required.
cpu_info = pycpu.CPUInfo()

#check if the CPU supports AES instructions
if cpu_info.features.aes :
    print('Yes, it supports, Run the optimized code')
else :
    print('No, run normal code')

```

#### 3. Get the list of supported features :
```python3
import pycpu
cpu_info = pycpu.CPUInfo()

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
import pycpu
cpu_info = pycpu.CPUInfo()

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
import pycpu
#obtain CPU info
cpu_info = pycpu.CPUInfo()

#call pprint method
cpu_info.pprint()
```

Print as table - This function uses python formatting/spacings to display the list as a table.
```python3
import pycpu
#obtain CPU info
cpu_info = pycpu.CPUInfo()

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
The binding code is written in C++ and uses `pybind11` to build `Cpython` extension. 