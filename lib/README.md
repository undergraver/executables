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

Examples of using these tools:
```
$ nm common.dll | grep -E "common[0-9]+" | head
0000000575991030 T common0
000000057599103b T common1
000000057599109e T common10
000000057599147c T common100
0000000575991487 T common101
0000000575991492 T common102
000000057599149d T common103
00000005759914a8 T common104
00000005759914b3 T common105
00000005759914be T common106
$
```
Here we can see the functions defined in the dll file. The same can be achieved with `objdump`
```
$ objdump -t common.dll | grep -E "common[0-9]+" | head
[ 19](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 1) 0x0000000000000030 common0
[ 21](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x000000000000003b common1
[ 22](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x0000000000000046 common2
[ 23](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x0000000000000051 common3
[ 24](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x000000000000005c common4
[ 25](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x0000000000000067 common5
[ 26](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x0000000000000072 common6
[ 27](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x000000000000007d common7
[ 28](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x0000000000000088 common8
[ 29](sec  1)(fl 0x00)(ty   20)(scl   2) (nx 0) 0x0000000000000093 common9

```
or with `strings`

$ strings common.dll | grep -E "common[0-9]+" | head
common0
common1
common10
common100
common101
common102
common103
common104
common105
common106
$
```
