include_directories (${CMAKE_SOURCE_DIR}/src)
include_directories (${EXTERNAL})
add_executable(ConsoleApp "consoleapp.cpp")
target_link_libraries (ConsoleApp SimpleServer)

file(COPY
    C:/Users/Benjamin/Source/Repos/ThreadPool/out/build/x64-Debug/src/ThreadPool.dll
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})