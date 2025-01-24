#pragma once


#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "BitmapHandler.hpp"
#include "GameObject.hpp"
#include "ObjectManager.hpp"
#include "Shape3D.hpp"
#include "Observer.hpp"
#include "InputMap.hpp"
#include "UpdatableObject.hpp"


class UpdatableObject;
class Engine : public Initializer, public ObjectManager {

protected:
  static Engine *instance;
  std::string name;

  // Initialize the camera and projection matrix
  Observer *observer;

  std::vector<GameObject *> objects;
  std::vector<UpdatableObject *> updatables;
  std::vector<Shape3D *> shapes;

  Shape3D *cube;
  Shape3D *gem;
  Shape3D *orb;
  Shape3D *boulder;
  Shape3D *ground;
  Shape3D *sphereBasicTest;
  InputMap *inputMap;

  float farPlane;
  float nearPlane;
  float fov;

  float fixedUpdateMs;

  int width;
  int height;
  unsigned int displayMode;
  bool fullscreen;


  BitmapHandler *bitmapHandler;


  GLfloat lightPos[4];

  glm::mat4 projection;

  GLuint vertexbuffer = 0;
  GLuint simpleShaderID = 0;
  float angle = 0.0f;


  bool warped = false;

  void prepareTextures();

  void prepareObjects();
  void cleanupObjects();

  void prepareCallbacks();


  bool lightingEnabled = true;
  void toggleLighting();


  void setupTimer();
  void fixedUpdate();
  void display();
  void onKeyboard(unsigned char key, int x, int y);
  void onSpecial(int key, int x, int y);
  void onSpecialUp(int key, int x, int y);
  void onKeyboardUp(unsigned char key, int x, int y);
  void onReshape(int width, int height);
  void onMotion(int x, int y);
  void onMouseWheel(int wheel, int direction, int x, int y);


  void drawBox();

  float sphereX = 1.0f;
  float sphereY = 1.0f;



public:
  Engine();
  virtual ~Engine();
  bool initialize(int* argc, char *argv[]);
  void run();
  void mainLoop();
  void setClearColor(const glm::vec4 &color);
  void setVideoMode(int width, int height, bool fullscreen, bool zBuffer);
  void setFixedUpdateFps(float fps);

  ObjectManager *getObjectManager() override;
  void addObject(GameObject *obj) override;
  void removeObject(GameObject *obj) override;
  GameObject *getFirstOfType(const std::type_info &type) const override;
  BitmapHandler *getBitmapHandler() override;

  void setupLight(
                          const glm::vec3 &ambient,
                          const glm::vec3 &diffuse,
                          const glm::vec3 &specular,
                          const glm::vec3 &position,
                          const glm::vec3 &direction,
                          float spotCutoffAngle,
                          float spotExponent,
                          float constantAttantuation,
                          float linearAttentuation,
                          float quadraticAttentuation);




};
