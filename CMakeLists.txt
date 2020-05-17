cmake_minimum_required (VERSION 3.8)
set(EXTERNAL ${CMAKE_SOURCE_DIR}/external)
project (SimpleServer)

add_subdirectory (consoleapp)
add_subdirectory(src)