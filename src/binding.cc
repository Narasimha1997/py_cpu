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
# define GetFeatureName GetX86FeaturesEnumName
# define GetFeatureValue GetX86FeaturesEnumValue
# define FeatureType X86Features
# define FeatureEnumType X86FeaturesEnum
# define LastFeature X86_LAST_
#elif defined(CPU_FEATURES_ARCH_ARM)
# include "cpuinfo_arm.h"
# define GetFeatureName GetArmFeaturesEnumName
# define GetFeatureValue GetArmFeaturesEnumValue
# define FeatureType ArmFeatures
# define FeatureEnumType ArmFeaturesEnum
# define LastFeature ARM_LAST_
#elif defined(CPU_FEATURES_ARCH_AARCH64)
# include "cpuinfo_aarch64.h"
# define GetFeatureName GetAarch64FeaturesEnumName
# define GetFeatureValue GetAarch64FeaturesEnumValue
# define FeatureType Aarch64Features
# define FeatureEnumType Aarch64FeaturesEnum
# define LastFeature AARCH64_LAST_
#elif defined(CPU_FEATURES_ARCH_MIPS)
# include "cpuinfo_mips.h"
# define GetFeatureName GetMipsFeaturesEnumName
# define GetFeatureValue GetMipsFeaturesEnumValue
# define FeatureType MipsFeatures
# define FeatureEnumType MipsFeaturesEnum
# define LastFeature MIPS_LAST_
#elif defined(CPU_FEATURES_ARCH_PPC)
# include "cpuinfo_ppc.h"
# define GetFeatureName GetPPCFeaturesEnumName
# define GetFeatureValue GetPPCFeaturesEnumValue
# define FeatureType PPCFeatures
# define FeatureEnumType PPCFeaturesEnum
# define LastFeature PPC_LAST_
#endif

#if defined(CPU_FEATURES_ARCH_X86)

//binding objects
struct x86_cpu_info {
    char brandString[49];
    std::string arch;
    std::string family;
    std::string model;
    std::string stepping;
    std::string uarch;
    FeatureType features;
};

#endif