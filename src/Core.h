//
// Created by ikmokhirio on 26.06.2022.
//

#ifndef DAEDALUS_CORE_H
#define DAEDALUS_CORE_H

#ifdef DAEDALUS_PLATFORM_WINDOWS
    #ifdef DAEDALUS_STATIC_BUILD
        #define DAEDALUS_API
    #else
        #ifdef DAEDALUS_BUILD_DLL
            #define DAEDALUS_API __declspec(dllexport)
        #else
            #define DAEDALUS_API __declspec(dllimport)
        #endif
    #endif
#else
#error "Only windows now"
#endif

#define BIT(x) 1 << x

#endif //DAEDALUS_CORE_H
