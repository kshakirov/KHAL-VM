#pragma once

#include <cstddef>
#include <limits>
#include <string>
#include <vector>

using NodeId = std::size_t;

inline constexpr NodeId no_node = std::numeric_limits<NodeId>::max();

enum class NodeTag { ATOM, APP };

struct Node {
  const NodeId id;
  NodeTag tag;
  NodeId left;
  NodeId right;
  std::string value;
  bool active;
};

struct Arena {
  std::vector<Node> nodes;
};

struct Cursor {
  NodeId current;
};

struct Tree {
  std::string value;
  std::vector<Tree> children;
};

NodeId make_atom(Arena &arena, std::string value, bool active = false);
NodeId make_app(Arena &arena, NodeId left, NodeId right,
                bool active = false);
const Node &get_node(const Arena &arena, NodeId id);

void set_cursor(Cursor &cursor, NodeId id);
void move_left(Cursor &cursor, const Arena &arena);
void move_right(Cursor &cursor, const Arena &arena);

NodeId compile_tree(Arena &arena, const Tree &tree);
