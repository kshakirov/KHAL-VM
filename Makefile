CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic

.PHONY: all test test_graph clean
all: build_graph test_graph

build_graph: studies/build_graph.C src/graph_machine.C include/graph_machine.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Iinclude studies/build_graph.C src/graph_machine.C -o $@

test_graph: test_graph_ski

test_graph_ski: studies/test_graph_ski.C src/graph_machine.C include/graph_machine.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Iinclude studies/test_graph_ski.C src/graph_machine.C -o $@

test: all
	./build_graph
	./test_graph_ski

clean:
	rm -f build_graph test_graph_ski
