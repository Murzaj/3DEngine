#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include "Engine.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) 
{   
  std::srand(std::time(NULL));
  Engine engine;
  engine.setVideoMode(800, 600, false, true);
  engine.setFixedUpdateFps(60);
  engine.initialize(&argc, argv);
  return 0;
}
