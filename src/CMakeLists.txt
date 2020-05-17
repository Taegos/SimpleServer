include_directories (${CMAKE_SOURCE_DIR}/external)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SimpleServer "SimpleServer.cpp")
target_link_libraries (SimpleServer ${CMAKE_SOURCE_DIR}/external/threadpool/lib/ThreadPool.lib)