#include "Application.h"
#include "ImageManager.h"
#include "GameManager.h"
#include "LevelDataManager.h"

Application::Application(ISBZLibrary* lib)
  : _lib(lib) {
  _lib->init(k_WINDOW_WIDTH, k_WINDOW_HEIGHT);

  ImageManager::init(_lib);
  GameManager::init(_lib);
  LevelDataManager::init();
  _world = new World();

  _prev_time = _lib->time();
}

Application::~Application() {
  ImageManager::deinit();
  GameManager::deinit();
  LevelDataManager::deinit();
  delete _world;
}

void Application::update() {
  while (_lib->update()) {
    float curr_time = _lib->time();
    float dt = curr_time - _prev_time;
    _prev_time = curr_time;

    GameManager::update(_world, _lib, dt);
    _world->update(_lib, dt);
  }
}
