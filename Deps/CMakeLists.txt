#assimp
add_subdirectory(assimp)

#freetype
add_subdirectory(freetype)

#glad
set(
    USE_MSVC_RUNTIME_LIBRARY_DLL
	OFF CACHE BOOL
	"Use MSVC runtime library DLL"
	FORCE
)
add_subdirectory(glad)

#glfw
set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE )
set( GLFW_BUILD_DOCS   OFF CACHE BOOL "GLFW lib only"          FORCE )
set( GLFW_INSTALL      OFF CACHE BOOL "GLFW lib only"          FORCE )

add_subdirectory(glfw)

#
# Create libraries and assign files to them
#
#add_library(   lua_lib STATIC IMPORTED GLOBAL)
#add_library(  GLFW_lib STATIC IMPORTED GLOBAL)
#add_library(  Glad_lib STATIC IMPORTED GLOBAL)
#add_library(Assimp_lib STATIC IMPORTED GLOBAL)
#
#add_dependencies(   lua_lib lua   )
#add_dependencies(  GLFW_lib GLFW  )
#add_dependencies(  Glad_lib Glad  )
#add_dependencies(Assimp_lib Assimp)
#
#set_target_properties(lua_lib PROPERTIES
#    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}lua${CMAKE_STATIC_LIBRARY_SUFFIX}"
#)
#
#set_target_properties(GLFW_lib PROPERTIES
#    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}"
#)
#
#set_target_properties(Glad_lib PROPERTIES
#    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glad${CMAKE_STATIC_LIBRARY_SUFFIX}"
#)
#
#set_target_properties(Assimp_lib PROPERTIES
#    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}assimp${CMAKE_STATIC_LIBRARY_SUFFIX}"
#)