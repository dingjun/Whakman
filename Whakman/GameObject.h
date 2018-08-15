#pragma once

#include "InputComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "GraphicsComponent.h"
#include "World.h"

class InputComponent;
class ColliderComponent;
class RigidbodyComponent;
class GraphicsComponent;
class World;

class GameObject {
public:
  float x;
  float y;

  GameObject(const float& x, const float& y, InputComponent* input, ColliderComponent* collider, RigidbodyComponent* rigidbody, GraphicsComponent* graphics);
  ~GameObject();

  void update(World& world, ISBZLibrary* lib, const float& dt);

  inline int get_int_x() const { return static_cast<int>(x); }
  inline int get_int_y() const { return static_cast<int>(y); }
  inline const ColliderComponent* get_collider_component() const { return _collider; }
  inline RigidbodyComponent* get_rigidbody_component() const { return _rigidbody; }

private:
  InputComponent* _input;
  ColliderComponent* _collider;
  RigidbodyComponent* _rigidbody;
  GraphicsComponent* _graphics;
};
