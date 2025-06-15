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
