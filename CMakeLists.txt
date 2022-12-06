cmake_minimum_required(VERSION 3.5)

project(Engine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES   Engine/Source/*.cpp )
file(GLOB_RECURSE HEADER_FILES   Engine/Source/*.h   )
file(GLOB_RECURSE RESOURCE_FILES Engine/Resources/*.*)

add_library(Engine STATIC ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES} Engine/Source/Renderer/Metal/Metal.h Engine/Source/Renderer/Metal/Metal.cpp Engine/Source/Renderer/Metal/MetalRenderer.cpp Engine/Source/Renderer/Metal/MetalRenderer.h)

find_library(APPLE_FWK_METAL Metal)

find_package(Vulkan)

#if(${VULKAN_FOUND})
#    ADD_DEFINITIONS(-DVULKAN)
#	# if it was found add libraries to link to and headers
#    target_link_libraries     (Engine PRIVATE ${Vulkan_LIBRARIES}   )
#    target_include_directories(Engine PUBLIC  ${Vulkan_INCLUDE_DIRS})
#else()
#    # If vulkan was not found exclude source code for vulkan
#    message(WARNING "Vulkan SDK not found. Building without vulkan.")
#    list(FILTER SOURCE_FILES EXCLUDE REGEX "Vulkan")
#    list(FILTER HEADER_FILES EXCLUDE REGEX "Vulkan")
#endif()

message(WARNING "Vulkan SDK not found. Building without vulkan.")
list(FILTER SOURCE_FILES EXCLUDE REGEX "Vulkan")
list(FILTER HEADER_FILES EXCLUDE REGEX "Vulkan")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine FILES ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

if(UNIX)
    target_link_libraries (Engine PUBLIC pthread dl)
    target_compile_options(Engine PUBLIC -Wl,-rpath -Wl,.)
endif()

add_subdirectory(Deps)

target_link_libraries(Engine
    PRIVATE glad
    PRIVATE OpenAL
    PRIVATE common
    PRIVATE glfw
    PRIVATE shaderc
    PRIVATE assimp
    PRIVATE freetype
    PRIVATE spirv-cross-cpp

)

target_include_directories(Engine
        PUBLIC Deps/metal-cpp/SingleHeader
    PUBLIC Deps/glm
    PUBLIC Deps/openal-soft/include
    PUBLIC Deps/glfw/include
    PUBLIC Deps/assimp/include
    PUBLIC Deps/stb
    PUBLIC Deps/entt/single_include
    PUBLIC Deps/SPIRV-Cross
    PUBLIC Engine/Source
    PUBLIC Deps/shaderc/libshaderc/include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Deps/glad/include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Deps/assimp/include
)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.16")
    target_precompile_headers(Engine PRIVATE $<INSTALL_INTERFACE:Engine/Source/PCH.h>)
endif()