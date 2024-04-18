cmake_minimum_required(VERSION 3.27.4)

project(SyncPrimitives)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SyncPrimitives main.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(SyncPrimitives PUBLIC OpenMP::OpenMP_CXX)
endif()

