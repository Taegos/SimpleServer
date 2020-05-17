include_directories (${EXTERNAL})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SimpleServer "SimpleServer.cpp")

target_link_libraries (SimpleServer ${EXTERNAL}/threadpool/ThreadPool.lib)

file(COPY
    C:/Users/Benjamin/Source/Repos/ThreadPool/src/headers
    DESTINATION ${EXTERNAL}/threadpool)

file(COPY
    C:/Users/Benjamin/Source/Repos/SimpleNetworkExceptions/SimpleNetworkExceptions/SimpleNetworkExceptions.h
    DESTINATION ${EXTERNAL}/headeronly)

file(COPY
    C:/Users/Benjamin/Source/Repos/SimpleLogger/SimpleLogger/SimpleLogger.h
    DESTINATION ${EXTERNAL}/headeronly)