#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include <string>

//cpu_features
#include "cpu_features_macros.h"

/*
    Architecture specific marcos
*/

#if defined(CPU_FEATURES_ARCH_X86)
# include "cpuinfo_x86.h"

const cpu_features::X86Info GetCPUInfo() {
    const cpu_features::X86Info cpu_info = cpu_features::GetX86Info();
    return cpu_info;
}

#elif defined(CPU_FEATURES_ARCH_ARM)
# include "cpuinfo_arm.h"

const cpu_features::ArmInfo GetCPUInfo() {
    const cpu_features::ArmInfo cpu_info = cpu_features::GetArmInfo();
    return cpu_info;
}

#elif defined(CPU_FEATURES_ARCH_AARCH64)
# include "cpuinfo_aarch64.h"

const cpu_features::Aarch64Info GetCpuInfo() {
    const cpu_features::Aarch64Info cpu_info = cpu_features::GetAarch64Info();
    return cpu_info;
}

#elif defined(CPU_FEATURES_ARCH_MIPS)
# include "cpuinfo_mips.h"

const cpu_features::MipsInfo GetCpuInfo() {
    const cpu_features::MipsInfo cpu_info = cpu_features::GetMipsInfo();
    return cpu_info;
}

#elif defined(CPU_FEATURES_ARCH_PPC)
# include "cpuinfo_ppc.h"

const cpu_features::PPCInfo GetCpuInfo() {
    const cpu_features::PPCInfo cpu_info = cpu_features::GetPPCInfo();
    return cpu_info;
}

#else

void GetCpuInfo() {
    return;
}

#endif

PYBIND11_MODULE(pycpu, mod) {
    mod.doc() = "Cross-platform CPU features library. Built on Google's cpu_features.";
    
    //Add platform-specific CPU Info function
    mod.def("get_cpu_info", &GetCPUInfo, "Query CPU info at runtime.");
}