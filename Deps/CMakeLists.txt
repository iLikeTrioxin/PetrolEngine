#assimp
add_subdirectory(assimp)

#freetype
add_subdirectory(freetype)

#glad
set( USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "Use MSVC runtime library DLL" FORCE )
set( GLAD_INSTALL                 ON  CACHE BOOL "Generate installation target" FORCE )


add_subdirectory(glad)

#lua
add_subdirectory(lua-cmake)

#glfw
set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE )
set( GLFW_BUILD_DOCS   OFF CACHE BOOL "GLFW lib only"          FORCE )
set( GLFW_INSTALL      OFF CACHE BOOL "GLFW lib only"          FORCE )

add_subdirectory(glfw)

#shaderc
set( SHADERC_SKIP_TESTS    ON  CACHE BOOL "Skip building tests"    FORCE )
set( SHADERC_SKIP_EXAMPLES ON  CACHE BOOL "Skip building examples" FORCE )

find_package (Python COMPONENTS Interpreter Development)

execute_process(COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Deps/shaderc/utils/git-sync-deps COMMAND_ECHO STDOUT)

add_subdirectory(shaderc)

