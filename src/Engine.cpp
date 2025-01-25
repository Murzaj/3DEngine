#include "Engine.hpp"
#include "UpdatableObject.hpp"

#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <algorithm>
#include <iostream>
#include <ostream>

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb_image.h"


Engine *Engine::instance = nullptr;

Engine::Engine() {
  name = "3D Engine";
  width = 800;
  height = 600;
  fixedUpdateMs = 20;
  fullscreen = false;
  bitmapHandler = new BitmapHandler();
  displayMode = GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
}

Engine::~Engine() { 
  cleanupObjects();
  delete bitmapHandler;
  instance = nullptr;
}


void Engine::setupView(float farPlane, float nearPlane, float fov, glm::vec3 cameraPos, glm::vec3 cameraLookAt, glm::vec3 cameraUp) {
  Observer *oldObserver = nullptr;
  if(observer != nullptr) {
    oldObserver = observer;
  }
  observer = new Observer(cameraPos, cameraLookAt, cameraUp);
  fov = fov;
  farPlane = farPlane;
  nearPlane = nearPlane;
  onReshape(width, height);
  if(oldObserver != nullptr) {
    delete oldObserver;
  }
}

void Engine::setupLight(
                        const glm::vec3 &ambient,
                        const glm::vec3 &diffuse,
                        const glm::vec3 &specular,
                        const glm::vec3 &position,
                        const glm::vec3 &direction,
                        float spotCutoffAngle,
                        float spotExponent,
                        float constantAttantuation,
                        float linearAttentuation,
                        float quadraticAttentuation
) {
  glEnable(GL_LIGHT0);
  GLfloat amb[] = {ambient.r, ambient.g, ambient.b, 1.0}; // RGBA
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

  GLfloat diff[] = {diffuse.r, diffuse.g, diffuse.b, 1.0}; // RGBA
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

  GLfloat spec[] = {specular.r, specular.g, specular.b, 1.0}; // RGBA
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

  GLfloat lightPos[] = {position.x, position.y, position.z, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  GLfloat spotDir[] = {direction.x, direction.y, direction.z};
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoffAngle);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantAttantuation);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttentuation);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttentuation);
}

void Engine::display() {
  const auto view = observer->getTransform();
  glShadeModel(GL_SMOOTH);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(projection));
  // Set up the view matrix (camera)
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(view));

  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  GLfloat emiss[] = {0.0, 0.0, 0.0, 1.0};
  glMaterialfv(GL_FRONT, GL_EMISSION, emiss);
  GLfloat specul[] = {0.5, 0.5, 0.5, 1.0};
  glMaterialfv(GL_FRONT, GL_SPECULAR, specul);

  for (auto shape : shapes) {
    shape->draw(view);
  }

  glutSwapBuffers();
}

template <typename T> void removeFromVector(std::vector<T> &vec, T obj) {
  vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());
}

void Engine::fixedUpdate() {
  angle += 1.0f;
  if (angle >= 360.0f) {
    angle -= 360.0f;
  }

  if(inputMap->isKeyDown(27)) {
    stop();
  }
  if(inputMap->isKeyJustPressed('l')) {
    toggleLighting();
  }

  for(auto updatable : updatables) {
    updatable->update(fixedUpdateMs, *inputMap, this);
  }

  inputMap->resetTemporary();
}

void Engine::setupTimer() {
  // TODO: this is temporary
  glutTimerFunc(
      fixedUpdateMs,
      [](int x) {
        instance->fixedUpdate();
        instance->setupTimer();
        glutPostRedisplay();
      },
      1);
}


void Engine::onSpecial(int key, int x, int y) {}
void Engine::onSpecialUp(int key, int x, int y) {}

bool Engine::isLightingEnabled() const {
  return lightingEnabled;
}

void Engine::toggleLighting() {
  if (lightingEnabled) {
    glDisable(GL_LIGHTING);
    lightingEnabled = false;
  }
  else {
    glEnable(GL_LIGHTING);
    lightingEnabled = true;
  }
}


void Engine::onKeyboard(unsigned char key, int x, int y) {
  inputMap->setKeyDown(key);
}

void Engine::onKeyboardUp(unsigned char key, int x, int y) {
  inputMap->setKeyUp(key);
}

void Engine::mainLoop() { glutMainLoop(); }

void Engine::onReshape(int width, int height) {
  this->width = width;
  this->height = height;
  projection =
      glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);
  glViewport(0, 0, width, height);
}

void Engine::setFixedUpdateFps(float fps) { fixedUpdateMs = 1000 / fps; }

void Engine::setVideoMode(int width, int height, bool fullscreen,
                          bool zBuffer) {
  this->width = width;
  this->height = height;
  this->fullscreen = fullscreen;
  displayMode = GLUT_RGB | GLUT_DOUBLE;
  if (zBuffer) {
    displayMode |= GLUT_DEPTH;
  }
}

void Engine::setClearColor(const glm::vec4 &clearColor) {
  glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
}

void Engine::onMotion(int x, int y) {
  if (warped) {
    warped = false;
    return;
  }

  int halfw = width / 2;
  int halfh = height / 2;

  if (x != halfw || y != halfh) {
    glutWarpPointer(halfw, halfh);
    warped = true;
  }

  int dx = x - halfw;
  int dy = y - halfh;
  inputMap->setMouseMotion(dx,dy);
}


void Engine::onMouseFunc(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if(state == GLUT_UP) {
        inputMap->setLeftClickUp();
      }
      if (state == GLUT_DOWN) {
        inputMap->setLeftClickDown();
      }
    break;
    case GLUT_RIGHT_BUTTON:
      if(state == GLUT_UP) {
        inputMap->setRightClickUp();
      }
      if (state == GLUT_DOWN) {
        inputMap->setRightClickDown();
      }
    break;
  }
      


}






void Engine::onMouseWheel(int wheel, int direction, int x, int y) {
  const float DEG_IN_RAD = 0.01745329;
  fov -= direction * DEG_IN_RAD;
  projection = glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);
}

void Engine::prepareObjects() {
  inputMap = new InputMap;
}

void Engine::cleanupObjects() {
  for (auto x : objects) {
    removeObject(x);
  }
  delete observer;
  delete inputMap;
}


void Engine::prepareCallbacks() {
  // temporary
  instance->setupTimer();

  glutIgnoreKeyRepeat(true);
  glutDisplayFunc([]() { instance->display(); });
  glutSpecialFunc(
      [](int key, int x, int y) { instance->onSpecial(key, x, y); });
  glutSpecialUpFunc(
      [](int key, int x, int y) { instance->onSpecialUp(key, x, y); });
  glutKeyboardFunc(
      [](unsigned char key, int x, int y) { instance->onKeyboard(key, x, y); });
  glutKeyboardUpFunc([](unsigned char key, int x, int y) {
    instance->onKeyboardUp(key, x, y);
  });
  glutReshapeFunc([](int w, int h) { instance->onReshape(w, h); });
  glutPassiveMotionFunc([](int x, int y) { instance->onMotion(x, y); });
  glutMotionFunc([](int x, int y) { instance->onMotion(x, y); });
  glutMouseWheelFunc([](int wheel, int direction, int x, int y) {
    instance->onMouseWheel(wheel, direction, x, y);
  });

  glutMouseFunc([](int button, int state, int x, int y){ instance->onMouseFunc(button, state, x, y); });
}



bool Engine::initialize(int *argc, char *argv[]) {
  if (instance != nullptr) {
    return false;
  }

  instance = this;
  glutInit(argc, argv);
  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutSetOption(GLUT_MULTISAMPLE, 4);
  glutInitDisplayMode(displayMode);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(name.c_str());
  if (fullscreen) {
    glutFullScreen();
  }
  glutSetCursor(GLUT_CURSOR_NONE);
  glewInit();

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);

  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);


  const float DEG_IN_RAD = 0.01745329;
  fov = 80 * DEG_IN_RAD;
  nearPlane = 0.1f;
  farPlane = 100.0f;
  projection = glm::perspective(fov, width / (float)height, nearPlane, farPlane);
  return true;
}


void Engine::run() {
  if(observer == nullptr) {
    std::cerr << "Please call setupView() at least once!" << std::endl;
  }
  prepareObjects();
  prepareCallbacks();
  mainLoop();
}


EngineManager *Engine::getEngineManager() { return this; }
BitmapHandler *Engine::getBitmapHandler() { return bitmapHandler; }



void Engine::addObject(GameObject *obj) {
  obj->init(this);
  // Add to the general objects vector
  objects.push_back(obj);
  
  // Check for DrawableObject interface
  if (auto shape = dynamic_cast<Shape3D *>(obj)) {
      shapes.push_back(shape);
  }
  if (auto updatable = dynamic_cast<UpdatableObject *>(obj)) {
    updatables.push_back(updatable);
  }
}


GameObject *Engine::getFirstOfType(const std::type_info &type) const {
  for (GameObject *obj : objects) {
    if (typeid(*obj) == type) {
      return obj;
    }
  }
  return nullptr; // Not found
}
void Engine::removeObject(GameObject *obj) {
  std::cout << "Removing." << std::endl;
  if (auto shape = dynamic_cast<Shape3D *>(obj)) {
    std::cout << "Removing Shape." << std::endl;
    removeFromVector(shapes, shape);
  }
  if (auto updatable = dynamic_cast<UpdatableObject *>(obj)) {
    std::cout << "Removing Updatable." << std::endl;
    removeFromVector(updatables, updatable);
  }
  removeFromVector(objects, obj);
  cleanupTable.push_back(obj);
  //delete obj;
}


void Engine::stop() {
  cleanupObjects();
  std::exit(0);
}

