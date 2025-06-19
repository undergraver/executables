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


