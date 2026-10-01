
GCC=g++
FLAGS=-std=c++23
#FLAGS=-std=c++23 -fmodules-ts 

all:
	$(GCC) main.C   frontend.C vm.C  -o main    $(FLAGS)

parser: parser.C include/khal_types.hpp
	$(GCC) parser.C -o parser $(FLAGS)

