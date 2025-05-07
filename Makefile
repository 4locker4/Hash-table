CC = g++

CFLAGS = -c -O3 -msse4.2 -mavx -mavx2 -masm=intel -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline		\
	-Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default		    		\
	-Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy            	\
	-Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers 	\
	-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing   	\
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

RELEASEFLAGS = -c -O0 -msse4.2 -mavx -mavx2 -masm=intel -D NDEBUG 

INCLUDES = ./inc/HashMain.hpp ./DL_list/inc/Errors.h ./DL_list/inc/header.h ./DL_list/inc/Utils.h 					\
		   ./DL_list/inc/Asserts.h ./inc/Parsing.hpp

SOURCES = ./src/HashMain.cpp ./DL_list/src/main.cpp ./DL_list/src/Utils.cpp ./DL_list/src/list.cpp 					\
		  ./src/FilePreparingPars.cpp ./src/avx_strcmp.cpp ./src/src32_hash_opt.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = hashtable.exe

all: $(SOURCES) $(INCLUDES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

.cpp.o: $(INCLUDES) $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

rn:
	./hashtable.exe

clean:
	rm -rf ./src/*.o
	rm -rf *.exe