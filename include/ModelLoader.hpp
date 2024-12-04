#pragma once

#include "Shape3D.hpp"
#include <string>
#include <vector>

namespace modelloader {
  Shape3D *shapeFromOBJ(const std::string &filename);
}
