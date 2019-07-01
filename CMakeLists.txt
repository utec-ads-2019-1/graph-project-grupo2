cmake_minimum_required(VERSION 3.14)
project(graph)

set(CMAKE_CXX_STANDARD 17)
file(GLOB src
        "*.cpp")

set(SFML_INCLUDE_DIR "/home/yoncho/Downloads/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/yoncho/Downloads/SFML-2.5.1/lib")
set(SFML_DIR "/home/yoncho/Downloads/SFML-2.5.1/lib/cmake/SFML")
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()
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
target_link_libraries (graph sfml-graphics sfml-window sfml-system)