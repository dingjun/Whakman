#include "LevelDataManager.h"

const unsigned char LevelDataManager::k_MAP_1[LevelDataManager::k_NUMBER_TILES] = {
  5, 3, 3, 7, 3, 3, 7, 3, 3, 6,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  13, 3, 3, 15, 3, 3, 15, 3, 3, 14,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  13, 3, 3, 15, 3, 3, 15, 3, 3, 14,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  9, 3, 3, 11, 3, 3, 11, 3, 3, 10
};
const unsigned char LevelDataManager::k_MAP_2[LevelDataManager::k_NUMBER_TILES] = {
  5, 3, 3, 7, 3, 3, 7, 3, 3, 6,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  15, 3, 3, 15, 3, 3, 15, 3, 3, 15,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  15, 3, 3, 15, 3, 3, 15, 3, 3, 15,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  12, 0, 0, 12, 0, 0, 12, 0, 0, 12,
  9, 3, 3, 11, 3, 3, 11, 3, 3, 10
};
const unsigned char LevelDataManager::k_COIN_1[LevelDataManager::k_NUMBER_TILES] = {
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const unsigned char LevelDataManager::k_COIN_2[LevelDataManager::k_NUMBER_TILES] = {
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const std::vector<float> LevelDataManager::k_GHOST_X_1{ 512.0f, 576.0f };
const std::vector<float> LevelDataManager::k_GHOST_X_2{ 512.0f, 576.0f };
const std::vector<float> LevelDataManager::k_GHOST_Y_1{ 576.0f, 512.0f };
const std::vector<float> LevelDataManager::k_GHOST_Y_2{ 576.0f, 512.0f };
const std::vector<float> LevelDataManager::k_GHOST_INTELLIGENCE_1{ 0.6f, 0.9f };
const std::vector<float> LevelDataManager::k_GHOST_INTELLIGENCE_2{ 0.6f, 0.9f };
const float LevelDataManager::k_WHAKMAN_X_1 = 0.0f;
const float LevelDataManager::k_WHAKMAN_X_2 = 0.0f;
const float LevelDataManager::k_WHAKMAN_Y_1 = 0.0f;
const float LevelDataManager::k_WHAKMAN_Y_2 = 0.0f;

std::vector<LevelData*> LevelDataManager::_level;

void LevelDataManager::init() {
  _level.push_back(new LevelData(k_MAP_1, k_COIN_1, k_GHOST_X_1, k_GHOST_Y_1, k_GHOST_INTELLIGENCE_1, k_WHAKMAN_X_1, k_WHAKMAN_Y_1));
  _level.push_back(new LevelData(k_MAP_2, k_COIN_2, k_GHOST_X_2, k_GHOST_Y_2, k_GHOST_INTELLIGENCE_2, k_WHAKMAN_X_2, k_WHAKMAN_Y_2));
}

void LevelDataManager::deinit() {
  for (auto level : _level) {
    delete level;
  }
  _level.clear();
}
