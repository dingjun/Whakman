#pragma once

#include "InputComponent.h"

class WhakmanInputComponent : public InputComponent {
public:
  virtual void update(GameObject& obj, World& world, ISBZLibrary* lib, const float& dt) override;
};
