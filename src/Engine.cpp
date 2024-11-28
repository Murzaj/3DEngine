#include "Engine.hpp"

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/glew.h>
#include <GL/glu.h>
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
#include <cmath>

Engine *Engine::instance = nullptr;

Engine::Engine() { name = "3D Engine"; }

void Engine::fixedUpdate() {
  angle += 1.0f;
  if (angle >= 360.0f) {
    angle -= 360.0f;
  }
  view = glm::rotate<float>(view, rotationV, glm::vec3(0.0, 1.0, 0.0));
  fov += zoomV;
  projection = glm::perspective(fov, (float)width/(float)height, nearPlane, farPlane);
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
  switch (key) {
    case GLUT_KEY_LEFT:
      rotationV = -0.01;
      break;
    case GLUT_KEY_RIGHT:
      rotationV = +0.01;
      break;
    case GLUT_KEY_DOWN:
      zoomV += 0.01;
      break;
    case GLUT_KEY_UP:
      zoomV -= 0.01;
      break;
  }
}

void Engine::onSpecialUp(int key, int x, int y) {
  std::cout << "Released Special: " << key << std::endl;
  switch (key) {
    case GLUT_KEY_LEFT:
      if(rotationV < 0.0) {
        rotationV = 0.0;
      }
      break;
    case GLUT_KEY_RIGHT:
      if(rotationV > 0.0) {
        rotationV = 0.0;
      }
      break;
    case GLUT_KEY_UP:
      if(zoomV < 0.0) {
        zoomV = 0.0;
      }
      break;
    case GLUT_KEY_DOWN:
      if(zoomV > 0.0) {
        zoomV = 0.0;
      }
      break;
  }
}

void Engine::onKeyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    std::exit(0);
  }
  std::cout << "Pressed: " << key << std::endl;
}

void Engine::onKeyboardUp(unsigned char key, int x, int y) {
  std::cout << "Released: " << key << std::endl;
}

Engine::~Engine() { instance = nullptr; }

void Engine::mainLoop() { glutMainLoop(); }

void Engine::onReshape(int width, int height) {
  this->width = width;
  this->height = height;
  glViewport(0,0,width,height);
}

void Engine::initialize(int *argc, char *argv[]) {
  if (instance != nullptr) {
  }
  instance = this;

  width = 800;
  height = 800;

  glutInit(argc, argv);
  glutInitContextVersion(3,3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
  glutSetOption(GLUT_MULTISAMPLE, 4);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow(name.c_str());
  glewInit();


  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


  // setup camera and projection
  cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); // Camera position
  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Look at the origin
  cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Camera's up vector
  fov = 1.0f;
  nearPlane = 0.1f;
  farPlane = 100.0f;
  view = glm::lookAt(cameraPos, cameraTarget, cameraUp); // Camera view matrix
  projection = glm::perspective(fov, (float)width/(float)height, nearPlane, farPlane);
  
  
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
  glutKeyboardUpFunc(
      [](unsigned char key, int x, int y) { instance->onKeyboardUp(key, x, y); });

  glutReshapeFunc([](int w,int h){ instance->onReshape(w, h); });
  mainLoop();
}
