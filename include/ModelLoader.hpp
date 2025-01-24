#pragma once

#include "TexturedModelShape3D.hpp"
#include <GL/gl.h>
#include <string>

namespace modelloader {
  ModelShape3D *shapeFromOBJ(const std::string &filename);
  TexturedModelShape3D *texturedShapeFromOBJ(const std::string &filename, GLuint textureId);
}
