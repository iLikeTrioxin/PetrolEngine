cmake_minimum_required(VERSION 3.5)

project(Engine)

set (CMAKE_CXX_STANDARD 17)

File(GLOB_RECURSE SOURCE_FILES   Engine/Source/*.cpp )
File(GLOB_RECURSE HEADER_FILES   Engine/Source/*.h   )
File(GLOB_RECURSE RESOURCE_FILES Engine/Resources/*.*)

source_group(TREE ${CMAKE_SOURCE_DIR}/Engine FILES ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

add_library                (Engine ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES} )
target_precompile_headers  (Engine PRIVATE "Engine/Source/PCH.h"    )

if(NOT WIN32)
target_link_libraries(Engine PUBLIC pthread dl)
endif()

add_subdirectory(Deps)

FIND_PACKAGE(Vulkan REQUIRED)

target_link_libraries(Engine
    PRIVATE glad
    PRIVATE glfw
    PRIVATE assimp
    PRIVATE freetype
    PRIVATE shaderc
    PRIVATE lua::lib
    PRIVATE ${Vulkan_LIBRARIES}
)

# include only libraries
target_include_directories(Engine
    PUBLIC Deps/glm
    PUBLIC Deps/stb
    PUBLIC Deps/entt/single_include
    PUBLIC Engine/Source
	PUBLIC ${Vulkan_INCLUDE_DIRS}
)
target_compile_options(Engine PUBLIC -Wl,-rpath -Wl,.)

add_executable             (Engine_test        Engine/Source/Main.cpp   )
target_include_directories (Engine_test PUBLIC Engine/Source            )
target_include_directories (Engine_test PUBLIC ${DEPENDENCY_INCLUDE_DIR})
target_link_libraries      (Engine_test Engine                          )


target_include_directories(Engine_test
    PUBLIC Deps/glm
    PUBLIC Deps/stb
    PUBLIC Deps/entt/single_include
)