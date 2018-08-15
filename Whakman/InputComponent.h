#pragma once

#include "GameObject.h"
#include "World.h"
#include "sbzwhakman.h"

class GameObject;
class World;

class InputComponent {
public:
  virtual ~InputComponent() {}
  virtual void update(GameObject& obj, World& world, ISBZLibrary* lib, const float& dt) = 0;
};
