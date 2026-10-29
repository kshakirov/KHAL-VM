CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic

graph_khal: src/main.C src/graph_machine.C include/graph_machine.hpp
	$(CXX) $(CXXFLAGS) -Iinclude src/main.C src/graph_machine.C -o graph_khal

test: graph_khal
	./graph_khal

clean:
	rm -f graph_khal
