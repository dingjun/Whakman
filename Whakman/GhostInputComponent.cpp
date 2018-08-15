#include <random>
#include <queue>
#include <functional>

#include "GhostInputComponent.h"

GhostInputComponent::GhostInputComponent(float intelligence)
  : _intelligence(intelligence)
  , _timer(0.0f)
  , _combo_dir(RigidbodyComponent::Direction::NONE) {
  _graph = new Graph();
}

GhostInputComponent::~GhostInputComponent() {
  delete _graph;
}

void GhostInputComponent::update(GameObject& obj, World& world, ISBZLibrary* lib, const float& dt) {
  RigidbodyComponent* rigidbody = obj.get_rigidbody_component();
  if (rigidbody == nullptr) {
    return;
  }
  
  _timer += dt;
  if (_combo_dir != RigidbodyComponent::Direction::NONE) {
    rigidbody->set_next_dir(_combo_dir);
    _combo_dir = RigidbodyComponent::Direction::NONE;
    return;
  }
  if (_timer < k_AI_INPUT_TIME) {
    return;
  }
  _timer = 0.0f;

  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  if (distribution(generator) < _intelligence ) {
    const GameObject& whakman_obj = world.get_whakman();
    int ghost = world.get_current_tile_index(obj);
    int whakman = world.get_current_tile_index(whakman_obj);

    if (ghost == whakman) {
      set_next_direction_same_tile(rigidbody, obj, whakman_obj, ghost, world.get_tile_size());
    }
    else {
      set_next_direction(rigidbody, obj, ghost, whakman);
    }
    if (rigidbody->is_turning_90_degrees()) {
      set_combo_direction(rigidbody, obj, ghost, world.get_tile_size());
    }
  }
  else {
    set_random_direction(rigidbody);
  }
}

void GhostInputComponent::set_next_direction_same_tile(RigidbodyComponent* rigidbody, const GameObject& ghost_obj, const GameObject& whakman_obj, const int& tile_index, const int& tile_size) {
  RigidbodyComponent::Direction dir = RigidbodyComponent::Direction::NONE;
  if (ghost_obj.x == whakman_obj.x || ghost_obj.y == whakman_obj.y) {
    if (ghost_obj.x < whakman_obj.x) {
      dir = RigidbodyComponent::Direction::RIGHT;
    }
    else if (ghost_obj.x > whakman_obj.x) {
      dir = RigidbodyComponent::Direction::LEFT;
    }
    else if (ghost_obj.y < whakman_obj.y) {
      dir = RigidbodyComponent::Direction::DOWN;
    }
    else if (ghost_obj.y > whakman_obj.y) {
      dir = RigidbodyComponent::Direction::UP;
    }
  }
  else {
    int tile_x = tile_index % LevelDataManager::k_NUMBER_COLUMNS * tile_size;
    int tile_y = tile_index / LevelDataManager::k_NUMBER_COLUMNS * tile_size;
    if (tile_x < whakman_obj.x) {
      dir = RigidbodyComponent::Direction::RIGHT;
    }
    else if (tile_x > whakman_obj.x) {
      dir = RigidbodyComponent::Direction::LEFT;
    }
    else if (tile_y < whakman_obj.y) {
      dir = RigidbodyComponent::Direction::DOWN;
    }
    else if (tile_y > whakman_obj.y) {
      dir = RigidbodyComponent::Direction::UP;
    }
  }
  rigidbody->set_next_dir(dir);
}

void GhostInputComponent::set_next_direction(RigidbodyComponent* rigidbody, const GameObject& ghost_obj, const int& ghost, const int& whakman) {
  RigidbodyComponent::Direction dir = RigidbodyComponent::Direction::NONE;
  
  int next_tile = a_star_search(ghost, whakman);

  int x_distance = get_x_distance(ghost, next_tile);
  int y_distance = get_y_distance(ghost, next_tile);
  if (x_distance == 1) {
    if (ghost < next_tile) {
      dir = RigidbodyComponent::Direction::RIGHT;
    }
    else {
      dir = RigidbodyComponent::Direction::LEFT;
    }
  }
  else if (x_distance > 1) {
    if (ghost < next_tile) {
      dir = RigidbodyComponent::Direction::LEFT;
    }
    else {
      dir = RigidbodyComponent::Direction::RIGHT;
    }
  }
  else if (y_distance == 1) {
    if (ghost < next_tile) {
      dir = RigidbodyComponent::Direction::DOWN;
    }
    else {
      dir = RigidbodyComponent::Direction::UP;
    }
  }
  else if (y_distance > 1) {
    if (ghost < next_tile) {
      dir = RigidbodyComponent::Direction::UP;
    }
    else {
      dir = RigidbodyComponent::Direction::DOWN;
    }
  }
  rigidbody->set_next_dir(dir);
}

void GhostInputComponent::set_combo_direction(RigidbodyComponent* rigidbody, const GameObject& ghost_obj, const int& tile_index, const int& tile_size) {
  int tile_x = tile_index % LevelDataManager::k_NUMBER_COLUMNS * tile_size;
  int tile_y = tile_index / LevelDataManager::k_NUMBER_COLUMNS * tile_size;
  if (tile_x < ghost_obj.x && rigidbody->get_curr_dir() == RigidbodyComponent::Direction::RIGHT) {
    _combo_dir = rigidbody->get_next_dir();
    rigidbody->set_next_dir(RigidbodyComponent::Direction::LEFT);
  }
  else if (tile_x > ghost_obj.x && rigidbody->get_curr_dir() == RigidbodyComponent::Direction::LEFT) {
    _combo_dir = rigidbody->get_next_dir();
    rigidbody->set_next_dir(RigidbodyComponent::Direction::RIGHT);
  }
  else if (tile_y < ghost_obj.y && rigidbody->get_curr_dir() == RigidbodyComponent::Direction::DOWN) {
    _combo_dir = rigidbody->get_next_dir();
    rigidbody->set_next_dir(RigidbodyComponent::Direction::UP);
  }
  else if (tile_y > ghost_obj.y && rigidbody->get_curr_dir() == RigidbodyComponent::Direction::UP) {
    _combo_dir = rigidbody->get_next_dir();
    rigidbody->set_next_dir(RigidbodyComponent::Direction::DOWN);
  }
}

void GhostInputComponent::set_random_direction(RigidbodyComponent* rigidbody) const {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> distribution(0, 3);
  switch (distribution(generator)) {
  case 0:
    rigidbody->set_next_dir(RigidbodyComponent::Direction::UP);
    break;
  case 1:
    rigidbody->set_next_dir(RigidbodyComponent::Direction::DOWN);
    break;
  case 2:
    rigidbody->set_next_dir(RigidbodyComponent::Direction::LEFT);
    break;
  case 3:
    rigidbody->set_next_dir(RigidbodyComponent::Direction::RIGHT);
    break;
  }
}

int GhostInputComponent::a_star_search(const int& self, const int& whakman) const {
  typedef std::pair<int, int> Element;
  std::priority_queue<Element, std::vector<Element>, std::greater<Element>> elements;
  elements.emplace(0, self);

  std::unordered_map<int, int> parent;
  std::unordered_map<int, int> cost;
  parent[self] = self;
  cost[self] = 0;

  while (elements.empty() == false) {
    int current = elements.top().second;
    elements.pop();
    if (current == whakman) {
      break;
    }

    for (auto next : _graph->get_neighbors(current)) {
      int new_cost = cost[current] + 1;
      if (cost.find(next) == cost.end() || new_cost < cost[next]) {
        cost[next] = new_cost;
        elements.emplace(new_cost + get_manhattan_distance(current, next), next);
        parent[next] = current;
      }
    }
  }

  int path_node = whakman;
  while (parent[path_node] != self) {
    path_node = parent[path_node];
  }
  return path_node;
}
