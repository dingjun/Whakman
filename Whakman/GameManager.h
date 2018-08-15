#pragma once

#include <string>

#include "World.h"
#include "sbzwhakman.h"

class World;

class GameManager {
public:
  enum State {
    READY,
    IN_GAME,
    LEVEL_BEATEN,
    LIFE_LOST,
    GAME_OVER
  };

  static const int k_POINTS_COIN            = 10;
  static const int k_POINTS_BONUS           = 100;
  static const int k_POINTS_GHOST           = 200;    // TODO: increasing in single powerup

  static void init(ISBZLibrary* lib);
  static void deinit();
  static void update(World* world, ISBZLibrary* lib, const float& dt);
  static void set_state(const State& state);

  inline static void add_points(const int& points) { _score += points; }
  inline static State get_state() { return _state; }
  inline static int get_level() { return _level; }

private:
  static const int k_NUMBER_LIVES           = 3;

  static const int k_HUD_LIVES_IMAGE_SIZE   = 24;
  static const int k_HUD_SCORE_X            = 60;
  static const int k_HUD_MESSAGE_X          = 255;
  static const int k_HUD_LIVES_RIGHT_X      = 580;
  static const int k_HUD_Y                  = 640;

  static const float k_NEXT_STATE_TIME;

  static const std::string k_TEXT_SCORE;
  static const std::string k_MESSAGE_READY;
  static const std::string k_MESSAGE_IN_GAME;
  static const std::string k_MESSAGE_LEVEL_BEATEN;
  static const std::string k_MESSAGE_LIFE_LOST;
  static const std::string k_MESSAGE_GAME_OVER;

  static void start();
  static void update_input(World* world, ISBZLibrary* lib);
  static void update_state_machine(World* world, const float& dt);
  static void update_hud();

  static IImage* _image;
  static IFont* _font;
  static State _state;
  static float _state_timer;
  static int _level;
  static int _score;
  static int _lives;
};
