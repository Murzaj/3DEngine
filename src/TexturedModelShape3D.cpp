#include "TexturedModelShape3D.hpp"
#include <windows.h> 
#include <GL/gl.h>


TexturedModelShape3D::TexturedModelShape3D(const std::vector<float> &verts, const std::vector<float> &colors, glm::vec3 modulateColor, const std::vector<float> &normals, const std::vector<unsigned int> &indices, const std::vector<float> &texCoord, GLuint textureId)
: ModelShape3D(verts, colors, modulateColor, normals, indices, texCoord), textureId(textureId)
{}


void TexturedModelShape3D::draw(const glm::mat4 &view) {
  glBindTexture(GL_TEXTURE_2D, textureId);
  ModelShape3D::draw(view);
  glBindTexture(GL_TEXTURE_2D, 0);
}


