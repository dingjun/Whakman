#pragma once

#include "InputComponent.h"
#include "Graph.h"

class GhostInputComponent : public InputComponent {
public:
  GhostInputComponent(float intelligence);
  ~GhostInputComponent();
  virtual void update(GameObject& obj, World& world, ISBZLibrary* lib, const float& dt) override;

private:
  const float k_AI_INPUT_TIME = 0.5f;

  void set_next_direction_same_tile(RigidbodyComponent* rigidbody, const GameObject& ghost_obj, const GameObject& whatkman_obj, const int& tile_index, const int& tile_size);
  void set_next_direction(RigidbodyComponent* rigidbody, const GameObject& ghost_obj, const int& ghost, const int& whakman);
  void set_combo_direction(RigidbodyComponent* rigidbody, const GameObject& ghost_obj, const int& tile_index, const int& tile_size);
  void set_random_direction(RigidbodyComponent* rigidbody) const;

  int a_star_search(const int& self, const int& whakman) const;
  
  inline int get_x_coordinate(const int& tile_index) const { return tile_index % LevelDataManager::k_NUMBER_COLUMNS; }
  inline int get_y_coordinate(const int& tile_index) const { return tile_index / LevelDataManager::k_NUMBER_COLUMNS; }
  inline int get_x_distance(const int& start, const int& end) const { return abs(get_x_coordinate(end) - get_x_coordinate(start)); }
  inline int get_y_distance(const int& start, const int& end) const { return abs(get_y_coordinate(end) - get_y_coordinate(start)); }
  inline int get_manhattan_distance(const int& start, const int& end) const { return get_x_distance(start, end) + get_y_distance(start, end); }

  float _intelligence;
  float _timer;
  RigidbodyComponent::Direction _combo_dir;
  Graph* _graph;
};
