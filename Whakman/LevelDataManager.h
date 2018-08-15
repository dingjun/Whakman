#pragma once

#include <vector>

// TODO: load from text/json file

struct LevelData {
  LevelData(
    const unsigned char* map,
    const unsigned char* coin,
    const std::vector<float>& ghost_x,
    const std::vector<float>& ghost_y,
    const std::vector<float>& ghost_intelligence,
    const float& whakman_x,
    const float& whakman_y
    )
    : map(map)
    , coin(coin)
    , ghost_x(ghost_x)
    , ghost_y(ghost_y)
    , ghost_intelligence(ghost_intelligence)
    , whakman_x(whakman_x)
    , whakman_y(whakman_y) {
  }

  const unsigned char* map;
  const unsigned char* coin;
  const std::vector<float> ghost_x;
  const std::vector<float> ghost_y;
  const std::vector<float> ghost_intelligence;
  const float whakman_x;
  const float whakman_y;
};

class LevelDataManager {
public:
  static const int k_NUMBER_COLUMNS   = 10;
  static const int k_NUMBER_ROWS      = 10;
  static const int k_NUMBER_TILES     = k_NUMBER_COLUMNS * k_NUMBER_ROWS;

  static void init();
  static void deinit();
  
  inline static int get_level_size() { return _level.size(); }
  inline static LevelData* get_level_data(const int& index) { return _level[index]; }

private:
  static const unsigned char k_MAP_1[k_NUMBER_TILES];
  static const unsigned char k_MAP_2[k_NUMBER_TILES];
  static const unsigned char k_COIN_1[k_NUMBER_TILES];
  static const unsigned char k_COIN_2[k_NUMBER_TILES];
  static const std::vector<float> k_GHOST_X_1;
  static const std::vector<float> k_GHOST_X_2;
  static const std::vector<float> k_GHOST_Y_1;
  static const std::vector<float> k_GHOST_Y_2;
  static const std::vector<float> k_GHOST_INTELLIGENCE_1;
  static const std::vector<float> k_GHOST_INTELLIGENCE_2;
  static const float k_WHAKMAN_X_1;
  static const float k_WHAKMAN_X_2;
  static const float k_WHAKMAN_Y_1;
  static const float k_WHAKMAN_Y_2;

  static std::vector<LevelData*> _level;
};
