# --------------------------------------------- 
# Makefile for a "Hello, World!" C++ program
# ---------------------------------------------

# We choose clang++ as the C++ compiler
CXX = clang++
# We choose which warnings and standards to enforce
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
# We specify the linker
LINK.o = $(CXX) $(LDFLAGS)
# We add the standard library and math library
LDFLAGS += -lstdc++ -lm

Out.txt : hello 
	./hello > Out.txt

hello : hello.cc
	c++ -o hello hello.cc

clean :
	rm -f hello Out.txt