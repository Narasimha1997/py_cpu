#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <unordered_map>
#include <string>

//cpu_features
#include "cpu_features_macros.h"

/*
    Architecture specific marcos
*/

#if defined(CPU_FEATURES_ARCH_X86)
#include "cpuinfo_x86.h"

typedef struct
{
    std::string brand;
    std::string vendor;
    int family;
    int model;
    int stepping;
    std::string arch;
    std::string uarch;
    std::unordered_map<std::string, bool> features;
} x86_CPU;

x86_CPU GetCPUInfo()
{
    const cpu_features::X86Info cpu_info = cpu_features::GetX86Info();
    //set the structure fields :
    x86_CPU cpu;
    cpu.arch = "x86";
    cpu.vendor = cpu_info.vendor;
    cpu.family = cpu_info.family;
    cpu.model = cpu_info.model;
    cpu.stepping = cpu_info.stepping;
    cpu.uarch = cpu_features::GetX86MicroarchitectureName(
        cpu_features::GetX86Microarchitecture(&cpu_info));

    for (int i = 0; i < cpu_features::X86_LAST_; i++)
    {
        const auto enum_val = static_cast<cpu_features::X86FeaturesEnum>(i);
        std::pair<std::string, bool> feature_pair(
            cpu_features::GetX86FeaturesEnumName(enum_val),
            cpu_features::GetX86FeaturesEnumValue(&cpu_info.features, enum_val));
        cpu.features.insert(feature_pair);
    }

    //set brand string
    char brand[49];
    cpu_features::FillX86BrandString(brand);

    cpu.brand = brand;

    return cpu;
}

PYBIND11_MODULE(bindings, mod)
{
    mod.doc() = "Cross-platform CPU features library. Built on Google's cpu_features.";

    //Bind the feature-map
    pybind11::bind_map<std::unordered_map<std::string, bool>>(mod, "Features");

    auto classExporter = pybind11::class_<x86_CPU>(mod, "CpuInfo");

    classExporter.def(pybind11::init<>());
    classExporter.def_readonly("arch", &x86_CPU::arch);
    classExporter.def_readonly("brand", &x86_CPU::brand);
    classExporter.def_readonly("vendor", &x86_CPU::vendor);
    classExporter.def_readonly("family", &x86_CPU::family);
    classExporter.def_readonly("model", &x86_CPU::model);
    classExporter.def_readonly("stepping", &x86_CPU::stepping);
    classExporter.def_readonly("uarch", &x86_CPU::uarch);
    classExporter.def_readonly("features", &x86_CPU::features);

    //Add platform-specific CPU Info function
    mod.def("get_cpu_info", &GetCPUInfo, "Get cpu features.");
}

#elif defined(CPU_FEATURES_ARCH_ARM)
#include "cpuinfo_arm.h"

typedef struct
{
    int implementer;
    int architecture;
    int variant;
    int part;
    int revision;
    std::unordered_map<std::string, bool> features;
} ARM_CPU;

ARM_CPU GetCPUInfo()
{
    const cpu_features::ArmInfo cpu_info = cpu_features::GetArmInfo();
    ARM_CPU cpu;
    cpu.implementer = cpu_info.implementer;
    cpu.architecture = cpu_info.architecture;
    cpu.variant = cpu_info.variant;
    cpu.part = cpu_info.part;
    cpu.revision = cpu_info.revision;

    for (int i = 0; i < cpu_features::ARM_LAST_; i++)
    {
        const auto enum_val = static_cast<cpu_features::ArmFeaturesEnum>(i);
        std::pair<std::string, bool> feature_pair(
            cpu_features::GetArmFeaturesEnumName(enum_val),
            cpu_features::GetArmFeaturesEnumValue(&cpu_info.features, enum_val));
        cpu.features.insert(feature_pair);
    }

    return cpu;
}

PYBIND11_MODULE(bindings, mod)
{
    mod.doc() = "Cross-platform CPU features library. Built on Google's cpu_features.";

    //Bind the feature-map
    pybind11::bind_map<std::unordered_map<std::string, bool>>(mod, "Features");

    auto classExporter = pybind11::class_<ARM_CPU>(mod, "CpuInfo");

    classExporter.def(pybind11::init<>());
    classExporter.def_readonly("implementer", &ARM_CPU::implementer);
    classExporter.def_readonly("architecture", &ARM_CPU::architecture);
    classExporter.def_readonly("variant", &ARM_CPU::variant);
    classExporter.def_readonly("revision", &ARM_CPU::revision);
    classExporter.def_readonly("part", &ARM_CPU::part);
    classExporter.def_readonly("arch", &ARM_CPU::arch);

    classExporter.def_readonly("features", &ARM_CPU::features);

    //Add platform-specific CPU Info function
    mod.def("get_cpu_info", &GetCPUInfo, "Get cpu features.");
}

#elif defined(CPU_FEATURES_ARCH_AARCH64)
#include "cpuinfo_aarch64.h"

typedef struct
{
    std::unordered_map<std::string, bool> features;
    int implementer;
    int variant;
    int part;
    int revision;
    std::string arch;
} AARCH_CPU;

AARCH_CPU GetCpuInfo()
{
    const cpu_features::Aarch64Info cpu_info = cpu_features::GetAarch64Info();
    AARCH_CPU cpu;

    cpu.arch = "aarch64";
    cpu.variant = cpu_info.variant;
    cpu.implementer = cpu_info.implementer;
    cpu.part = cpu_info.part;
    cpu.revision = cpu.revision;

    for (int i = 0; i < cpu_features::AARCH64_LAST_; i++)
    {
        const auto enum_val = static_cast<cpu_features::Aarch64FeaturesEnum>(i);
        std::pair<std::string, bool> feature_pair(
            cpu_features::GetAarch64FeaturesEnumName(enum_val),
            cpu_features::GetAarch64FeaturesEnumValue(&cpu_info.features, enum_val));
        cpu.features.insert(feature_pair);
    }

    return cpu;
}

PYBIND11_MODULE(bindings, mod)
{
    mod.doc() = "Cross-platform CPU features library. Built on Google's cpu_features.";

    //Bind the feature-map
    pybind11::bind_map<std::unordered_map<std::string, bool>>(mod, "Features");

    auto classExporter = pybind11::class_<AARCH_CPU>(mod, "CpuInfo");

    classExporter.def(pybind11::init<>());
    classExporter.def_readonly("implementer", &AARCH_CPU::implementer);
    classExporter.def_readonly("variant", &AARCH_CPU::variant);
    classExporter.def_readonly("revision", &AARCH_CPU::revision);
    classExporter.def_readonly("part", &AARCH_CPU::part);
    classExporter.def_readonly("arch", &AARCH_CPU::arch);

    classExporter.def_readonly("features", &AARCH_CPU::features);

    //Add platform-specific CPU Info function
    mod.def("get_cpu_info", &GetCpuInfo, "Get cpu features.");
}

#elif defined(CPU_FEATURES_ARCH_MIPS)
#include "cpuinfo_mips.h"

typedef struct
{
    std::string arch;
    std::unordered_map<std::string, bool> features;
} MIPS_CPU;

MIPS_CPU GetCpuInfo()
{
    const cpu_features::MipsInfo cpu_info = cpu_features::GetMipsInfo();
    MIPS_CPU cpu;

    cpu.arch = "mips";
    for (int i = 0; i < cpu_features::MIPS_LAST_; i++)
    {
        const auto enum_val = static_cast<cpu_features::MipsFeaturesEnum>(i);
        std::pair<std::string, bool> feature_pair(
            cpu_features::GetMipsFeaturesEnumName(enum_val),
            cpu_features::GetMipsFeaturesEnumValue(&cpu_info.features, enum_val));
        cpu.features.insert(feature_pair);
    }

    return cpu;
}

PYBIND11_MODULE(bindings, mod)
{
    mod.doc() = "Cross-platform CPU features library. Built on Google's cpu_features.";

    //Bind the feature-map
    pybind11::bind_map<std::unordered_map<std::string, bool>>(mod, "Features");

    auto classExporter = pybind11::class_<MIPS_CPU>(mod, "CpuInfo");

    classExporter.def(pybind11::init<>());
    classExporter.def_readonly("arch", &MIPS_CPU::arch);
    classExporter.def_readonly("features", &MIPS_CPU::features);

    //Add platform-specific CPU Info function
    mod.def("get_cpu_info", &GetCpuInfo, "Get cpu features.");
}

#elif defined(CPU_FEATURES_ARCH_PPC)
#include "cpuinfo_ppc.h"

typedef struct
{
    std::string platform;
    std::string model;
    std::string machine;
    std::string cpu;
    std::string base_platform;
    std::string arch;
    std::unordered_map<std::string, bool> features;
} PPC_CPU;

PPC_CPU GetCpuInfo()
{
    const cpu_features::PPCInfo cpu_info = cpu_features::GetPPCInfo();
    const cpu_features::PPCPlatformStrings platform = cpu_features::GetPPCPlatformStrings();

    PPC_CPU cpu;

    cpu.arch = "ppc";
    cpu.platform = platform.platform;
    cpu.machine = platform.machine;
    cpu.model = platform.model;
    cpu.cpu = platform.cpu;
    cpu.base_platform = platform.type.base_platform;

    for (int i = 0; i < cpu_features::PPC_LAST_; i++)
    {
        const auto enum_val = static_cast<cpu_features::PPCFeaturesEnum>(i);
        std::pair<std::string, bool> feature_pair(
            cpu_features::GetPPCFeaturesEnumName(enum_val),
            cpu_features::GetPPCFeaturesEnumValue(&cpu_info.features, enum_val));
        cpu.features.insert(feature_pair);
    }

    return cpu;
}

PYBIND11_MODULE(bindings, mod)
{
    mod.doc() = "Cross-platform CPU features library. Built on Google's cpu_features.";

    //Bind the feature-map
    pybind11::bind_map<std::unordered_map<std::string, bool>>(mod, "Features");

    auto classExporter = pybind11::class_<PPC_CPU>(mod, "CpuInfo");

    classExporter.def(pybind11::init<>());
    classExporter.def_readonly("platform", &PPC_CPU::platform);
    classExporter.def_readonly("model", &PPC_CPU::model);
    classExporter.def_readonly("machine", &PPC_CPU::machine);
    classExporter.def_readonly("cpu", &PPC_CPU::cpu);
    classExporter.def_readonly("base_platform", &PPC_CPU::base_platform);
    classExporter.def_readonly("arch", &PPC_CPU::arch);

    classExporter.def_readonly("features", &PPC_CPU::features);

    //Add platform-specific CPU Info function
    mod.def("get_cpu_info", &GetCpuInfo, "Get cpu features.");
}

#endif