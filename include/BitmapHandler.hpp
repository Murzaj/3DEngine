#pragma once
#include <windows.h> 
#include <GL/gl.h>
#include <string>
#include <unordered_map>

class BitmapHandler {
public:
  GLuint loadBitmap(const std::string &name, const std::string &filename, GLint magFilter, GLint minFilter);
  GLuint getBitmap(const std::string &name);
  void removeBitmap(const std::string &name);
private:
  std::unordered_map<std::string, GLuint> loadedTextures;
};
