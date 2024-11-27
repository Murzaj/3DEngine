#pragma once

#include <GL/glew.h>
#include <string>


class Engine {
protected:
  static Engine *instance;
  std::string name;


  GLuint vertexbuffer = 0;
  GLuint simpleShaderID = 0;
  float angle = 0.0f;


  void setupTimer();
  void testOpenGL2GlutPrimitiveDisplay(); // REMOVE LATER
public:
  virtual ~Engine();
  void initialize(int* argc, char *argv[]);
  Engine();

  void display();
  void onKeyboard(unsigned char key, int x, int y);
  void mainLoop();
};
