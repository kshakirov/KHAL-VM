#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>
#include <iostream>

using NodeId = int32_t;

enum State { DESCENDING, ASCENDING };

inline constexpr NodeId no_node = std::numeric_limits<NodeId>::max();

enum class NodeTag { ATOM, APP, I,K,S, REF, INT };

struct Node {
  const NodeId id;
  NodeTag tag; 
  NodeId left;
  NodeId right;
  NodeId back;
  NodeId data;
  bool is_right;
};

struct Arena {
  std::vector<Node> nodes;
};

struct Cursor {
  NodeId current;
};

NodeId make_atom(Arena &arena, NodeTag tag, NodeId data = no_node,
                 bool is_right = false);
NodeId make_combinator(Arena &arena, NodeTag tag, bool is_right = false);
NodeId make_app(Arena &arena, NodeId left, NodeId right,
                bool is_right = false);
const Node &get_node(const Arena &arena, NodeId id);
Node &get_node(Arena &arena, NodeId id);

void set_cursor(Cursor &cursor, NodeId id);
void move_left(Cursor &cursor, const Arena &arena);
void move_right(Cursor &cursor, const Arena &arena);
void reduce(Cursor& cursor,  Arena& arena);
