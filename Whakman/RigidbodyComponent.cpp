#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(const float& speed)
  : _speed(speed)
  , _prev_dir(Direction::RIGHT)
  , _curr_dir(Direction::NONE)
  , _next_dir(Direction::NONE) {
}

void RigidbodyComponent::update(GameObject& obj, World& world, const float& dt) {
  int dx = 0;
  int dy = 0;
  switch (_curr_dir) {
  case Direction::UP:
    dy = -1;
    break;
  case Direction::DOWN:
    dy = 1;
    break;
  case Direction::LEFT:
    dx = -1;
    break;
  case Direction::RIGHT:
    dx = 1;
    break;
  }
  float new_x = obj.x + _speed * dx * dt;
  float new_y = obj.y + _speed * dy * dt;
  bool is_turning = is_turning_90_degrees();
  bool is_colliding_another_tile = world.is_actor_colliding_with_another_tile(obj.x, obj.y, new_x, new_y);

  float pre_x;
  float pre_y;

  if ((!is_turning && _curr_dir != _next_dir || is_turning && is_colliding_another_tile)
    && world.is_actor_direction_valid(obj, true) == true) {
    world.set_actor_to_next_position(obj, new_x, new_y, is_colliding_another_tile);
    _curr_dir = _next_dir;
  }
  else if (is_colliding_another_tile && world.is_actor_direction_valid(obj, false) == false) {
    world.set_actor_to_tile_position(obj);
    _curr_dir = Direction::NONE;
  }
  else {
    pre_x = obj.x;
    pre_y = obj.y;
    obj.x = new_x;
    obj.y = new_y;
  }

  if (obj.x < 0) {
    obj.x += world.get_world_width();
  }
  else if (obj.x >= world.get_world_width()) {
    obj.x -= world.get_world_width();
  }
  if (obj.y < 0) {
    obj.y += world.get_world_height();
  }
  else if (obj.y >= world.get_world_height()) {
    obj.y -= world.get_world_height();
  }

  if (_curr_dir != Direction::NONE) {
    _prev_dir = _curr_dir;
  }
}

bool RigidbodyComponent::is_turning_90_degrees() const {
  unsigned char sum = static_cast<unsigned char>(_curr_dir) + static_cast<unsigned char>(_next_dir);
  return sum == 0b1010 || sum == 0b1001 || sum == 0b0110 || sum == 0b0101;
}
