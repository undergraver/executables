# executables
This repository contains basic samples to understand what an applications is made of and how to do that

NOTE: This is mainly thought as an example of using GNU Tools to develop applications under a cross platform environment.
# Installation of environment
## Under Linux (or WSL under Windows)
Just install these packages on your distribution (adapt `zypper` SUSE package manager to your distribution - for example in Ubuntu that is `apt`)

`zypper install gcc gcc-c++ make gettext-tools git`

## Under Windows

1. Install Msys from here: https://www.msys2.org/
2. Start the Msys shell and type this command: `pacman -S -y -u` (this upgrades the packages and updates the list of packages)
3. Install the packages required for this repository: `pacman -S make gcc gettext git`

After these steps you will have install gcc/g++/make and gettext (used for L10N and I18N) and git to clone this repo.

Please note that `pacman` provides a lot of packages, libraries that can be used in development.
Please mind that gcc offers multiple environment choices like presented here: https://www.msys2.org/docs/environments/
Some environments use gcc, other clang, other have different dependencies.

### Useful pacman commands
* update list of packages `pacman -Sy`
* seach for packages `pacman -Ss <text>`
* list installed packages `pacman -Q`
* list contents of package `pacman -Q -l <package>`
* help for `pacman`
  * `pacman -h` - base help
  * `pacman -S -h` - details option help (for -S option)

# Why gcc/g++, make etc?

Because it is free / open source and testing it requires no additional costs for you. You are either way free to use whatever tools/toolchains you want as long as you adapt the code to that particular environment, if needed.

At this step you should have a build environment you can use to develop applications.


We will use make (and makefiles) in order to build out project. This makes it easier to just issue a command that includes multiple files and yields multiple exectuables and/or libraries used by executables.

# What some program suite has

## Executables
Creating an executable is quite easy, we don't need to do anything special.

## Dynamic link libraries (dll) / shared objects (so)

Usually when a application suite offers multiple executables when installed it is always a good thing to have the code shared between them, if needed. This can be achieved with DLLs/SOs. This is the basic use of DLLs, to avoid code redundancy.

### DLL as shared code
The simple way of using DLLs is by putting common thing into one place, and use them via a DLL (dynamic linking).

### DLL as plugin
Plugins are DLLs that are not necessarily linked dynamically to one or more executables but instead they are loaded dynamically at runtime. This means that you can extend the functionality of a program without recompiling the program.
