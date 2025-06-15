include ../general.make
STATIC_LIB=libcommon.a
DYNAMIC_LIB=$(DLL_PREFIX)common$(DLL_EXTENSION)
COMMON_OBJ=common.o

all: static dynamic
static: $(STATIC_LIB)
$(STATIC_LIB): $(COMMON_OBJ)
	ar rcs $(STATIC_LIB) $(COMMON_OBJ)

$(COMMON_OBJ): common.c common.h
	gcc $(LIB_FLAGS) -c common.c -o $(COMMON_OBJ)

dynamic: $(DYNAMIC_LIB)

$(DYNAMIC_LIB): $(COMMON_OBJ)
	gcc -shared $(COMMON_OBJ) -o $(DYNAMIC_LIB)

clean:
	rm -f $(COMMON_OBJ) $(STATIC_LIB) $(DYNAMIC_LIB)
