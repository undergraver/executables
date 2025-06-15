ifeq ($(OS),Windows_NT)
    #Windows
    EXE_EXTENSION=.exe
    DLL_PREFIX=
    DLL_EXTENSION=.dll
    LIB_FLAGS=-DBUILD_DLL
else
    #Linux
    EXE_EXTENSION=
    DLL_PREFIX=lib
    DLL_EXTENSION=.so
    LIB_FLAGS=-fPIC
endif
