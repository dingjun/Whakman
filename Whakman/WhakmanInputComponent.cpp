#include "WhakmanInputComponent.h"

void WhakmanInputComponent::update(GameObject& obj, World& world, ISBZLibrary* lib, const float& dt) {
  RigidbodyComponent* rigidbody = obj.get_rigidbody_component();
  if (rigidbody == nullptr) {
    return;
  }

  int keys[8];
  int nr_pressed = lib->pressed_keys(keys, 8);
  for (int i = 0; i < nr_pressed; ++i) {
    switch (keys[i]) {
    case ISBZLibrary::KC_UP:
    case 'w':
      rigidbody->set_next_dir(RigidbodyComponent::Direction::UP);
      break;
    case ISBZLibrary::KC_DOWN:
    case 's':
      rigidbody->set_next_dir(RigidbodyComponent::Direction::DOWN);
      break;
    case ISBZLibrary::KC_LEFT:
    case 'a':
      rigidbody->set_next_dir(RigidbodyComponent::Direction::LEFT);
      break;
    case ISBZLibrary::KC_RIGHT:
    case 'd':
      rigidbody->set_next_dir(RigidbodyComponent::Direction::RIGHT);
      break;
    }
  }
}
