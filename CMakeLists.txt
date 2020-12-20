cmake_minimum_required(VERSION 3.5)

project(Engine)

add_subdirectory(Dependencies)

include_directories(${DEPENDENCY_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

File(GLOB SOURCE_FILES
    Engine/Source/*.cpp
)

File(GLOB HEADER_FILES
    Engine/Source/*.h
)

#set(SHADER_FILES
#    shader/cs.glsl
#)
#
#set(EXAMPLE_FILES
#    scenes/CubeScene.mtl
#    scenes/CubeScene.obj
#    scenes/MirrorRoom.mtl
#    scenes/MirrorRoom.obj
#)
#
#foreach(SHADER ${SHADER_FILES})
#configure_file(${SHADER} ${SHADER} COPYONLY)
#endforeach()
#
#foreach(EXAMPLE ${EXAMPLE_FILES})
#configure_file(${EXAMPLE} ${EXAMPLE} COPYONLY)
#endforeach()
#
#configure_file(settings.txt settings.txt COPYONLY)

add_executable(Engine ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(Engine GLFW GLM Glad Assimp)
target_link_libraries(Engine PUBLIC GLFW_lib Glad_lib Assimp_lib dl)
target_compile_options(Engine PUBLIC -Wall -g)
