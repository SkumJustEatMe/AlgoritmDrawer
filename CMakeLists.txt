cmake_minimum_required(VERSION 3.25)
project(MANAlgo)

set(CMAKE_CXX_STANDARD 20)

add_executable(MANAlgo main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(MANAlgo sfml-system sfml-window sfml-graphics sfml-audio)
