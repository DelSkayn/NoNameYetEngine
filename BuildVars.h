#ifndef BUILDVARS_H
#define BUILDVARS_H

#include <string>

class BuildVars {
    static const int  VERSIONMAJOR = ImpactEngine_VERSION_MAJOR;
    static const int VERSIONMINOR = ImpactEngine_VERSION_MINOR; 
    static const int VERSIONPATCH = ImpactEngine_VERSION_PATCH;

    static const std::string BUILD_TIME = __TIME__;
    static const std::string BUILD_DATE = __DATE__;
};


#endif /* BUILDVARS_H */
