cmake_minimum_required(VERSION 3.5)

project(Engine)

set(CMAKE_CXX_STANDARD 17)

File(GLOB_RECURSE SOURCE_FILES   Engine/Source/*.cpp )
File(GLOB_RECURSE HEADER_FILES   Engine/Source/*.h   )
File(GLOB_RECURSE RESOURCE_FILES Engine/Resources/*.*)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine FILES ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

add_library(Engine ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES} )

if(UNIX)

target_link_libraries (Engine PUBLIC pthread dl)
target_compile_options(Engine PUBLIC -Wl,-rpath -Wl,.)

endif()

add_subdirectory(Deps)

FIND_PACKAGE(Vulkan REQUIRED)

target_link_libraries(Engine
    PRIVATE glad
    PRIVATE glfw
    PRIVATE assimp
    PRIVATE shaderc
    PRIVATE freetype
    PRIVATE lua::lib
    PRIVATE ${Vulkan_LIBRARIES}
)

target_include_directories(Engine
    PUBLIC Deps/glm
    PUBLIC Deps/glfw/include
    PUBLIC Deps/assimp/include
    PUBLIC Deps/stb
    PUBLIC Deps/entt/single_include
    PUBLIC Engine/Source
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Deps/assimp/include
	PUBLIC ${Vulkan_INCLUDE_DIRS}
)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.16")

target_precompile_headers  ( Engine PRIVATE $<INSTALL_INTERFACE:Engine/Source/PCH.h> )

endif()

add_executable             (Engine_test        Engine/Source/Main.cpp   )
target_include_directories (Engine_test PUBLIC Engine/Source            )
target_include_directories (Engine_test PUBLIC ${DEPENDENCY_INCLUDE_DIR})
target_link_libraries      (Engine_test Engine                          )


target_include_directories(Engine_test
    PUBLIC Deps/glm
    PUBLIC Deps/stb
    PUBLIC Deps/entt/single_include
)
