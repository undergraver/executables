include ../general.make

MAIN=main
PLUGIN_DIR=plugins
all: $(MAIN)
$(MAIN): main.cpp
	g++ -Wall -o main main.cpp -ldl
clean:
	rm -f $(MAIN) *.so a.out

$(PLUGIN_DIR):
	mkdir $(PLUGIN_DIR)

plugins_ok: $(PLUGIN_DIR)
	gcc -shared $(LIB_FLAGS) -o $(PLUGIN_DIR)/lib1.so p1.c
	gcc -shared $(LIB_FLAGS) -o $(PLUGIN_DIR)/lib2.so p2.c

plugins_bad: $(PLUGIN_DIR)
	gcc -shared $(LIB_FLAGS) -o $(PLUGIN_DIR)/libnosym.so nosym.c
	gcc -shared $(LIB_FLAGS) -o $(PLUGIN_DIR)/libonesym.so onesym.c
	touch $(PLUGIN_DIR)/libempty.so

# we compile them with c++ with no consideration
plugins_mangled: $(PLUGIN_DIR)

# we compile them with c++ but more careful
plugins_unmangled: $(PLUGIN_DIR)
