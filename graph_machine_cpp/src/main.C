#include "graph_machine.hpp"

#include <cassert>
#include <iostream>

int main() {
  const Tree program{
      "PROGRAM",
      {{"SCOPE",
        {{"A", {}},
         {"BIND", {{"x", {}}, {"10", {}}}},
         {"BIND",
          {{"plus", {}},
           {"LAMBDA",
            {{"y", {}},
             {"APP",
              {{"APP",
                {{"ADD", {}}, {"RESOLVE", {{"A", {}}, {"x", {}}}}}},
               {"y", {}}}}}}}}}},
       {"BIND",
        {{"result", {}},
         {"APP",
          {{"RESOLVE", {{"A", {}}, {"plus", {}}}}, {"5", {}}}}}}}};

  Arena arena;
  const NodeId root = compile_tree(arena, program);

  assert(arena.nodes.size() == 47);
  assert(get_node(arena, root).tag == NodeTag::APP);

  Cursor cursor{root};
  move_left(cursor, arena);
  move_left(cursor, arena);

  const Node &program_atom = get_node(arena, cursor.current);
  assert(program_atom.tag == NodeTag::ATOM);
  assert(program_atom.value == "PROGRAM");

  set_cursor(cursor, root);
  move_right(cursor, arena);
  const Node &result_binding = get_node(arena, cursor.current);
  assert(result_binding.tag == NodeTag::APP);

  std::cout << "Graph KHAL: tree compiled to " << arena.nodes.size()
            << " graph nodes\n";
}
