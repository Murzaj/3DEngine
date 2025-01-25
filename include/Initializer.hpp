#pragma once

#include "BitmapHandler.hpp"

class EngineManager;

class Initializer { 
public:
  virtual BitmapHandler *getBitmapHandler() = 0;
  virtual EngineManager *getEngineManager() = 0;
};


