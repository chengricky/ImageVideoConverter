cmake_minimum_required(VERSION 3.0.0)

project(ImgVideo VERSION 1.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_BUILD_TYPE "Release")

# set the directory of executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ImgVideo_SOURCE_DIR}/bin)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ImgVideo Source.cpp)

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})

# opencv libraries
target_link_libraries(ImgVideo ${OpenCV_LIBS})
