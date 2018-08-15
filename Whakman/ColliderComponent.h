#pragma once

#include "GameObject.h"
#include "World.h"

class GameObject;
class World;

class ColliderComponent {
public:
  ColliderComponent(const float& center_offset, const float& radius);
  virtual ~ColliderComponent() {}
  virtual void update(GameObject& obj, World& world, const float& dt) {}
  
  virtual bool is_colliding(const GameObject& self, const GameObject& other) const;

  float get_center_x(const GameObject& obj) const;
  float get_center_y(const GameObject& obj) const;

  inline float get_radius() const { return _radius; }

protected:
  float _center_offset;
  float _radius;
};
