#pragma once

#include <vector>

#include "LevelDataManager.h"
#include "GameObject.h"
#include "sbzwhakman.h"

class GameObject;

class World {
public:
  World();
  ~World();

  void init();
  void deinit();
  void init_actors();
  void deinit_actors();

  void update(ISBZLibrary* lib, const float& dt);

  void set_actor_to_next_position(GameObject& actor, const float& new_x, const float& new_y, const bool& is_colliding_another_tile);
  void set_actor_to_tile_position(GameObject& actor);

  bool is_actor_colliding_with_another_tile(const float& x, const float& y, const float& new_x, const float& new_y) const;
  bool is_actor_direction_valid(const GameObject& actor, const bool& is_checking_next_direction) const;

  int get_current_tile_index(const GameObject& actor) const;
  
  inline const GameObject& get_whakman() const { return *_whakman; }
  inline const int get_tile_size() const { return k_TILE_SIZE; }
  inline const int get_world_width() const { return k_WORLD_WIDTH; }
  inline const int get_world_height() const { return k_WORLD_HEIGHT; }

private:
  const int k_TILE_SIZE           = 64;
  const int k_HALF_TILE_SIZE      = k_TILE_SIZE / 2;
  const int k_WORLD_WIDTH         = k_TILE_SIZE * LevelDataManager::k_NUMBER_COLUMNS;
  const int k_WORLD_HEIGHT        = k_TILE_SIZE * LevelDataManager::k_NUMBER_ROWS;

  const float k_RADIUS_COIN       = 22.0f;
  const float k_RADIUS_GHOST      = 26.0f;
  const float k_RADIUS_WHAKMAN    = 0.0f;
  const float k_SPEED_GHOST       = 123.0f;
  const float k_SPEED_WHAKMAN     = 120.0f;

  void init_tiles();
  void init_coins();
  void deinit_whakman();

  void check_coin_with_whakman(const int& tile_index);
  void check_items_with_whakman();
  void check_ghosts_with_whakman();
  
  int get_tile_index_from_tile_coordinates(int x, int y) const;

  inline int get_tile_index_from_world_coordinates(const int& x, const int& y) const {
    return get_tile_index_from_tile_coordinates(x / k_TILE_SIZE, y / k_TILE_SIZE); }
  
  std::vector<GameObject*> _tiles;
  std::vector<GameObject*> _coins;
  std::vector<GameObject*> _ghosts;
  GameObject* _whakman;
  int _left_coins;
};
