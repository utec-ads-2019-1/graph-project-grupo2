file(REMOVE_RECURSE
  "CMakeCache.txt"
  "CMakeFiles/"
  "Makefile"
  "cmake_install.cmake"
  "compile_commands.json"
  "CMakeFiles/graph.dir/main.cpp.o"
  "graph.pdb"
  "graph"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/graph.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
