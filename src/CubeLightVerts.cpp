#include "CubeLightVerts.hpp"
#include <GL/gl.h>
#include <limits>
#include <cstdlib>

float randFloatTemp() {
  return std::rand() / (float)std::numeric_limits<int>::max();
}

// TODO
CubeLightVerts::CubeLightVerts() :
  Shape3D(
    {
      // FACE DOWN
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f, 
      1.0f, -1.0f, 1.0f, 
      // FACE UP
      1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, 1.0f, 
      1.0f, 1.0f, 1.0f, 
      // FACE FRONT
      1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f,  1.0f,
      1.0f, 1.0f, 1.0f,
      // FACE BACK
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f, 1.0f,  -1.0f,
      1.0f, 1.0f, -1.0f,
      // FACE LEFT
      -1.0f, -1.0f, 1.0f, 
      -1.0f, -1.0f, -1.0f,
      -1.0f,1.0f, -1.0f,
      -1.0f,1.0f, 1.0f, 
      // FACE RIGHT
      1.0f, -1.0f, 1.0f, 
      1.0f, -1.0f, -1.0f,
      1.0f,1.0f, -1.0f,
      1.0f,1.0f, 1.0f, 
    }, {
      // COLORS
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
      randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(), randFloatTemp(),
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
      //UP
      0,1,2,
      0,2,3,

      //DOWN
      4,5,6,
      4,6,7,
      //FRONT
      8,9,10,
      8,10,11,
      //BACK
      12,13,14,
      12,14,15,
      //LEFT
      16,17,18,
      16,18,19,
      //RIGHT
      20,21,22,
      20,22,23,
      }
    ) {}


void CubeLightVerts::draw() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &verts.front());
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(3, GL_FLOAT, &normals.front());
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, &colors.front());
  glDrawElements(
    GL_TRIANGLES,
    indices.size(),
    GL_UNSIGNED_INT,
    &indices.front());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}
