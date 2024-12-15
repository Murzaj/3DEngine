#include "CubeLightVerts.hpp"
#include <GL/gl.h>

// TODO
CubeLightVerts::CubeLightVerts() :
  Shape3D(
    {
      // FACE DOWN
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,
      // FACE UP
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      // FACE FRONT
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,
      // FACE BACK
      -1.0f, 1.0f, -1.0f,
      1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      // FACE LEFT
      -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      // FACE RIGHT
      1.0f, -1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
    }, {
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
    },
    {
      // FACE DOWN
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      // FACE UP
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      // FACE FRONT
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      // FACE BACK
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      // FACE LEFT
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      // FACE RIGHT
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      },{
      
    }
    ) {}


void CubeLightVerts::draw() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &verts.front());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, &colors.front());
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(3, GL_FLOAT, &normals.front());
  glDrawElements(
    GL_TRIANGLES,
    indices.size(),
    GL_UNSIGNED_INT,
    &indices.front());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}
