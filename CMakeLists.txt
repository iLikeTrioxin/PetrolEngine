cmake_minimum_required(VERSION 3.5)

project(Engine)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(Deps)

File(GLOB SOURCE_FILES
    Engine/Source/*.cpp
)

File(GLOB HEADER_FILES
    Engine/Source/*.h
)

add_library                (Engine ${SOURCE_FILES} ${HEADER_FILES}  )
target_include_directories (Engine PUBLIC ${DEPENDENCY_INCLUDE_DIR} )
target_link_libraries      (Engine PUBLIC pthread dl                )
add_dependencies           (Engine glm GLFW Glad Assimp Stb EnTT    )

set(OUTPUT_LIB_NAME "${CMAKE_STATIC_LIBRARY_PREFIX}Engine_and_deps${CMAKE_STATIC_LIBRARY_SUFFIX}")

if(WIN32)
	set(CONNECT_LIBS_COMMAND ${CMAKE_AR} /LIBPATH:${DEPENDENCY_INCLUDE_DIR}/../Lib /OUT:${CMAKE_BINARY_DIR}/Lib/${OUTPUT_LIB_NAME} $<TARGET_FILE:GLFW_lib> $<TARGET_FILE:Glad_lib> $<TARGET_FILE:Assimp_lib> $<TARGET_FILE:Engine> )
else()
	set(CONNECT_LIBS_COMMAND ${CMAKE_AR} ${CMAKE_BINARY_DIR}/Lib/${OUTPUT_LIB_NAME} $<TARGET_FILE:GLFW_lib> $<TARGET_FILE:Glad_lib> $<TARGET_FILE:Assimp_lib> $<TARGET_FILE:Engine> )
endif()

add_definitions("-Wall -g")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

add_custom_target(combined DEPENDS Engine ALL COMMAND ${CONNECT_LIBS_COMMAND})

add_library(Engine_and_deps STATIC IMPORTED GLOBAL)

set_target_properties(Engine_and_deps PROPERTIES IMPORTED_LOCATION
  "${CMAKE_BINARY_DIR}/Lib/${OUTPUT_LIB_NAME}"
)

add_executable             (Engine_test        Engine/Source/Main.cpp    )
target_include_directories (Engine_test PUBLIC Engine/Source             )
target_include_directories (Engine_test PUBLIC ${DEPENDENCY_INCLUDE_DIR} )
add_dependencies           (Engine_test Engine                           )
add_dependencies           (Engine_test Engine_and_deps                  )
target_link_libraries      (Engine_test Engine_and_deps                  )
