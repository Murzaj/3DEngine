#pragma once

#include "TexturedModelShape3D.hpp"

#include <GL/gl.h>
#include <glm/glm.hpp>

class TexturedPlane3D : public TexturedModelShape3D {
public:
  TexturedPlane3D(glm::vec3 modulateColor, GLuint textureId) :
  TexturedModelShape3D(
    {
      -1.0f, 0.0f, -1.0f,
      1.0f, 0.0f, -1.0f,
      1.0f, 0.0f, 1.0f,
      -1.0f, 0.0f, 1.0f,
    },
    {},
    modulateColor,
    {
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
    },
    {
        0, 1, 2,
        0, 2, 3
    },
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    },
    textureId) 
  {}
};
