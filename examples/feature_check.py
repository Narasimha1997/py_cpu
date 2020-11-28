import py_cpu

#get cpu info
cpu_info = py_cpu.CPUInfo()

#get a list of features table as dict
cpu_info.get_features_as_dict()

#get a list of features as FeatureFalgs object, supports . operator based checks
cpu_info.get_features()

#check if your cpu supports AES Instruction set (INTEL-NI)
if cpu_info.features.aes :
    print("CPU has instruction sets for AES, dispatch H/W accelerated code optimized code.")
else:
    print('CPU does not support AES Instruction set, dispatch S/W defined code.')
