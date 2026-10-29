#include "graph_machine.hpp"

#include <utility>

NodeId make_atom(Arena &arena, std::string value, bool active) {
  const NodeId id = arena.nodes.size();
  arena.nodes.push_back(
      Node{id, NodeTag::ATOM, no_node, no_node, std::move(value), active});
  return id;
}

NodeId make_app(Arena &arena, NodeId left, NodeId right, bool active) {
  const NodeId id = arena.nodes.size();
  arena.nodes.push_back(Node{id, NodeTag::APP, left, right, {}, active});
  return id;
}

const Node &get_node(const Arena &arena, NodeId id) {
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

NodeId compile_tree(Arena &arena, const Tree &tree) {
  NodeId root = make_atom(arena, tree.value);

  for (const Tree &child : tree.children) {
    root = make_app(arena, root, compile_tree(arena, child));
  }

  return root;
}
