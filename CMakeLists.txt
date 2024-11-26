cmake_minimum_required(VERSION 3.20)
project(3DEngineProject)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)


add_executable(3DEngine 
  src/main.cpp
)

include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(3DEngine PRIVATE
    OpenGL::GL
    GLUT::GLUT
    glm::glm-header-only
)
