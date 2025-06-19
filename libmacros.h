#pragma once

#ifdef _WIN32
  #ifdef BUILD_DLL
    #define DECL_API __declspec(dllexport)
  #else
    #define DECL_API __declspec(dllimport)
  #endif
#else
  #define DECL_API
#endif


#ifdef __cplusplus
#define DEMANGLE extern "C"
#else
#define DEMANGLE
#endif
