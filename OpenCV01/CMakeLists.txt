# 指定要求的CMake最低版本
cmake_minimum_required(VERSION 3.0)
# 指定项目名称
project(TestIni)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include )
# Find the OpenCV package
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# 添加可执行文件并指定源文件
add_executable(test opencv09.cpp)

# Link your project with OpenCV
target_link_libraries(test PRIVATE ${OpenCV_LIBS} ${CMAKE_SOURCE_DIR}/include/FaceDetection/lib/libfacedetection.so)
