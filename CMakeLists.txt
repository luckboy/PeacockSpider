cmake_minimum_required(VERSION 2.6)
project(peacockspider)

add_executable(peacockspider main.cpp)

install(TARGETS peacockspider RUNTIME DESTINATION bin)
