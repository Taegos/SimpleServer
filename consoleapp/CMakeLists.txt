include_directories (${CMAKE_SOURCE_DIR}/src)
include_directories (${CMAKE_SOURCE_DIR}/external)
add_executable(ConsoleApp "consoleapp.cpp")
target_link_libraries (ConsoleApp SimpleServer)