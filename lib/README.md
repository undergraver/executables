This is an example of dynamic linking and a comparison.

You simply run `make` and see the results

Advantages/Disadvantages:
- static linking avoids the so called dependency hell - https://en.wikipedia.org/wiki/Dependency_hell
- dynamic linking can save some space if multiple executables share code

For a better difference you can modify the shared library so it has multple functions, so the library size increases.

```
iulians@tumbleweed:~/executables/lib> ./biglib.py > common.c 2> common.h
iulians@tumbleweed:~/executables/lib>
```
Then run `make` again and see the results.

```
$ ls -ltr
total 1160
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi    585 Jun 20 14:38 README.md
-rwxr-xr-x 1 MITEL+serbanoi MITEL+serbanoi    294 Jun 20 14:38 biglib.py
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi     94 Jun 20 14:38 main.c
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi  31802 Jun 22 11:00 common.c
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi  17905 Jun 22 11:00 common.h
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi    514 Jun 22 13:38 makefile
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi  88596 Jun 22 13:38 common.o
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi 102618 Jun 22 13:38 libcommon.a
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi 608838 Jun 22 13:38 common.dll.a
-rwxr-xr-x 1 MITEL+serbanoi MITEL+serbanoi 127290 Jun 22 13:38 common.dll
$
```

# Compiling the executables

## static

```
$ gcc main.c libcommon.a -o static
```

## dynamic

### under Windows

```
gcc main.c common.dll.a -o dyn
```

### under linux

Even though the version above with the import lib works on Linux also it is not something Linux gcc needs.

```
gcc main.c -lcommon -L. -o dyn
```

The final results are:

```
$ ls -ltr
total 1160
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi    585 Jun 20 14:38 README.md
-rwxr-xr-x 1 MITEL+serbanoi MITEL+serbanoi    294 Jun 20 14:38 biglib.py
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi     94 Jun 20 14:38 main.c
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi  31802 Jun 22 11:00 common.c
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi  17905 Jun 22 11:00 common.h
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi    514 Jun 22 13:38 makefile
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi  88596 Jun 22 13:38 common.o
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi 102618 Jun 22 13:38 libcommon.a
-rw-r--r-- 1 MITEL+serbanoi MITEL+serbanoi 608838 Jun 22 13:38 common.dll.a
-rwxr-xr-x 1 MITEL+serbanoi MITEL+serbanoi 127290 Jun 22 13:38 common.dll
-rwxr-xr-x 1 MITEL+serbanoi MITEL+serbanoi 118284 Jun 22 13:39 static.exe
-rwxr-xr-x 1 MITEL+serbanoi MITEL+serbanoi  61264 Jun 22 13:40 dyn.exe
```

As we can see the size of the dynamic executable is smaller that the static one and multiple executable would gain some space if the same library is shared between them.

To see the symbols from this library you can use the following `binutils` executables:
* nm
* objdump
* strings

If you are looking for a visual tool you have this under Windows: https://github.com/lucasg/Dependencies
