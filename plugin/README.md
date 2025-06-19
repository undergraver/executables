Modern operating systems provide means to load libraries dynamically.

This is a very important concept. This means that a program can in theory load such libraries and extend its functionality.

It is the base for extensions for various software, libraries etc.

For example by creating such DLLs you can extend with extra functionality:
- Python
- Java
- Perl
- Lua
- ...

You can also add plugins/extensions to the application without compiling (sometimes even without restarting it as we'll see in our example). 

Examples of applications are:
- notepad++
- vscode
- modern web browsers
- ...

# compiling the main program
Here we have a main.cpp file which contains some primitives (they work only in Linux at the moment).

Let's initially compile the program and test to see how it looks. It is better to have two terminals open to play with it but not mandatory.

```
make clean all
./main
iulians@tumbleweed:~/executables/plugin> ./main

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
Select: 1
Dir ./plugins couldn't be open:No such file or directory

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
Select: 2
iulians@tumbleweed:~/executables/plugin>
```

As we see it suggests it searches for plugins in the plugins directory.

# making the plugins

The plugins will be very simple in order to quickly test them.

```
iulians@tumbleweed:~/executables/plugin> make plugins_ok
mkdir plugins
gcc -shared -fPIC -o plugins/lib1.so p1.c
gcc -shared -fPIC -o plugins/lib2.so p2.c
```


Running the application again and loading will show the plugins in the list.

```
iulians@tumbleweed:~/executables/plugin> make all
g++ -Wall -o main main.cpp -ldl
iulians@tumbleweed:~/executables/plugin> ./main

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
Select: 1
Adding ./plugins/lib1.so
Adding ./plugins/lib2.so

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
3) execute First plugin (./plugins/lib1.so)
4) execute 2nd plugin (./plugins/lib2.so)
Select:
```

We can also have plugins that don't have all the symbols or ar invalid and this is how it goes:

```
iulians@tumbleweed:~/executables/plugin> make plugins_bad
gcc -shared -fPIC -o plugins/libnosym.so nosym.c
gcc -shared -fPIC -o plugins/libonesym.so onesym.c
touch plugins/libempty.so
iulians@tumbleweed:~/executables/plugin> ./main

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
Select: 1
Adding ./plugins/lib1.so
Adding ./plugins/lib2.so
Adding ./plugins/libnosym.so
Adding ./plugins/libonesym.so
Adding ./plugins/libempty.so
couldn't resolve 'name' symbol:./plugins/libnosym.so: undefined symbol: name
couldn't resolve 'action' symbol:./plugins/libnosym.so: undefined symbol: action
couldn't resolve 'name' symbol:./plugins/libonesym.so: undefined symbol: name
library couldn't be loaded:./plugins/libempty.so: file too short

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
3) execute First plugin (./plugins/lib1.so)
4) execute 2nd plugin (./plugins/lib2.so)
Select:
```

# mangling and unmangling

We have some extra cases that are usually very difficult to trace, related to what we mentioned in other sessions: name mangling (https://en.wikipedia.org/wiki/Name_mangling). We will see how we can use the tools provided by the compiler to understand what is going on

```
iulians@tumbleweed:~/executables/plugin> make plugins_extra
g++ -shared -fPIC -o plugins/libmangled.so mangled.cpp
g++ -shared -fPIC -I.. -o plugins/libdemangled.so demangled.cpp
iulians@tumbleweed:~/executables/plugin> ./main

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
Select: 1
Adding ./plugins/lib1.so
Adding ./plugins/lib2.so
Adding ./plugins/libnosym.so
Adding ./plugins/libonesym.so
Adding ./plugins/libempty.so
Adding ./plugins/libmangled.so
Adding ./plugins/libdemangled.so
couldn't resolve 'name' symbol:./plugins/libnosym.so: undefined symbol: name
couldn't resolve 'action' symbol:./plugins/libnosym.so: undefined symbol: action
couldn't resolve 'name' symbol:./plugins/libonesym.so: undefined symbol: name
library couldn't be loaded:./plugins/libempty.so: file too short
couldn't resolve 'name' symbol:./plugins/libmangled.so: undefined symbol: name
couldn't resolve 'action' symbol:./plugins/libmangled.so: undefined symbol: action

== Plugin Loader ==
1) Load/Reload plugins
2) Exit
3) execute First plugin (./plugins/lib1.so)
4) execute 2nd plugin (./plugins/lib2.so)
5) execute demangled (./plugins/libdemangled.so)
Select:

```

Even both functions are defined in libmangled.so (see mangled.cpp) they are not working as it is compiled with C++

```
iulians@tumbleweed:~/executables/plugin> cat mangled.cpp
#include <stdio.h>

const char* name()
{
        return "test";
}

void action(void)
{
        printf("This is the action.\n");
}
iulians@tumbleweed:~/executables/plugin>
```

Using `nm` would tell us the reason behind the failure, comparing it with one that works:
```
iulians@tumbleweed:~/executables/plugin> nm plugins/libmangled.so
0000000000004010 b completed.0
                 w __cxa_finalize@GLIBC_2.2.5
0000000000001050 t deregister_tm_clones
00000000000010c0 t __do_global_dtors_aux
0000000000003dc0 d __do_global_dtors_aux_fini_array_entry
0000000000004008 d __dso_handle
0000000000003dc8 d _DYNAMIC
000000000000112c t _fini
0000000000001100 t frame_dummy
0000000000003db8 d __frame_dummy_init_array_entry
00000000000020e0 r __FRAME_END__
0000000000003fe8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
000000000000201c r __GNU_EH_FRAME_HDR
0000000000001000 t _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U puts@GLIBC_2.2.5
0000000000001080 t register_tm_clones
0000000000004010 d __TMC_END__
0000000000001109 T _Z4namev
0000000000001116 T _Z6actionv
iulians@tumbleweed:~/executables/plugin>
iulians@tumbleweed:~/executables/plugin> nm plugins/libmangled.so
0000000000004010 b completed.0
                 w __cxa_finalize@GLIBC_2.2.5
0000000000001050 t deregister_tm_clones
00000000000010c0 t __do_global_dtors_aux
0000000000003dc0 d __do_global_dtors_aux_fini_array_entry
0000000000004008 d __dso_handle
0000000000003dc8 d _DYNAMIC
000000000000112c t _fini
0000000000001100 t frame_dummy
0000000000003db8 d __frame_dummy_init_array_entry
00000000000020e0 r __FRAME_END__
0000000000003fe8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
000000000000201c r __GNU_EH_FRAME_HDR
0000000000001000 t _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U puts@GLIBC_2.2.5
0000000000001080 t register_tm_clones
0000000000004010 d __TMC_END__
0000000000001109 T _Z4namev
0000000000001116 T _Z6actionv
iulians@tumbleweed:~/executables/plugin>
iulians@tumbleweed:~/executables/plugin> nm plugins/lib1.so
0000000000001116 T action
0000000000004010 b completed.0
                 w __cxa_finalize@GLIBC_2.2.5
0000000000001050 t deregister_tm_clones
00000000000010c0 t __do_global_dtors_aux
0000000000003df0 d __do_global_dtors_aux_fini_array_entry
0000000000004008 d __dso_handle
0000000000003df8 d _DYNAMIC
000000000000112c t _fini
0000000000001100 t frame_dummy
0000000000003de8 d __frame_dummy_init_array_entry
00000000000020f0 r __FRAME_END__
0000000000003fe8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000002028 r __GNU_EH_FRAME_HDR
0000000000001000 t _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000001109 T name
                 U puts@GLIBC_2.2.5
0000000000001080 t register_tm_clones
0000000000004010 d __TMC_END__
iulians@tumbleweed:~/executables/plugin> nm plugins/lib1.so | grep " T "
0000000000001116 T action
0000000000001109 T name
iulians@tumbleweed:~/executables/plugin> nm plugins/libmangled.so | grep " T "
0000000000001109 T _Z4namev
0000000000001116 T _Z6actionv
iulians@tumbleweed:~/executables/plugin>

```

In order to avoid this we can use the `extern "C"` for these functions. We already did this in a header that can be used depending on how you code:
```
iulians@tumbleweed:~/executables/plugin> grep cplusplus -A4 ../libmacros.h
#ifdef __cplusplus
#define DEMANGLE extern "C"
#else
#define DEMANGLE
#endif
iulians@tumbleweed:~/executables/plugin>

```

And we use that macro in the demangle.cpp code:
```
iulians@tumbleweed:~/executables/plugin> cat demangled.cpp
#include <stdio.h>
#include "libmacros.h"

DEMANGLE const char* name()
{
        return "demangled";
}

DEMANGLE void action(void)
{
        printf("Demangling in action.\n");
}
iulians@tumbleweed:~/executables/plugin>
```
