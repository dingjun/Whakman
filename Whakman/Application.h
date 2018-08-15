#pragma once

#include "World.h"
#include "sbzwhakman.h"

class Application {
public:
  Application(ISBZLibrary* lib);
  ~Application();

  void update();

private:
  const int k_WINDOW_WIDTH    = 640;
  const int k_WINDOW_HEIGHT   = 664;

  ISBZLibrary* _lib;
  World* _world;
  float _prev_time;
};
