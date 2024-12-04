#include "Shape3D.hpp"
#include <GL/gl.h>

void Shape3D::draw() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &verts.front());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, &colors.front());
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, &indices.front());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}
