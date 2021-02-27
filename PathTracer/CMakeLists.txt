cmake_minimum_required(VERSION 3.14)
project(PathTracer)

set(CMAKE_CXX_STANDARD 14)


include(cmake/lidanBase.cmake)
include(cmake/LidanBuild.cmake)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/common
)

ADD_SUBSRC(commondir  common)

add_executable(PathTracer main.cpp
                          ${commondir}
        ../model/Objmodel.cpp ../model/ObjModel.cpp ../model/ObjModel.h ../model/Sphere.h common/Model.h BasicRayTracing/Scenic.cpp BasicRayTracing/Scenic.h)