#include "graph_machine.hpp"

#include <cassert>
#include <iostream>

int main() {
  Arena arena;
  const NodeId node_i = make_combinator(arena, NodeTag::I);
  const NodeId node_x = make_atom(arena, NodeTag::INT, 42, true);
  const NodeId root = make_app(arena, node_i, node_x);

  assert(arena.nodes.size() == 3);
  std::cout << "Graph KHAL: root " << root << '\n';
}
