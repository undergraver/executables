#include <dirent.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

static int has_so_suffix(const char *name) {
    const char *dot = strrchr(name, '.');
    return dot && strcmp(dot, ".so") == 0;
}

#define PLUGINS_DIR "./plugins"

vector<string> getPluginPaths() {
    vector<string> paths;
    const char *dir_path = PLUGINS_DIR;
    DIR *dir = opendir(dir_path);
    if (!dir) {
        const char *err = strerror(errno); 
	fprintf(stderr,"Dir %s couldn't be open:%s\n",dir_path,err);
        return paths;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (!has_so_suffix(ent->d_name))
            continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dir_path, ent->d_name);
	printf("Adding %s\n",fullpath);
	paths.push_back(fullpath);
    }

    closedir(dir);
    return paths;
}

struct plugin {
    string so_path;
    string plugin_name;
    typedef void (*action_fn)(void);
    action_fn action;
    plugin(const string &so_path_) : so_path(so_path_) {
        handle = dlopen(so_path.c_str(),RTLD_LAZY);
	if (handle != NULL) {
		name = (name_fn)dlsym(handle,"name");
		if (name != NULL) {
			plugin_name = name();
		}
		else {
			fprintf(stderr, "couldn't resolve 'name' symbol:%s\n",dlerror());
		}
		action = (action_fn)dlsym(handle,"action");
		if (action == NULL) {
			fprintf(stderr, "couldn't resolve 'action' symbol:%s\n",dlerror());
		}
	}
	else {
		fprintf(stderr, "library couldn't be loaded:%s\n",dlerror());
	}
    }
    ~plugin() {
	    if (handle != NULL) dlclose(handle);
    }
    bool isValid() const {
	    if (handle == NULL) return false;
	    if (name == NULL) return false;
	    if (action == NULL) return false;
	    return true;
    }
private:
    plugin(const plugin&);                 // Prevent copy-construction
    plugin& operator=(const plugin&);      // Prevent assignment
    void *handle;
    typedef char *(*name_fn)(void);
    name_fn name;
};

vector<plugin*> loadedPlugins;

static int get_option(void) {
    puts("\n== Plugin Loader ==");
    puts("1) Load/Reload plugins");
    puts("2) Exit");
    for (size_t i=0;i<loadedPlugins.size();++i) {
        char c = '3'+i;
	auto & p = loadedPlugins[i];
	printf("%c) execute %s (%s)\n",c,p->plugin_name.c_str(),p->so_path.c_str());
    }
    printf("Select: ");
    int option = 0;
    scanf("%d",&option);
    return option;
}

static void handle_option(int op) {
   op-=3; 
   if (op >= loadedPlugins.size()) {
	   fprintf(stderr,"Invalid option");
   }
   else {
	   auto &p = loadedPlugins[op];
	   p->action();
   }
}

void loadPlugins() {
	// free all the loaded plugins
	for (auto p : loadedPlugins) {
		delete p;
	}
	auto libs = getPluginPaths();
	for(auto& lib : libs) {
		auto p = new plugin(lib);
		if (p->isValid()) {
			loadedPlugins.push_back(p);
		}
		else {
			delete p;
		}
	}	
}

int main(int argc, char **argv) {
    int option = 0;
    
    while (option != 2) {

        option = get_option();
        if (option == 1) {
            loadPlugins();
        }
        else if (option == 2) {
            break;
        }
	else {
		handle_option(option);
	}
    }

    return 0;
}
