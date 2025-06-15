#!/usr/bin/env python3
import sys

maximum=1000

print("#pragma once\n\n",file=sys.stderr)
for i in range(maximum):
    print("int common"+str(i)+"();\n",file=sys.stderr)


print("#include \"common.h\"\n\n")
for i in range(maximum):
    print("int common"+str(i)+"() {\nreturn "+str(i)+";\n}")
