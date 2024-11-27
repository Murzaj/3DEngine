#include "Engine.hpp"

#include <GL/freeglut_std.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
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
        if(instance->angle >= 360.0f) {
          instance->angle -= 360.0f;
        }
        std::cout << "Angle: " << instance->angle << std::endl;
        instance->setupTimer();
        glutPostRedisplay();
      },
      1);
}

void Engine::testOpenGL2GlutPrimitiveDisplay() {
  // REMOVE LATER
  glLoadIdentity(); // Reset transformations
  // Set up the camera
  gluLookAt(0.0, 0.0, 5.0,  // Camera position
            0.0, 0.0, 0.0,  // Look-at point
            0.0, 1.0, 0.0); // Up vector

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

void Engine::onKeyboard(unsigned char key, int x, int y) {
  if (key == 27) {
    std::exit(0);
  }
  std::cout << "Pressed: " << key << ", pos: " << x << ", " << y << "\n";
}

Engine::~Engine() { instance = nullptr; }

void Engine::mainLoop() { glutMainLoop(); }

void setupProjection() {
  glMatrixMode(GL_PROJECTION); // Switch to the Projection Matrix
  glLoadIdentity();            // Reset the Projection Matrix

  // Set up a perspective projection
  gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW); // Switch back to the Modelview Matrix
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
  setupProjection();

  // simpleShaderID = util::loadShaders("shader/SimpleVertexShader.vert",
  // "shader/SimpleFragmentShader.frag");

  // bind events to instance using lambdas

  instance->setupTimer();

  glutDisplayFunc([]() { instance->display(); });

  glutKeyboardFunc(
      [](unsigned char key, int x, int y) { instance->onKeyboard(key, x, y); });

  // glutReshapeFunc([](int x,int y){ return; });
  mainLoop();
}
