#pragma once

#include "GraphicsComponent.h"

class WhakmanGraphicsComponent : public GraphicsComponent {
public:
  WhakmanGraphicsComponent(const std::vector<IImage*>& images);
  virtual void update(GameObject& obj, const World& world, const float& dt) override;

private:
  const float k_ANIMATION_FLIP_TIME = 0.1f;

  float _timer;
  int _frame;
};
