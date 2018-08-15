#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

class TileColliderComponent : public ColliderComponent {
public:
  TileColliderComponent(const float& center_offset, const unsigned char& tile_type);

  inline bool is_direction_valid(const RigidbodyComponent::Direction& dir) const { return (static_cast<unsigned char>(dir) & _tile_type) > 0; }
  
private:
  unsigned char _tile_type;
};
