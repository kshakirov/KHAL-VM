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

void reduce(Cursor& cursor, Arena& arena){
  int i = 0;
  auto state = State::DESCENDING;
  //Cursor cursor;
  auto wip = true;
  NodeId parent;
  auto root = cursor.current;
  parent = root;
  //auto reduct = no_node;
  auto use_i_reduct = false;
  //set_cursor(cursor, root);
  while (i < 5 && wip) {
    auto& node = get_node(arena, cursor.current);
    switch (state) {
    case DESCENDING: {
      switch (node.tag) {
      case NodeTag::APP: {
	node.back = parent;
        set_cursor(cursor, node.left);
        parent = node.id;
        std::cout << "APP" << std::endl;
        break;
      }
      case NodeTag::I: {
        node.back = parent;
        set_cursor(cursor, node.back);
	use_i_reduct = true;
        state = ASCENDING;
        std::cout << "I getting back to APP" << std::endl;
        break;
      }
      case NodeTag::ATOM: {
        break;
      }
      default: {
        std::cout << "Descending: Default " << std::endl;
      }
      }
      break;
    }
    case ASCENDING: {
      switch (node.tag) {
      case NodeTag::APP: {
	if(use_i_reduct && node.id != root){
	  auto& outer = get_node(arena, node.back);
	  outer.left = node.right;
	  use_i_reduct = false;
	}


        if (node.id == root && use_i_reduct) {
          root = node.right;
          wip = false;
	  use_i_reduct = false; 
          set_cursor(cursor, root);
        } else {
          set_cursor(cursor, node.back);
        }

        break;
      }
      default: {

        break;
      }
      }
      break;
    }
    }
    i += 1;
  }

  
}

