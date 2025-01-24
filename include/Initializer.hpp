#pragma once

#include "BitmapHandler.hpp"

class ObjectManager;

class Initializer { 
public:
  virtual BitmapHandler *getBitmapHandler() = 0;
  virtual ObjectManager *getObjectManager() = 0;
};


