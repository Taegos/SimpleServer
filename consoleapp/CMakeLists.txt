include_directories (${CMAKE_SOURCE_DIR}/src)
include_directories (${EXTERNAL}/headers)

add_executable(ConsoleApp "consoleapp.cpp")
target_link_libraries (ConsoleApp SimpleServer)

file(COPY
    C:/Users/Benjamin/Source/Repos/ThreadPool/out/build/x64-Debug/src/ThreadPool.dll
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY
    C:/Users/Benjamin/Source/Repos/ThreadPool/out/build/x64-Debug/src/ThreadPool.lib
    DESTINATION ${EXTERNAL}/libs)

file(COPY
    C:/Users/Benjamin/Source/Repos/ThreadPool/src/headers
    DESTINATION ${EXTERNAL}/)

file(COPY
    C:/Users/Benjamin/Source/Repos/SimpleNetworkExceptions/SimpleNetworkExceptions/SimpleNetworkExceptions.h
    DESTINATION ${EXTERNAL}/headers)

file(COPY
    C:/Users/Benjamin/Source/Repos/SimpleLogger/SimpleLogger/SimpleLogger.h
    DESTINATION ${EXTERNAL}/headers)