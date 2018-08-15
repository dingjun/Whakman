#pragma once

#include <vector>

#include "GameObject.h"
#include "sbzwhakman.h"

class GameObject;

class GraphicsComponent {
public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject& obj, const World& world, const float& dt) = 0;

protected:
  std::vector<IImage*> _images;
};
