cmake_minimum_required(VERSION 3.22)
project(test)

set(CMAKE_CXX_STANDARD 17)
#aux_source_directory(. DIR_SRCS)

#message("${DIR_SRCS} ---------")
#add_executable(hello-server ${DIR_SRCS})
add_executable(hello-server hello-server.cpp)
add_executable(hello-client hello-client.cpp)
add_executable(low-open low-open.cpp)
add_executable(endian-conv endian-conv.cpp)
add_executable(ip-to-addr ip-to-addr.cpp)