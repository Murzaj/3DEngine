#include "Cube.hpp"
#include <random>

float randFloat() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  return dist(rng);
}

Cube::Cube() : Shape3D(
  {
    -1.0f, -1.0f, +1.0f,
    -1.0f, -1.0f, -1.0f,
    +1.0f, -1.0f, -1.0f,
    +1.0f, -1.0f, +1.0f,
    -1.0f, +1.0f, +1.0f, 
    -1.0f, +1.0f, -1.0f, 
    +1.0f, +1.0f, -1.0f,  
    +1.0f, +1.0f, +1.0f, 
  },
  {
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
    randFloat(), randFloat(), randFloat(),
  }, 
  {
  },
  {
    0,1,2,
    0,2,3,
    4,5,6,
    6,7,4,
    0,1,5,
    4,5,0,
    1,2,5,
    5,6,2,
    2,3,7,
    7,6,2,
    0,3,7,
    7,4,0
  }
) {}
