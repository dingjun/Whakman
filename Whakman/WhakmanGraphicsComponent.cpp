#include "WhakmanGraphicsComponent.h"

WhakmanGraphicsComponent::WhakmanGraphicsComponent(const std::vector<IImage*>& images)
  : _timer(0.0f)
  , _frame(0) {
  _images = images;
}

void WhakmanGraphicsComponent::update(GameObject& obj, const World& world, const float& dt) {
  const RigidbodyComponent* rigidbody = obj.get_rigidbody_component();
  if (rigidbody == nullptr) {
    return;
  }

  if (rigidbody->get_curr_dir() != RigidbodyComponent::Direction::NONE) {
    _timer += dt;
  }
  if (_timer >= k_ANIMATION_FLIP_TIME) {
    _timer = 0.0f;
    _frame = (_frame + 1) % _images.size();
  }

  int x = obj.get_int_x();
  int y = obj.get_int_y();
  float rotation = 0.0f;
  switch (rigidbody->get_prev_dir()) {
  case RigidbodyComponent::Direction::UP:
    rotation = 270.0f;
    break;
  case RigidbodyComponent::Direction::DOWN:
    rotation = 90.0f;
    break;
  case RigidbodyComponent::Direction::LEFT:
    rotation = 180.0f;
    break;
  case RigidbodyComponent::Direction::RIGHT:
    rotation = 0.0f;
    break;
  }
  
  _images[_frame]->draw(x, y, rotation);
  if (x < 0) {
    _images[_frame]->draw(x + world.get_world_width(), y, rotation);
  }
  else if (x >= world.get_world_width() - world.get_tile_size()) {
    _images[_frame]->draw(x - world.get_world_width(), y, rotation);
  }
  if (y < 0) {
    _images[_frame]->draw(x, y + world.get_world_height(), rotation);
  }
  else if (y >= world.get_world_height() - world.get_tile_size()) {
    _images[_frame]->draw(x, y - world.get_world_height(), rotation);
  }
}
