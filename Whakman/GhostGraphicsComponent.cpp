#include "GhostGraphicsComponent.h"

GhostGraphicsComponent::GhostGraphicsComponent(const std::vector<IImage*>& images) {
  _images = images;
}

void GhostGraphicsComponent::update(GameObject& obj, const World& world, const float& dt) {
  int x = obj.get_int_x();
  int y = obj.get_int_y();
  _images[0]->draw(x, y);
  if (x < 0) {
    _images[0]->draw(x + world.get_world_width(), y);
  }
  else if (x >= world.get_world_width() - world.get_tile_size()) {
    _images[0]->draw(x - world.get_world_width(), y);
  }
  if (y < 0) {
    _images[0]->draw(x, y + world.get_world_height());
  }
  else if (y >= world.get_world_height() - world.get_tile_size()) {
    _images[0]->draw(x, y - world.get_world_height());
  }
}
