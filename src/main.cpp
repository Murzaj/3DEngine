#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include "Engine.hpp"
#include "ModelLoader.hpp"
#include "game/FallingBoulder.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) 
{   
  std::srand(std::time(NULL));
  Engine engine;
  engine.setVideoMode(800, 600, false, true);
  engine.setFixedUpdateFps(60);
  if(!engine.initialize(&argc, argv)) std::exit(1);

  engine.setClearColor(glm::vec4(0.0f,0.0f,0.0f, 1.0f));
  auto handler = engine.getBitmapHandler();

  auto rockTexture = handler->loadBitmap("rock", "rock.jpg", GL_LINEAR, GL_LINEAR);
  auto boulderTexture = handler->loadBitmap("boulder", "boulder.jpg", GL_LINEAR, GL_LINEAR);

  auto boulderModel = modelloader::texturedShapeFromOBJ("boulder.obj", handler->getBitmap("boulder"));


  engine.addObject(new FallingBoulder(
  glm::vec3(0.0, 8.0, 0.0),
  glm::vec3(4.0, 1.0, 4.0),
  1.0f, 2.0f,
  1.0f, 1.5f,
  0.0f, boulderModel));

  engine.setupLight(
    //amb, diff, spec
    glm::vec3(0.2, 0.2, 0.2),
    glm::vec3(0.9, 0.9, 0.9),
    glm::vec3(1.0, 1.0, 1.0),

    // pos
    glm::vec3(3.0, 2.0, -3.0),
    // dir
    glm::vec3(-0.5, -1.0, 0.0),
    // cutoff,exponent, attentuation
    90.0,
    2.0,
    0.0,1.0,0.2
  );
  engine.run();
  return 0;
}
