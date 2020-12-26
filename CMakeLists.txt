cmake_minimum_required(VERSION 3.5)

project(Engine)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(Deps)

include_directories(${DEPENDENCY_INCLUDE_DIR})

File(GLOB SOURCE_FILES
    Engine/Source/*.cpp
)

File(GLOB HEADER_FILES
    Engine/Source/*.h
)

add_library     (Engine ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(Engine GLFW glm Glad Assimp Stb EnTT)

set(OUTPUT_LIB_NAME      "${CMAKE_STATIC_LIBRARY_PREFIX}Engine_and_deps${CMAKE_STATIC_LIBRARY_SUFFIX}")

if(WIN32)
	set(CONNECT_LIBS_COMMAND ${CMAKE_AR} /LIBPATH:${DEPENDENCY_INCLUDE_DIR}/../Lib /OUT:${CMAKE_BINARY_DIR}/Lib/${OUTPUT_LIB_NAME} $<TARGET_FILE:GLFW_lib> $<TARGET_FILE:Glad_lib> $<TARGET_FILE:Assimp_lib> $<TARGET_FILE:Engine> )
else()
	set(CONNECT_LIBS_COMMAND ${CMAKE_AR} ${CMAKE_BINARY_DIR}/Lib/${OUTPUT_LIB_NAME} $<TARGET_FILE:GLFW_lib> $<TARGET_FILE:Glad_lib> $<TARGET_FILE:Assimp_lib> $<TARGET_FILE:Engine> )
endif()

add_definitions("-Wall -g")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
add_custom_target(combined ALL COMMAND ${CONNECT_LIBS_COMMAND})

add_library(Engine_and_deps STATIC IMPORTED GLOBAL)

set_target_properties(Engine_and_deps PROPERTIES IMPORTED_LOCATION
  "${CMAKE_BINARY_DIR}/Lib/${OUTPUT_LIB_NAME}"
)

add_executable(Engine_test Engine/Source/main.cpp)
target_link_libraries(Engine_test Engine_and_deps)
