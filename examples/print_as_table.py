import py_cpu

#obtain CPU info
cpu_info = py_cpu.CPUInfo()

#call pprint method
cpu_info.print_as_table()

#subscriptable:
print(cpu_info['arch'])