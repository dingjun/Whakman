#pragma once

#include "GameObject.h"
#include "World.h"

class GameObject;
class World;

class RigidbodyComponent {
public:
  enum Direction : unsigned char {
    UP = 0b1000,
    DOWN = 0b0100,
    LEFT = 0b0010,
    RIGHT = 0b0001,
    NONE = 0b0000
  };

  RigidbodyComponent(const float& speed);
  virtual void update(GameObject& obj, World& world, const float& dt);

  bool is_turning_90_degrees() const;

  inline void set_next_dir(Direction dir) { _next_dir = dir; }
  inline Direction get_prev_dir() const { return _prev_dir; }
  inline Direction get_curr_dir() const { return _curr_dir; }
  inline Direction get_next_dir() const { return _next_dir; }

private:
  float _speed;
  Direction _prev_dir;
  Direction _curr_dir;
  Direction _next_dir;
};
