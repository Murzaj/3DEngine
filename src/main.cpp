#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include "Engine.hpp"
#include "ModelLoader.hpp"
#include "SphereShape3D.hpp"
#include "TexturedPlane3D.hpp"
#include "game/FallingBoulder.hpp"
#include "game/Player.hpp"
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
  auto groundModel = new TexturedPlane3D(glm::vec3(1.0f), handler->getBitmap("rock"));
  groundModel->translate(glm::vec3(.0f, -2.0f, .0f));
  groundModel->scale(glm::vec3(8.0f));



  //auto playerModel = modelloader::texturedShapeFromOBJ("player.obj", handler->getBitmap("player"));
  auto playerModel = new SphereShape3D(glm::vec3(1.0f), 1.0f, 8, 16);
  std::random_device rd;
  int boulderCount = 10;
  engine.addObject(new Player(playerModel, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
  engine.addObject(groundModel);



  for (int i = 0; i < boulderCount; i++) {
    engine.addObject(new FallingBoulder(
    glm::vec3(0.0, 8.0, 0.0),
    glm::vec3(4.0, 1.0, 4.0),
    1.0f, 2.0f,
    1.0f, 1.5f,
    0.0f, boulderModel, rd));
  }

  engine.setupView(8.0f, 0.0f,glm::radians(80.0f), glm::vec3(0, 2, 4), glm::vec3(0,0,0), glm::vec3(0, 1, 0));

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
    180.0,
    1.0,
    0.0,1.0,0.2
  );

  engine.run();
  return 0;
}
