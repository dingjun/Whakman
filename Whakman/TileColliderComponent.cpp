#include "TileColliderComponent.h"

TileColliderComponent::TileColliderComponent(const float& center_offset, const unsigned char& tile_type)
  : ColliderComponent(center_offset, 0.0f)
  , _tile_type(tile_type) {
}
