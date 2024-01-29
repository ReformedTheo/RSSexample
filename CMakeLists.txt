cmake_minimum_required(VERSION 3.5)
project(RssExample)

set(OpenCV_DIR "C:/opencv/build")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(RssExample main.cpp)
target_link_libraries(RssExample ${OpenCV_LIBS})
