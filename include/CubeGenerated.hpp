#include "Shape3D.hpp"
#include <vector>

class Cube3D : public Shape3D {
public:
    Cube3D()
        : Shape3D(
              // Vertices of a cube (8 corners of a unit cube)
              {
                  -0.5f, -0.5f, -0.5f // 0: Bottom-left-back
                  0.5f, -0.5f, -0.5f  // 1: Bottom-right-back
                  0.5f, 0.5f, -0.5f   // 2: Top-right-back
                  -0.5f, 0.5f, -0.5f  // 3: Top-left-back
                  -0.5f, -0.5f, 0.5f  // 4: Bottom-left-front
                  0.5f, -0.5f, 0.5f   // 5: Bottom-right-front
                  0.5f, 0.5f, 0.5f    // 6: Top-right-front
                  -0.5f, 0.5f, 0.5f    // 7: Top-left-front
              },
              // Colors for each vertex (R, G, B)
              {
                  1.0f, 0.0f, 0.0f
                  0.0f, 1.0f, 0.0f
                  0.0f, 0.0f, 1.0f
                  1.0f, 1.0f, 0.0f
                  0.0f, 1.0f, 1.0f
                  1.0f, 0.0f, 1.0f
                  0.5f, 0.5f, 0.5f
                  1.0f, 1.0f, 1.0f
              },
              // Normals for each vertex (pointing outward from each face)
              {
                  0.0f, 0.0f, -1.0f, // Back face
                  0.0f, 0.0f, -1.0f,
                  0.0f, 0.0f, -1.0f,
                  0.0f, 0.0f, -1.0f,
                  0.0f, 0.0f, 1.0f,  // Front face
                  0.0f, 0.0f, 1.0f,
                  0.0f, 0.0f, 1.0f,
                  0.0f, 0.0f, 1.0f
              },
              // Indices defining the triangles of the cube (two per face)
              {
                  0, 1, 2, 2, 3, 0, // Back face
                  4, 5, 6, 6, 7, 4, // Front face
                  0, 4, 7, 7, 3, 0, // Left face
                  1, 5, 6, 6, 2, 1, // Right face
                  3, 2, 6, 6, 7, 3, // Top face
                  0, 1, 5, 5, 4, 0  // Bottom face
              },
              // Texture coordinates for each vertex
              {
                  {0.0f, 0.0f}, // Bottom-left
                  {1.0f, 0.0f}, // Bottom-right
                  {1.0f, 1.0f}, // Top-right
                  {0.0f, 1.0f}, // Top-left
                  {0.0f, 0.0f}, // Bottom-left (front face)
                  {1.0f, 0.0f}, // Bottom-right
                  {1.0f, 1.0f}, // Top-right
                  {0.0f, 1.0f}  // Top-left
              }) {
    }

    void draw() override {
        // Custom draw logic for Cube3D if needed.
        // Otherwise, call base class draw (if implemented)
        Shape3D::draw();
    }
};

