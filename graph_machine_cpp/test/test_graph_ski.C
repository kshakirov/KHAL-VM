#include "../include/graph_machine.hpp"
#include <cassert>
#include <iostream>
#include <variant>
using std::cout;
using std::endl;

enum State{
  DESCENDING,
  ASCENDING
};



int main(void){
  cout << "Working wit SKI combinators" << endl;
  Arena arena;
  auto node_i = make_atom(arena, "I", false);
  auto node_x = make_atom(arena, "x", true);
  auto node_app = make_app(arena, node_i, node_x);
  assert(arena.nodes.size() == 3);
  int i = 0;
  auto state = State::DESCENDING;
  Cursor cursor;
  auto wip = true;
  NodeId parent;
  auto root = node_app;
  auto reduct = no_node;
  set_cursor(cursor, root);
  while (i < 5 && wip) {
    switch (state) {
    case DESCENDING: {
      auto node = get_node(arena, cursor.current);
      if(node.tag == NodeTag::APP){
	set_cursor(cursor,node.left);
	parent = node.id;
	cout << "Tag is  APP"  <<endl;
      }else{
	if(node.value == "I"){
	  node.back = parent;
	  set_cursor(cursor, node.right);
	  parent = node.id;
	  cout << "I combinator  "  << node.value <<endl;
	}else if (node.is_right) {
	  if(node.tag == NodeTag::ATOM){
	    node.back  = parent;
	    reduct = node.id;
	    state = ASCENDING;
	    cout << "Right atom  "  << node.value <<endl;
	  }
	  
	    }
      }
      i += 1;
      break;
    }
    case ASCENDING: {
      auto node = get_node(arena, cursor.current);

      set_cursor(cursor,node.back);
            i += 1;
	    break;
    }
    default: {
      i += 1;
    }

    }
  }
}
