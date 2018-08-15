#include "GameManager.h"
#include "ImageManager.h"
#include "LevelDataManager.h"

const float GameManager::k_NEXT_STATE_TIME              = 2.0f;

const std::string GameManager::k_TEXT_SCORE             = "Score: ";
const std::string GameManager::k_MESSAGE_READY          = "   READY!";
const std::string GameManager::k_MESSAGE_IN_GAME        = "   Level: ";
const std::string GameManager::k_MESSAGE_LEVEL_BEATEN   = "  YOU WIN";
const std::string GameManager::k_MESSAGE_LIFE_LOST      = "  YOU LOSE";
const std::string GameManager::k_MESSAGE_GAME_OVER      = "GAME OVER         press R to restart";

IImage* GameManager::_image;
IFont* GameManager::_font;
GameManager::State GameManager::_state;
float GameManager::_state_timer;
int GameManager::_level;
int GameManager::_score;
int GameManager::_lives;

void GameManager::init(ISBZLibrary* lib) {
  _image = ImageManager::get_image(10);
  _font = lib->load_font("fonts/LondonBetween.ttf");
  start();
}

void GameManager::deinit() {
  _font->destroy();
}

void GameManager::update(World* world, ISBZLibrary* lib, const float& dt) {
  update_input(world, lib);
  update_state_machine(world, dt);
  update_hud();
}

void GameManager::set_state(const State& state) {
  _state = state;
  _state_timer = 0.0f;
}

void GameManager::start() {
  set_state(State::READY);
  _level = 0;
  _score = 0;
  _lives = k_NUMBER_LIVES - 1;
}

void GameManager::update_input(World* world, ISBZLibrary* lib) {
  if (_state != State::GAME_OVER) {
    return;
  }

  int keys[8];
  int nr_pressed = lib->pressed_keys(keys, 8);
  for (int i = 0; i < nr_pressed; ++i) {
    switch (keys[i]) {
    case 'r':
      start();
      world->deinit();
      world->init();
      break;
    }
  }
}

void GameManager::update_state_machine(World* world, const float& dt) {
  if (_state == State::IN_GAME || _state == State::GAME_OVER) {
    return;
  }

  _state_timer += dt;
  if (_state_timer >= k_NEXT_STATE_TIME) {
    switch (_state) {
    case State::READY:
      set_state(State::IN_GAME);
      break;
    case State::LEVEL_BEATEN:
      _level = (_level + 1) % LevelDataManager::get_level_size();
      set_state(State::READY);
      world->deinit();
      world->init();
      break;
    case State::LIFE_LOST:
      if (_lives > 0) {
        --_lives;
        set_state(State::READY);
        world->deinit_actors();
        world->init_actors();
      }
      else {
        set_state(State::GAME_OVER);
      }
      break;
    }
  }
}

void GameManager::update_hud() {
  _font->draw(k_HUD_SCORE_X, k_HUD_Y, (k_TEXT_SCORE + std::to_string(_score)).c_str(), IFont::Color(255, 255, 255, 0));

  switch (_state) {
  case State::READY:
    _font->draw(k_HUD_MESSAGE_X, k_HUD_Y, k_MESSAGE_READY.c_str(), IFont::Color(0, 255, 0, 0));
    break;
  case State::IN_GAME:
    _font->draw(k_HUD_MESSAGE_X, k_HUD_Y, (k_MESSAGE_IN_GAME + std::to_string(_level + 1)).c_str(), IFont::Color(0, 255, 0, 0));
    break;
  case State::LEVEL_BEATEN:
    _font->draw(k_HUD_MESSAGE_X, k_HUD_Y, k_MESSAGE_LEVEL_BEATEN.c_str(), IFont::Color(255, 255, 0, 0));
    break;
  case State::LIFE_LOST:
    _font->draw(k_HUD_MESSAGE_X, k_HUD_Y, k_MESSAGE_LIFE_LOST.c_str(), IFont::Color(255, 255, 0, 0));
    break;
  case State::GAME_OVER:
    _font->draw(k_HUD_MESSAGE_X, k_HUD_Y, k_MESSAGE_GAME_OVER.c_str(), IFont::Color(255, 0, 0, 0));
    break;
  }

  int x = k_HUD_LIVES_RIGHT_X;
  for (int i = 0; i < _lives; ++i) {
    x -= k_HUD_LIVES_IMAGE_SIZE;
    _image->draw(x, k_HUD_Y);
  }
}
