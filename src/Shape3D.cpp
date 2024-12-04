#include "Shape3D.hpp"
#include <GL/gl.h>

Shape3D::Shape3D(
  const std::vector<float> &verts,
  const std::vector<float> &colors,
  const std::vector<unsigned int> &indices
) : verts(verts), colors(colors), indices(indices) {}

void Shape3D::draw() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &verts.front());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, &colors.front());
  glDrawElements(
    GL_TRIANGLES,
    indices.size(),
    GL_UNSIGNED_INT,
    &indices.front());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}
