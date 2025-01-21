#include "Shape3D.hpp"

#include <GL/gl.h>

Shape3D::Shape3D(
  const std::vector<float> &verts,
  const std::vector<float> &colors,
  const std::vector<float> &normals,
  const std::vector<unsigned int> &indices,
  const std::vector<float> &texCoord
) : verts(verts), colors(colors), indices(indices), normals(normals), texCoords(texCoord) {}

void Shape3D::draw() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &verts.front());

  if(!colors.empty()) {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, &colors.front());
  }

  if(!normals.empty()) {
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &normals.front());
  }

  if(!texCoords.empty()) {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, &texCoords.front());
  }

  glDrawElements(
    GL_TRIANGLES,
    indices.size(),
    GL_UNSIGNED_INT,
    &indices.front());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}
