#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject(const float& x, const float& y, InputComponent* input, ColliderComponent* collider, RigidbodyComponent* rigidbody, GraphicsComponent* graphics)
  : x(x)
  , y(y)
  , _input(input)
  , _collider(collider)
  , _rigidbody(rigidbody)
  , _graphics(graphics) {
}

GameObject::~GameObject() {
  delete _input;
  delete _collider;
  delete _rigidbody;
  delete _graphics;
}

void GameObject::update(World& world, ISBZLibrary* lib, const float& dt) {
  if (_input != nullptr && GameManager::get_state() == GameManager::State::IN_GAME) {
    _input->update(*this, world, lib, dt);
  }
  if (_collider != nullptr) {
    _collider->update(*this, world, dt);
  }
  if (_rigidbody != nullptr && GameManager::get_state() == GameManager::State::IN_GAME) {
    _rigidbody->update(*this, world, dt);
  }
  if (_graphics != nullptr) {
    _graphics->update(*this, world, dt);
  }
}
