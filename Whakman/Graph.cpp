#include "Graph.h"
#include "LevelDataManager.h"
#include "GameManager.h"
#include "RigidbodyComponent.h"

Graph::Graph() {
  const unsigned char* tiles = LevelDataManager::get_level_data(GameManager::get_level())->map;
  for (int i = 0; i < LevelDataManager::k_NUMBER_TILES; ++i) {
    if (tiles[i] != k_TILE_TYPE_NONE) {
      _edges[i] = std::vector<int>{};
    }
  }
  for (auto edge : _edges) {
    int end_node;
    if ((tiles[edge.first] & static_cast<unsigned char>(RigidbodyComponent::Direction::DOWN)) > 0) {
      end_node = (edge.first + LevelDataManager::k_NUMBER_COLUMNS) % LevelDataManager::k_NUMBER_TILES;
      add_edge(edge.first, end_node);
    }
    if ((tiles[edge.first] & static_cast<unsigned char>(RigidbodyComponent::Direction::RIGHT)) > 0) {
      end_node = edge.first + 1;
      if (end_node % LevelDataManager::k_NUMBER_COLUMNS == 0) {
        end_node -= LevelDataManager::k_NUMBER_COLUMNS;
      }
      add_edge(edge.first, end_node);
    }
  }
}
