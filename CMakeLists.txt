cmake_minimum_required(VERSION 3.20)
project(3DEngineProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE INCLUDE include/*.hpp include/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)

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

target_link_libraries(3DEngine PRIVATE
    OpenGL::GL
    GLEW::glew
    GLUT::GLUT
    glm::glm-header-only
)
