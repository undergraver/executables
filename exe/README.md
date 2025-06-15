Compiling this project is done via a simple `make` that uses the information from `makefile` in order to do everything required.
Makefiles can be seen as file with targets and dependencies.

```
$ cat makefile
include ../general.make
EXE=example$(EXE_EXTENSION)

$(EXE): main.c
        gcc main.c -o $(EXE)
clean:
        rm -f $(EXE)

$
```

In this file we have the EXE target (example.exe) depending on main.c file and the clean target that has no dependency and cleans all the compilation results.

To see the dependencies you can use the `ldd` command from Msys shell.
```
$ ldd example.exe
        ntdll.dll => /c/Windows/SYSTEM32/ntdll.dll (0x7ffefbb90000)
        KERNEL32.DLL => /c/Windows/System32/KERNEL32.DLL (0x7ffefa500000)
        KERNELBASE.dll => /c/Windows/System32/KERNELBASE.dll (0x7ffef9260000)
        msys-2.0.dll => /usr/bin/msys-2.0.dll (0x180040000)
$
```

For Windows there is also a visual tool that can be used called "Dependencies" that can be downloaded from here: https://github.com/lucasg/Dependencies
