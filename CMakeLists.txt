cmake_minimum_required(VERSION 3.20)
project(3DEngineProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FILE(GLOB_RECURSE INCLUDE include/*.hpp include/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)

# Replace backslashes with forward slashes in PATH
if(DEFINED ENV{PATH})
    string(REPLACE "\\" "/" CLEANED_PATH $ENV{PATH})
    set(ENV{PATH} "${CLEANED_PATH}")
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)


add_executable(3DEngine 
  ${SOURCES}
)

target_include_directories(3DEngine PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(3DEngine PRIVATE include/)

target_link_libraries(3DEngine PRIVATE
    OpenGL::GL
    GLUT::GLUT
    glm::glm-header-only
)
