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
gcc -shared -fPIC -o plugins/lib1.so p1.c
gcc -shared -fPIC -o plugins/lib2.so p2.c
iulians@tumbleweed:~/executables/plugin> 
```

Running the application again and loading will show the plugins in the list.
