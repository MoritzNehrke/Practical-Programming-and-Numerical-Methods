CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt
	cat $<

Out.txt: main
	./$< > $@

main: main.o
main.o: vec.h
vec.o: vec.h

clean :
	rm -f *.o main Out.txt
