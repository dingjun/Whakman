#include "TileGraphicsComponent.h"

TileGraphicsComponent::TileGraphicsComponent(IImage* image, float rotation)
  :_rotation(rotation) {
  _images.push_back(image);
}

void TileGraphicsComponent::update(GameObject& obj, const World& world, const float& dt) {
  _images[0]->draw(obj.get_int_x(), obj.get_int_y(), _rotation);
}
