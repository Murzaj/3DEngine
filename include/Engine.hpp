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
#include "EngineManager.hpp"
#include "Shape3D.hpp"
#include "Observer.hpp"
#include "InputMap.hpp"
#include "UpdatableObject.hpp"


class UpdatableObject;
class Engine : public Initializer, public EngineManager {

protected:
  static Engine *instance;
  std::string name;

  // Initialize the camera and projection matrix
  Observer *observer = nullptr;

  std::vector<GameObject *> objects;
  std::vector<UpdatableObject *> updatables;
  std::vector<Shape3D *> shapes;
  std::vector<GameObject *> cleanupTable;

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
  void onMouseFunc(int button, int state, int x, int y);
  void drawBox();

public:
  Engine();
  virtual ~Engine();
  bool initialize(int* argc, char *argv[]);
  void run();
  void mainLoop();
  void setClearColor(const glm::vec4 &color);
  void setVideoMode(int width, int height, bool fullscreen, bool zBuffer);
  void setFixedUpdateFps(float fps);

  EngineManager *getEngineManager() override;
  void addObject(GameObject *obj) override;
  void removeObject(GameObject *obj) override;
  GameObject *getFirstOfType(const std::type_info &type) const override;
  BitmapHandler *getBitmapHandler() override;

  void stop() override;
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


  void setupView(float farPlane, float nearPlane, float fov, glm::vec3 cameraPos, glm::vec3 cameraLookAt, glm::vec3 cameraUp);
};
