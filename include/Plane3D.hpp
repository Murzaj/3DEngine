#include "Shape3D.hpp"
#pragma once

class Plane3D : public Shape3D {
public:
  Plane3D()
      : Shape3D(
            // Vertices of a plane
            {
                -0.5f, 0.0f, -0.5f, // 0: Bottom-left-back
                0.5f,  0.0f, -0.5f, // 1: Bottom-right-back
                -0.5f, 0.0f,-0.5f, // 2: Top-right-back
                0.5f,  0.0f,  0.5f // 3: Top-left-back
            },
            // Colors for each vertex (R, G, B)
            {},
            // Normals for each vertex (pointing outward from each face)
            {
             0.0f, 0.0f, -1.0f, // Back face
             0.0f, 0.0f, -1.0f,
             0.0f, 0.0f, 1.0f, // Front face
             0.0f, 0.0f, 1.0f
            },
            // Indices defining the triangles of the cube (two per face)
            {
            },
            // Texture coordinates for each vertex
            {
                0.0f, 0.0f, // Bottom-left
                1.0f, 0.0f, // Bottom-right
                1.0f, 1.0f, // Top-right
                0.0f, 1.0f, // Top-left
                0.0f, 0.0f, // Bottom-left (front face)
                1.0f, 0.0f, // Bottom-right
                1.0f, 1.0f, // Top-right
                0.0f, 1.0f  // Top-left
            }) {}
};
