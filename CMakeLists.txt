cmake_minimum_required(VERSION 3.23)
project(EEgames)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/")
add_executable(EEgames app.cpp graph.cpp io.cpp node.cpp)
