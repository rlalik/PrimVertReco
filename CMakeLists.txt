cmake_minimum_required(VERSION 2.6)
project(primvertreco)

add_executable(primvertreco main.cpp)

install(TARGETS primvertreco RUNTIME DESTINATION bin)
