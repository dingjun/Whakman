#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(const float& center_offset, const float& radius)
  : _center_offset(center_offset)
  , _radius(radius){
}

bool ColliderComponent::is_colliding(const GameObject& self, const GameObject& other) const {
  const ColliderComponent* other_collider = other.get_collider_component();
  if (other_collider == nullptr) {
    return false;
  }

  float self_center_x = get_center_x(self);
  float self_center_y = get_center_y(self);
  float other_center_x = other_collider->get_center_x(other);
  float other_center_y = other_collider->get_center_y(other);
  float manhattan_distance = abs(self_center_x - other_center_x) + abs(self_center_y - other_center_y);
  return manhattan_distance < this->get_radius() + other_collider->get_radius();
}

inline float ColliderComponent::get_center_x(const GameObject& obj) const { return obj.x + _center_offset; }
inline float ColliderComponent::get_center_y(const GameObject& obj) const { return obj.y + _center_offset; }
