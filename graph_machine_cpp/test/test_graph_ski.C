#include "../include/graph_machine.hpp"
#include <cassert>
#include <iostream>
#include <ostream>
#include <variant>
using std::cout;
using std::endl;

enum State { DESCENDING, ASCENDING };

int main(void) {
  cout << "Working wit SKI combinators" << endl;
  Arena arena;
  auto node_i = make_combinator(arena, NodeTag::I, false);
  auto node_x = make_atom(arena, NodeTag::INT, 42, true);
  auto node_app = make_app(arena, node_i, node_x);
  auto node_y = make_atom(arena, NodeTag::INT, 54, true);
  auto node_app_1 = make_app(arena, node_app, node_y);
  assert(arena.nodes.size() == 5);
  int i = 0;
  auto state = State::DESCENDING;
  Cursor cursor;
  auto wip = true;
  NodeId parent;
  auto root = node_app_1;
  parent = root;
  auto reduct = no_node;
  set_cursor(cursor, root);
  while (i < 5 && wip) {
    auto& node = get_node(arena, cursor.current);
    switch (state) {
    case DESCENDING: {
      switch (node.tag) {
      case NodeTag::APP: {
	node.back = parent;
        set_cursor(cursor, node.left);
        parent = node.id;
        cout << "APP" << endl;
        break;
      }
      case NodeTag::I: {
        node.back = parent;
        set_cursor(cursor, node.back);
        state = ASCENDING;
        cout << "I getting back to APP" << endl;
        break;
      }
      case NodeTag::ATOM: {
        break;
      }
      default: {
        cout << "Descending: Default " << endl;
      }
      }
      break;
    }
    case ASCENDING: {
      switch (node.tag) {
      case NodeTag::APP: {
        reduct = node.right;

        cout << "APP again" << endl;
        if (node.id == root) {
          root = reduct;
          wip = false;
          set_cursor(cursor, root);
        } else {
          set_cursor(cursor, node.back);
        }

        break;
      }
      default: {
        cout << "Ascending: Default " << endl;
        break;
      }
      }
      break;
    }
    }
    i += 1;
  }

  cout << cursor.current << endl;
  auto node = get_node(arena, cursor.current);
  assert(root == node.id);
}
