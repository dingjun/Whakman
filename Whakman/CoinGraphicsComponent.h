#pragma once

#include "GraphicsComponent.h"

class CoinGraphicsComponent : public GraphicsComponent {
public:
  CoinGraphicsComponent(const std::vector<IImage*>& images);
  virtual void update(GameObject& obj, const World& world, const float& dt) override;
};
