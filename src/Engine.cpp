#include "Engine.hpp"

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <util/Shader.hpp>

Engine *Engine::instance = nullptr;

Engine::Engine() {
  name = "3D Engine";
  width = 800;
  height = 600;
  fullscreen = false;
  displayMode = GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
}

void Engine::fixedUpdate() {
  angle += 1.0f;
  if (angle >= 360.0f) {
    angle -= 360.0f;
  }
}

void Engine::setupTimer() {
  // TODO: this is temporary
  glutTimerFunc(
      20,
      [](int x) {
        instance->fixedUpdate();
        instance->setupTimer();
        glutPostRedisplay();
      },
      1);
}

void Engine::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glLoadIdentity(); // Reset transformations
  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(projection));
  // Set up the view matrix (camera)
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(view));

  // Draw a red solid teapot
  glColor3f(1.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(-1.0f, 1.0f, 0.0f);
  glRotatef(-angle, 0.0, 1.0, 0.0);
  glutSolidTeapot(0.5);
  glPopMatrix();

  // Draw a green wireframe sphere
  glColor3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
  glTranslatef(1.0f, 1.0f, 0.0f);
  glutWireSphere(0.5, 20, 20);
  glPopMatrix();

  // Draw a blue solid cube
  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(-1.0f, -1.0f, 0.0f);
  glutSolidCube(0.8);
  glPopMatrix();

  // Draw a yellow wireframe cone
  glColor3f(1.0f, 1.0f, 0.0f);
  glPushMatrix();
  glTranslatef(1.0f, -1.0f, 0.0f);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glutWireCone(0.5, 1.0, 20, 20);
  glPopMatrix();
  glutSwapBuffers();
}

void Engine::onSpecial(int key, int x, int y) {
  std::cout << "Pressed Special: " << key << std::endl;
}

void Engine::onSpecialUp(int key, int x, int y) {
  std::cout << "Released Special: " << key << std::endl;
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
  std::cout << "Pressed: " << key << std::endl;
  if (key == 27) {
    std::cout << "Quitting..." << std::endl;
    std::exit(0);
  }
}

void Engine::onKeyboardUp(unsigned char key, int x, int y) {
  std::cout << "Released: " << key << std::endl;
}

Engine::~Engine() { instance = nullptr; }

void Engine::mainLoop() { glutMainLoop(); }

void Engine::onReshape(int width, int height) {
  this->width = width;
  this->height = height;
  glViewport(0, 0, width, height);
}

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

void Engine::onPassiveMotion(int x, int y) {
  if (warped) {
    warped = false;
    return;
  }
  int halfw = width / 2;
  int halfh = height / 2;

  std::cout << "PassiveMotion: " << x - halfw << ", " << y - halfh << std::endl;
  if (x != halfw || y != halfh) {
    glutWarpPointer(halfw, halfh);
    warped = true;
  }

  int dx = x - halfw;
  if (std::abs(dx) >= 0) {
    view = glm::rotate<float>(view, dx / 100.f, glm::vec3(0.0, 1.0, 0.0));
  }
}

void Engine::onMouseWheel(int wheel, int direction, int x, int y) {
  std::cout << "Mouse wheel: " << wheel << ", " << direction << ", " << x
            << ", " << y << std::endl;
  const float DEG_IN_RAD = 0.01745329;
  fov -= direction * DEG_IN_RAD;
  std::cout << "New FOV: " << fov * (180 / 3.14) << std::endl;

  projection = glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);
}

void Engine::initialize(int *argc, char *argv[]) {
  if (instance != nullptr) {
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

  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

  // setup camera and projection
  cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);    // Camera position
  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Look at the origin
  cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // Camera's up vector
  //
  const float DEG_IN_RAD = 0.01745329;
  fov = 80 * DEG_IN_RAD;

  nearPlane = 0.1f;
  farPlane = 100.0f;
  view = glm::lookAt(cameraPos, cameraTarget, cameraUp); // Camera view matrix
  projection =
      glm::perspective(fov, (float)width / (float)height, nearPlane, farPlane);

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

  glutPassiveMotionFunc([](int x, int y) { instance->onPassiveMotion(x, y); });
  glutMotionFunc([](int x, int y) { instance->onPassiveMotion(x, y); });

  glutMouseWheelFunc([](int wheel, int direction, int x, int y) {
    instance->onMouseWheel(wheel, direction, x, y);
  });

  mainLoop();
}
