/*
 * // Cube vertices (8 vertices)
GLfloat vertices[] = {
    -1.0, -1.0, -1.0,     // 0
     1.0, -1.0, -1.0,     // 1
     1.0,  1.0, -1.0,     // 2
    -1.0,  1.0, -1.0,     // 3
    -1.0, -1.0,  1.0,     // 4
     1.0, -1.0,  1.0,     // 5
     1.0,  1.0,  1.0,     // 6
    -1.0,  1.0,  1.0      // 7
};

// Cube indices (6 faces, 2 triangles per face, 3 vertices per triangle)
GLuint indices[] = {
    0, 1, 2,  2, 3, 0,   // Back face
    4, 5, 6,  6, 7, 4,   // Front face
    0, 4, 7,  7, 3, 0,   // Left face
    1, 5, 6,  6, 2, 1,   // Right face
    0, 1, 5,  5, 4, 0,   // Bottom face
    3, 7, 6,  6, 2, 3    // Top face
};

// Smooth normals that point diagonally outward from the center
GLfloat normals[] = {
    -1.0f, -1.0f, -1.0f,  // Vertex 0
     1.0f, -1.0f, -1.0f,  // Vertex 1
     1.0f,  1.0f, -1.0f,  // Vertex 2
    -1.0f,  1.0f, -1.0f,  // Vertex 3
    -1.0f, -1.0f,  1.0f,  // Vertex 4
     1.0f, -1.0f,  1.0f,  // Vertex 5
     1.0f,  1.0f,  1.0f,  // Vertex 6
    -1.0f,  1.0f,  1.0f   // Vertex 7
};

*/

#pragma once
#include "Shape3D.hpp"

class CubeSmooth3D : public Shape3D {
public:
  CubeSmooth3D()
    : Shape3D(
    {
      // Positions
      -1.0, -1.0, -1.0, // 0
      1.0,  -1.0, -1.0, // 1
      1.0,  1.0,  -1.0, // 2
      -1.0, 1.0,  -1.0, // 3
      -1.0, -1.0, 1.0,  // 4
      1.0,  -1.0, 1.0,  // 5
      1.0,  1.0,  1.0,  // 6
      -1.0, 1.0,  1.0   // 7
    },
    {
      // colors
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
      1.0, 1.0, 1.0,
    },
    {
      // normals
      -1.0f, -1.0f, -1.0f, // Vertex 0
      1.0f,  -1.0f, -1.0f, // Vertex 1
      1.0f,  1.0f,  -1.0f, // Vertex 2
      -1.0f, 1.0f,  -1.0f, // Vertex 3
      -1.0f, -1.0f, 1.0f,  // Vertex 4
      1.0f,  -1.0f, 1.0f,  // Vertex 5
      1.0f,  1.0f,  1.0f,  // Vertex 6
      -1.0f, 1.0f,  1.0f   // Vertex 7
    },
    {
      // indices
      0, 1, 2, 2, 3, 0, // Back face
      4, 5, 6, 6, 7, 4, // Front face
      0, 4, 7, 7, 3, 0, // Left face
      1, 5, 6, 6, 2, 1, // Right face
      0, 1, 5, 5, 4, 0, // Bottom face
      3, 7, 6, 6, 2, 3  // Top face
    },
    {}) {}
};
