#include "BitmapHandler.hpp"
#include "GL/gl.h"
#include "ext/stb_image.h"
#include <iostream>

GLuint BitmapHandler::loadBitmap(const std::string& name, const std::string& filename, GLint magFilter, GLint minFilter) {
  GLuint newId;
  // take care of textures
  glGenTextures(1, &newId);
  glBindTexture(GL_TEXTURE_2D, newId);
  int width, height, nchan;
  unsigned char* dt;
  dt = stbi_load(filename.c_str(), &width, &height, &nchan, 0);
  if (!dt) {
    std::cerr << "Couldn't load " << filename << "!\n";
    return 0;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dt);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  stbi_image_free(dt);
  
  loadedTextures[name] = newId;
  return newId;
}

GLuint BitmapHandler::getBitmap(const std::string& name) {
  if (!loadedTextures.count(name)) {
    std::cerr << "Texture name " << name << " not found!\n";
    return 0;
  }
  return loadedTextures[name];
}
void BitmapHandler::removeBitmap(const std::string& name) {
  if (!loadedTextures.count(name)) {
    return;
  }
  GLuint texId = loadedTextures[name];
  glDeleteTextures(1, &texId);
  loadedTextures.erase(name);
}



