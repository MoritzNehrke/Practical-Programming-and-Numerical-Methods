CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror
LDLIBS += -lm

main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean

clean:
	rm -f main.o erf_tab.dat gamma_tab.dat lgamma_tab.dat