include(ExternalProject)

set(DEPENDENCY_DIR ${CMAKE_BINARY_DIR}/Deps)
set(DEPENDENCY_INSTALL_DIR ${DEPENDENCY_DIR}/Installed)
set(DEPENDENCY_INSTALL_LIB_DIR ${DEPENDENCY_INSTALL_DIR}/lib)
set(DEPENDENCY_INSTALL_INCLUDE_DIR ${DEPENDENCY_INSTALL_DIR}/include)

if(WIN32)
    FILE(GLOB LIBRARIES ${DEPENDENCY_INSTALL_LIB_DIR}/*.lib)
else()
    FILE(GLOB LIBRARIES ${DEPENDENCY_INSTALL_LIB_DIR}/*.a ${DEPENDENCY_INSTALL_LIB_DIR}/*.so)
endif()
set(DEPENDENCY_INCLUDE_DIR ${CMAKE_BINARY_DIR}/Deps/Installed/include PARENT_SCOPE)

#
# Header only projects
#
ExternalProject_Add(glm
    GIT_REPOSITORY         "https://github.com/g-truc/glm"
	PREFIX                 ${DEPENDENCY_DIR}/glm
    CONFIGURE_COMMAND      ""
      INSTALL_COMMAND      ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/glm ${DEPENDENCY_INSTALL_INCLUDE_DIR}/glm
        BUILD_COMMAND      ""
       UPDATE_COMMAND      ""
       UPDATE_DISCONNECTED 1
)

ExternalProject_Add(EnTT
    GIT_REPOSITORY         "https://github.com/skypjack/entt"
    PREFIX                 ${DEPENDENCY_DIR}/EnTT
    CONFIGURE_COMMAND      ""
      INSTALL_COMMAND      ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR> ${DEPENDENCY_INSTALL_INCLUDE_DIR}/EnTT
        BUILD_COMMAND      ""
       UPDATE_COMMAND      ""
       UPDATE_DISCONNECTED 1
)

ExternalProject_Add(Stb
    GIT_REPOSITORY         "https://github.com/nothings/stb"
    PREFIX                 ${DEPENDENCY_DIR}/Stb
    CONFIGURE_COMMAND      ""
      INSTALL_COMMAND      ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR> ${DEPENDENCY_INSTALL_INCLUDE_DIR}/Stb
        BUILD_COMMAND      ""
       UPDATE_COMMAND      ""
       UPDATE_DISCONNECTED 1
)

#
# Accualy compile-required projects
#
ExternalProject_Add(lua
   URL                  "https://www.lua.org/ftp/lua-5.3.5.tar.gz"
   PREFIX               ${DEPENDENCY_DIR}/Lua
    UPDATE_COMMAND      ""
    UPDATE_DISCONNECTED 1
    PATCH_COMMAND       ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Deps/LuaCMakeLists.txt ${DEPENDENCY_DIR}/lua/src/lua/CMakeLists.txt
     CMAKE_ARGS         -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
)

ExternalProject_Add(GLFW
    GIT_REPOSITORY      "https://github.com/glfw/glfw"
    PREFIX              ${DEPENDENCY_DIR}/GLFW
    UPDATE_COMMAND      ""
    UPDATE_DISCONNECTED 1
    CMAKE_ARGS         -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
                        -DGLFW_BUILD_EXAMPLES=OFF
                        -DGLFW_BUILD_TESTS=OFF
)

ExternalProject_Add(Glad
    GIT_REPOSITORY      "https://github.com/Dav1dde/glad"
    PREFIX              ${DEPENDENCY_DIR}/Glad
    UPDATE_COMMAND      ""
    UPDATE_DISCONNECTED 1
    CMAKE_ARGS         -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
                        -DGLAD_INSTALL=ON
)

ExternalProject_Add(Assimp
    GIT_REPOSITORY       "https://github.com/assimp/assimp"
    GIT_TAG              "v5.0.1"
    PREFIX               ${DEPENDENCY_DIR}/Assimp
     UPDATE_COMMAND      ""
     UPDATE_DISCONNECTED 1
      CMAKE_ARGS         -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
                         -DLIBRARY_SUFFIX=
                         -DASSIMP_BUILD_TESTS=OFF
                         -DINJECT_DEBUG_POSTFIX=OFF
)

#
# Create libraries and assign files to them
#
add_library(   lua_lib STATIC IMPORTED GLOBAL)
add_library(  GLFW_lib STATIC IMPORTED GLOBAL)
add_library(  Glad_lib STATIC IMPORTED GLOBAL)
add_library(Assimp_lib STATIC IMPORTED GLOBAL)

add_dependencies(   lua_lib lua   )
add_dependencies(  GLFW_lib GLFW  )
add_dependencies(  Glad_lib Glad  )
add_dependencies(Assimp_lib Assimp)

set_target_properties(lua_lib PROPERTIES
    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}lua${CMAKE_STATIC_LIBRARY_SUFFIX}"
)

set_target_properties(GLFW_lib PROPERTIES
    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}"
)

set_target_properties(Glad_lib PROPERTIES
    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glad${CMAKE_STATIC_LIBRARY_SUFFIX}"
)

set_target_properties(Assimp_lib PROPERTIES
    IMPORTED_LOCATION "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}assimp${CMAKE_STATIC_LIBRARY_SUFFIX}"
)