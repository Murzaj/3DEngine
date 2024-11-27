#include "Engine.hpp"

#include <GL/freeglut_std.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
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

Engine::Engine() { name = "3D Engine"; }

void Engine::setupTimer() {
  // TODO: this is temporary
  glutTimerFunc(
      20,
      [](int x) {
        instance->angle = instance->angle + 1.0f;
        if (instance->angle >= 360.0f) {
          instance->angle -= 360.0f;
        }
        instance->setupTimer();
        glutPostRedisplay();
      },
      1);
}

void Engine::testOpenGL2GlutPrimitiveDisplay() {
  // REMOVE LATER
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
}

void Engine::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  testOpenGL2GlutPrimitiveDisplay();
  glutSwapBuffers();
}

void Engine::onSpecial(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
      view = glm::rotate<float>(view, 0.1, glm::vec3(0.0, 1.0, 0.0));
      glutPostRedisplay();
      break;

    case GLUT_KEY_RIGHT:
      view = glm::rotate<float>(view, -0.1, glm::vec3(0.0, 1.0, 0.0));
      glutPostRedisplay();
      break;
  }
  std::cout << "Pressed Special: " << key << ", pos: " << x << ", " << y << std::endl;
}

void Engine::onSpecialUp(int key, int x, int y) {
  std::cout << "Released Special: " << key << ", pos: " << x << ", " << y << std::endl;

}

void Engine::onKeyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    std::exit(0);
  }
  std::cout << "Pressed: " << key << ", pos: " << x << ", " << y << std::endl;
}

void Engine::onKeyboardUp(unsigned char key, int x, int y) {
  std::cout << "Released: " << key << ", pos: " << x << ", " << y << std::endl;
}

Engine::~Engine() { instance = nullptr; }

void Engine::mainLoop() { glutMainLoop(); }

void Engine::onReshape(int width, int height) {
  glViewport(0,0,width,height);
  projection = glm::perspective(70.0f, width / (float)height, 0.1f, 1000.0f);
}

void Engine::initialize(int *argc, char *argv[]) {
  if (instance != nullptr) {
  }
  instance = this;

  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 600);
  glutCreateWindow(name.c_str());
  glewInit();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

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
