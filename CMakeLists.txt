cmake_minimum_required(VERSION 3.20)
project(3DEngineProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE INCLUDE include/*.hpp include/*.h include/ext/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)

set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_BINARY_DIR}")

# Replace backslashes with forward slashes in PATH
if(DEFINED ENV{PATH})
    string(REPLACE "\\" "/" CLEANED_PATH $ENV{PATH})
    set(ENV{PATH} "${CLEANED_PATH}")
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# file(COPY src/shader DESTINATION ${CMAKE_BINARY_DIR}/Debug)

add_executable(3DEngine 
  ${SOURCES}
  ${INCLUDE}
)

target_include_directories(3DEngine PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(3DEngine PRIVATE include/)

# Add a custom target to copy assets
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SOURCE_DIR} ${ASSETS_OUTPUT_DIR}
    COMMENT "Copying assets to the build directory"
)
# Ensure the copy happens before the main build
add_dependencies(3DEngine copy_assets)

target_link_libraries(3DEngine PRIVATE
    OpenGL::GL
    GLEW::glew
    GLUT::GLUT
    glm::glm-header-only
)
