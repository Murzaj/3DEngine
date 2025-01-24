#include "PrimitiveShape3D.hpp"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>


void PrimitiveShape3D::draw(const glm::mat4 &view) {
  glm::mat4 mvp = view * getTransform();
  glLoadMatrixf(glm::value_ptr(mvp));
  glColor3f(color.r, color.g, color.b);
  primitiveDrawingFunc();
  glColor3f(1.0, 1.0, 1.0);
}
