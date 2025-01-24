#include "ModelShape3D.hpp"

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

ModelShape3D::ModelShape3D( const std::vector<float> &verts, const std::vector<float> &colors, glm::vec3 modulateColor, const std::vector<float> &normals, const std::vector<unsigned int> &indices,
  const std::vector<float> &texCoord
) : verts(verts), colors(colors), modulateColor(modulateColor), indices(indices), normals(normals), texCoords(texCoord) {}

void ModelShape3D::draw(const glm::mat4 &view) {
  glm::mat4 mvp = view * getTransform();
  glLoadMatrixf(glm::value_ptr(mvp));
  glColor3f(modulateColor.r, modulateColor.g, modulateColor.b);
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
  glColor3f(1.0, 1.0, 1.0);
}
