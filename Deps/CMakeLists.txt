#assimp
set( BUILD_SHARED_LIBS         ON )
set( ASSIMP_BUILD_ZLIB         ON  CACHE BOOL "xxx" FORCE )
set( ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "xxx" FORCE )
set( ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "xxx" FORCE )

add_subdirectory(assimp)

#freetype
add_subdirectory(freetype)

set( BUILD_SHARED_LIBS OFF FORCE)
set( BUILD_SHARED_LIBS OFF CACHE BOOL "xxx" FORCE )

# openal-soft
set( ALSOFT_UTILS          OFF CACHE BOOL "Build utility programs"                     FORCE )
set( ALSOFT_NO_CONFIG_UTIL ON  CACHE BOOL "Disable building the alsoft-config utility" FORCE )

add_subdirectory(openal-soft)

#glad
set( USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "Use MSVC runtime library DLL" FORCE )
set( GLAD_INSTALL                 ON  CACHE BOOL "Generate installation target" FORCE )


add_subdirectory(glad)

#glfw
set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE )
set( GLFW_BUILD_DOCS   OFF CACHE BOOL "GLFW lib only"          FORCE )
set( GLFW_INSTALL      OFF CACHE BOOL "GLFW lib only"          FORCE )

add_subdirectory(glfw)

#shaderc
set( SHADERC_SKIP_TESTS    ON  CACHE BOOL "Skip building tests"    FORCE )
set( SHADERC_SKIP_EXAMPLES ON  CACHE BOOL "Skip building examples" FORCE )

find_package (Python COMPONENTS Interpreter Development)

execute_process(COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/shaderc/utils/git-sync-deps COMMAND_ECHO STDOUT)

add_subdirectory(shaderc)

# SPIRV-Cross
add_subdirectory(SPIRV-Cross)

# metal
add_subdirectory(Metal)