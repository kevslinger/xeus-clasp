

#ifndef XCLASP_CONFIG_HPP
#define XCLASP_CONFIG_HPP

// Project version
#define XCLASP_VERSION_MAJOR 0
#define XCLASP_VERSION_MINOR 0
#define XCLASP_VERSION_PATCH 0

// Composing the version string from major, minor and path
#define XCLASP_CONCATENATE(A, B) XPYT_CONCATENATE_IMPL(A, B)
#define XCLASP_CONCATENATE_IMPL(A, B) A##B
#define XCLASP_STRINGIFY(a) XCLASP_STRINGIFY_IMPL(a)
#define XCLASP_STRINGIFY_IMPL(a) #a

#define XCLASP_VERSION XCLASP_STRINGIFY(XCLASP_CONCATENATE(XCLASP_VERSION_MAJOR,    \
                  XCLASP_CONCATENATE(.,XCLASP_CONCATENATE(XCLASP_VERSION_MINOR,    \
                                       XCLASP_CONCATENATE(., XCLASP_VERSION_PATCH)))))

#ifdef _WIN32
    #ifdef XEUS_CLASP_EXPORTS
        #define XEUS_CLASP_API __declspec(dllexport)
    #else
        #define XEUS_CLASP_API __declspec(dllimport)
    #endif
#else
    #define XEUS_CLASP_API
#endif


#endif
