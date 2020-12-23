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

function(combine_archives output_archive list_of_input_archives)
    set(mri_file ${TEMP_DIR}/${output_archive}.mri)
    set(FULL_OUTPUT_PATH ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib${output_archive}.a)
    file(WRITE ${mri_file} "create ${FULL_OUTPUT_PATH}\n")
    FOREACH(in_archive ${list_of_input_archives})
        file(APPEND ${mri_file} "addlib ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib${in_archive}.a\n")
    ENDFOREACH()
    file(APPEND ${mri_file} "save\n")
    file(APPEND ${mri_file} "end\n")

    set(output_archive_dummy_file ${TEMP_DIR}/${output_archive}.dummy.cpp)
    add_custom_command(OUTPUT ${output_archive_dummy_file}
                       COMMAND touch ${output_archive_dummy_file}
                       DEPENDS ${list_of_input_archives})

    add_library(${output_archive} STATIC ${output_archive_dummy_file})
    add_custom_command(TARGET ${output_archive}
                       POST_BUILD
                       COMMAND ar -M < ${mri_file})
endfunction(combine_archives)

add_library(Engine_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

combine_archives(Engine Engine_lib GLFW_lib Glad_lib Assimp_lib)

add_dependencies     (Engine GLFW GLM Glad Assimp Stb EnTT)
target_link_libraries(Engine PUBLIC GLFW_lib Glad_lib Assimp_lib )

target_compile_options(Engine PUBLIC -Wall -g)
