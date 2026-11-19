#include "graph_machine.hpp"

NodeId make_atom(Arena &arena, NodeTag tag, NodeId data, bool is_right) {
  const NodeId id = arena.nodes.size();
  arena.nodes.push_back(Node{id, tag, no_node, no_node, no_node, data, is_right});
  return id;
}

NodeId make_combinator(Arena &arena, NodeTag tag, bool is_right) {
  const NodeId id = arena.nodes.size();
  arena.nodes.push_back(
      Node{id, tag, no_node, no_node, no_node, no_node, is_right});
  return id;
}


NodeId make_app(Arena &arena, NodeId left, NodeId right, bool is_right) {
  const NodeId id = arena.nodes.size();
  arena.nodes.push_back(Node{id, NodeTag::APP, left, right, no_node, {}, is_right});
  return id;
}

const Node &get_node(const Arena &arena, NodeId id) {
  return arena.nodes.at(id);
}

Node &get_node(Arena &arena, NodeId id) {
  return arena.nodes.at(id);
}

void set_cursor(Cursor &cursor, NodeId id) { cursor.current = id; }

void move_left(Cursor &cursor, const Arena &arena) {
  const Node &node = get_node(arena, cursor.current);
  cursor.current = node.left;
}

void move_right(Cursor &cursor, const Arena &arena) {
  const Node &node = get_node(arena, cursor.current);
  cursor.current = node.right;
}

