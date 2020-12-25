cmake_minimum_required(VERSION 3.5)

project(Engine)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(Dependencies)

include_directories(${DEPENDENCY_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

File(GLOB SOURCE_FILES
    Engine/Source/*.cpp
)

File(GLOB HEADER_FILES
    Engine/Source/*.h
)

add_library(Engine_lib ${SOURCE_FILES} ${HEADER_FILES})
#add_dependencies(Engine_lib GLFW GLM Glad Assimp Stb EnTT)
target_link_libraries(Engine_lib PUBLIC GLFW_lib Glad_lib Assimp_lib)

Set(OutLib "C:/Users/mpr19/Desktop/Engine/build/Debug/ma.lib")

add_custom_target(combined ALL
    COMMAND ${CMAKE_AR} /out:${OutLib} $<TARGET_FILE:GLFW_lib> $<TARGET_FILE:Glad_lib> $<TARGET_FILE:Assimp_lib> $<TARGET_FILE:Engine_lib>)

add_executable(Engine_test Engine/Source/main.cpp)
#target_link_libraries(Engine_test Engine)

target_compile_options(Engine_test PUBLIC -Wall -g)
