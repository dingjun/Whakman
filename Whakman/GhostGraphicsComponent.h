#pragma once

#include "GraphicsComponent.h"

class GhostGraphicsComponent : public GraphicsComponent {
public:
  GhostGraphicsComponent(const std::vector<IImage*>& images);
  virtual void update(GameObject& obj, const World& world, const float& dt) override;
};
