cmake_minimum_required(VERSION 2.8)

project(jsonRPC)

add_executable(JsonRpc main.cpp JsonRpc.cpp JsonRpcClient.cpp)

#set(CMAKE_CXX_FLAGS -g)
set(CMAKE_CXX_FLAGS "-Wdeprecated-declarations -g -std=c++11")

target_link_libraries(JsonRpc json)
target_link_libraries(JsonRpc curl)
