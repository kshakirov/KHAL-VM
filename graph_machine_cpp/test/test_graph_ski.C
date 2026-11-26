#include "../include/graph_machine.hpp"
#include <cassert>
#include <iostream>
#include <ostream>
#include <variant>
using std::cout;
using std::endl;



int main(void) {
  cout << "Working wit SKI combinators" << endl;
  Arena arena;
  auto node_i = make_combinator(arena, NodeTag::I, false);
  auto node_x = make_atom(arena, NodeTag::INT, 42, true);
  auto node_app = make_app(arena, node_i, node_x);
  auto node_y = make_atom(arena, NodeTag::INT, 54, true);
  auto node_app_1 = make_app(arena, node_app, node_y);
  assert(arena.nodes.size() == 5);
  reduce(node_app_1, arena);
  //  cout << cursor.current << endl;
  //auto node = get_node(arena, cursor.current);
  //assert(root == node.id);
}
