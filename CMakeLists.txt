cmake_minimum_required(VERSION 3.7)
project(LasTest)

find_package(libLAS)
set(CMAKE_CXX_STANDARD 11)

include_directories("/home/tekla/Downloads/opencv/build/include")
FIND_PACKAGE( OpenCV REQUIRED core highgui imgproc)
set(OpenCV_FOUND TRUE)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES LidarClassProcess.cpp PointCloudData.cpp PointCloudData.h LasPoint.cpp LasPoint.h LandCoverParams.cpp LandCoverParams.h ReadWriteData.cpp ReadWriteData.h CalcParams.cpp CalcParams.h ClassMap.cpp ClassMap.h)
add_executable(LasTest ${SOURCE_FILES})
target_link_libraries(LasTest ${libLAS_LIBRARIES} ${OpenCV_LIBS})





