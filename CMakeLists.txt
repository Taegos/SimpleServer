cmake_minimum_required (VERSION 3.8)

project (SimpleServer)
set(EXTERNAL ${CMAKE_SOURCE_DIR}/external)

add_subdirectory (consoleapp)
add_subdirectory(src)