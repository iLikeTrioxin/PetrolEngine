include(ExternalProject)

set(DEPENDENCY_DIR ${CMAKE_BINARY_DIR}/Dependencies)
set(DEPENDENCY_INSTALL_DIR ${DEPENDENCY_DIR}/installed)
set(DEPENDENCY_INSTALL_LIB_DIR ${DEPENDENCY_INSTALL_DIR}/lib)
set(DEPENDENCY_INSTALL_INCLUDE_DIR ${DEPENDENCY_INSTALL_DIR}/include)

set(DEPENDENCY_INCLUDE_DIR ${CMAKE_BINARY_DIR}/Dependencies/installed/include PARENT_SCOPE)

externalproject_add(Stb
    PREFIX ${DEPENDENCY_DIR}/Stb
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
                    <SOURCE_DIR> ${DEPENDENCY_INSTALL_INCLUDE_DIR}/Stb
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    UPDATE_DISCONNECTED 1
    URL https://github.com/nothings/stb/archive/master.zip
)

externalproject_add(EnTT
    PREFIX ${DEPENDENCY_DIR}/EnTT
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
                    <SOURCE_DIR> ${DEPENDENCY_INSTALL_INCLUDE_DIR}/EnTT
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    UPDATE_DISCONNECTED 1
    URL https://github.com/skypjack/entt/archive/v3.5.2.zip
)

externalproject_add(GLM
    PREFIX ${DEPENDENCY_DIR}/GLM
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
                    <SOURCE_DIR>/GLM ${DEPENDENCY_INSTALL_INCLUDE_DIR}/GLM
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    UPDATE_DISCONNECTED 1
    URL https://github.com/g-truc/glm/archive/0.9.9-a2.zip
)

externalproject_add(GLFW
    PREFIX ${DEPENDENCY_DIR}/GLFW
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
	           -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
    UPDATE_COMMAND ""
    UPDATE_DISCONNECTED 1
    URL https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
)

externalproject_add(Glad
    PREFIX ${DEPENDENCY_DIR}/Glad
    CMAKE_ARGS -DGLAD_INSTALL=ON
               -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
    UPDATE_COMMAND ""
    UPDATE_DISCONNECTED 1
    URL https://github.com/Dav1dde/glad/archive/v0.1.34.zip
)
externalproject_add(Assimp
    PREFIX ${DEPENDENCY_DIR}/Assimp
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_INSTALL_DIR}
    UPDATE_COMMAND ""
    UPDATE_DISCONNECTED 1
    URL https://github.com/assimp/assimp/archive/v5.0.1.zip
)

add_library(GLFW_lib STATIC IMPORTED GLOBAL)
add_library(Glad_lib STATIC IMPORTED GLOBAL)
add_library(Assimp_lib STATIC IMPORTED GLOBAL)

set_target_properties(GLFW_lib PROPERTIES IMPORTED_LOCATION
  "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}"
)
set_target_properties(Glad_lib PROPERTIES IMPORTED_LOCATION
  "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}glad${CMAKE_STATIC_LIBRARY_SUFFIX}"
)
set_target_properties(Assimp_lib PROPERTIES IMPORTED_LOCATION
  "${DEPENDENCY_INSTALL_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}assimp-vc142-mtd${CMAKE_STATIC_LIBRARY_SUFFIX}"
)