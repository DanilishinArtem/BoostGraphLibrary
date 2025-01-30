cmake_minimum_required(VERSION 3.22)
project(MyGraphProject)

find_package(Boost REQUIRED COMPONENTS graph)
message(STATUS "Boost library found: ${Boost_FOUND}")
message(STATUS "Boost Include Dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")
message(STATUS "Boost Version: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})
add_executable(boostProject main.cpp)
target_link_libraries(boostProject PRIVATE Boost::graph)



# Boost_FOUND	TRUE, если Boost найден
# Boost_INCLUDE_DIRS	Путь к заголовочным файлам (boost/)
# Boost_LIBRARIES	Полный путь к библиотекам (libboost_graph.so)
# Boost_VERSION	Версия Boost (например, 1.82.0)
# conda install conda-forge::boost
# conda install graphviz