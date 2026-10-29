#include "graph_machine.hpp"

#include <cassert>
#include <iostream>

int main() {
  Arena arena;

  const NodeId add = make_atom(arena, "ADD");
  const NodeId one = make_atom(arena, "1");
  const NodeId two = make_atom(arena, "2");
  const NodeId add_one = make_app(arena, add, one);
  const NodeId root = make_app(arena, add_one, two, true);

  assert(get_node(arena, root).left == add_one);
  assert(get_node(arena, root).right == two);
  assert(get_node(arena, add_one).left == add);
  assert(get_node(arena, add_one).right == one);
  assert(get_node(arena, root).active);

  Cursor cursor{root};
  move_left(cursor, arena);
  assert(cursor.current == add_one);
  move_left(cursor, arena);
  assert(cursor.current == add);

  set_cursor(cursor, root);
  move_right(cursor, arena);
  assert(cursor.current == two);

  std::cout << "Graph KHAL: skeleton test passed\n";
}
