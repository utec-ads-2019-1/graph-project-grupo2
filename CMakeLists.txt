cmake_minimum_required(VERSION 3.14)
project(graph)

set(CMAKE_CXX_STANDARD 17)
file(GLOB src
	"*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(DIRECTORY APPEND PROPERTY
	ADDITIONAL_MAKE_CLEAN_FILES
	"CMakeCache.txt"
	"CMakeFiles/"
	"Makefile"
	"cmake_install.cmake"
	"compile_commands.json"
	)

add_executable(graph ${src})
