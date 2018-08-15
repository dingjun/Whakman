#include "CoinGraphicsComponent.h"

CoinGraphicsComponent::CoinGraphicsComponent(const std::vector<IImage*>& images) {
  _images = images;
}

void CoinGraphicsComponent::update(GameObject& obj, const World& world, const float& dt) {
  _images[0]->draw(obj.get_int_x(), obj.get_int_y());
}
