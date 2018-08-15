#pragma once

#include "GraphicsComponent.h"

class TileGraphicsComponent : public GraphicsComponent {
public:
  TileGraphicsComponent(IImage* image, float rotation);
  virtual void update(GameObject& obj, const World& world, const float& dt) override;

private:
  float _rotation;
};
