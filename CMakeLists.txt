cmake_minimum_required(VERSION 3.5)
project(RssExample)

# Set the directory where OpenCV is installed
set(OpenCV_DIR "C:/opencv/build")
find_package(OpenCV REQUIRED)

# Include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Create the executable from the main.cpp file
add_executable(RssExample main.cpp)

# Link OpenCV libraries
target_link_libraries(RssExample ${OpenCV_LIBS})
