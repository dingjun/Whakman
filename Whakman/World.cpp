#include "World.h"
#include "GameManager.h"
#include "ImageManager.h"
#include "TileColliderComponent.h"
#include "TileGraphicsComponent.h"
#include "CoinGraphicsComponent.h"
#include "WhakmanInputComponent.h"
#include "WhakmanGraphicsComponent.h"
#include "GhostInputComponent.h"
#include "GhostGraphicsComponent.h"

World::World() {
  init();
}

World::~World() {
  deinit();
}

void World::init() {
  init_tiles();
  init_coins();
  init_actors();
}

void World::deinit() {
  for (auto tile : _tiles) {
    delete tile;
  }
  _tiles.clear();
  for (auto coin : _coins) {
    delete coin;
  }
  _coins.clear();
  deinit_actors();
}

void World::init_actors() {
  LevelData* level_data = LevelDataManager::get_level_data(GameManager::get_level());
  std::vector<IImage*> ghost_images{ ImageManager::get_image(7), ImageManager::get_image(8) };
  std::vector<IImage*> whakman_images{ ImageManager::get_image(5), ImageManager::get_image(6) };
  for (std::size_t i = 0; i < level_data->ghost_x.size(); ++i)
    _ghosts.push_back(
      new GameObject(level_data->ghost_x[i], level_data->ghost_y[i],
        new GhostInputComponent(level_data->ghost_intelligence[i]),
        new ColliderComponent(static_cast<float>(k_HALF_TILE_SIZE), k_RADIUS_GHOST),
        new RigidbodyComponent(k_SPEED_GHOST),
        new GhostGraphicsComponent(ghost_images)));
  _whakman =
    new GameObject(level_data->whakman_x, level_data->whakman_y,
      new WhakmanInputComponent(),
      new ColliderComponent(static_cast<float>(k_HALF_TILE_SIZE), k_RADIUS_WHAKMAN),
      new RigidbodyComponent(k_SPEED_WHAKMAN),
      new WhakmanGraphicsComponent(whakman_images));
}

void World::deinit_actors() {
  for (auto ghost : _ghosts) {
    delete ghost;
  }
  _ghosts.clear();
  deinit_whakman();
}

void World::update(ISBZLibrary* lib, const float& dt) {
  for (auto tile : _tiles) {
    if (tile != nullptr) {
      tile->update(*this, lib, dt);
    }
  }
  for (auto coin : _coins) {
    if (coin != nullptr) {
      coin->update(*this, lib, dt);
    }
  }
  for (auto ghost : _ghosts) {
    if (ghost != nullptr) {
      ghost->update(*this, lib, dt);
    }
  }
  if (_whakman != nullptr) {
    _whakman->update(*this, lib, dt);

    check_items_with_whakman();
    check_ghosts_with_whakman();

    if (GameManager::get_state() == GameManager::State::LIFE_LOST) {
      deinit_whakman();
    }
  }
}

void World::set_actor_to_next_position(GameObject& actor, const float& new_x, const float& new_y, const bool& is_colliding_another_tile) {
  if (is_colliding_another_tile) {
    set_actor_to_tile_position(actor);
  }
  float offset = abs(new_x - actor.x + new_y - actor.y);
  switch (actor.get_rigidbody_component()->get_next_dir()) {
  case RigidbodyComponent::Direction::UP:
    actor.y -= offset;
    break;
  case RigidbodyComponent::Direction::DOWN:
    actor.y += offset;
    break;
  case RigidbodyComponent::Direction::LEFT:
    actor.x -= offset;
    break;
  case RigidbodyComponent::Direction::RIGHT:
    actor.x += offset;
    break;
  }
}

void World::set_actor_to_tile_position(GameObject& actor) {
  int tile_index = get_current_tile_index(actor);
  actor.x = _tiles[tile_index]->x;
  actor.y = _tiles[tile_index]->y;
}

bool World::is_actor_colliding_with_another_tile(const float& x, const float& y, const float& new_x, const float& new_y) const {
  int x_coord = static_cast<int>(x + k_TILE_SIZE);
  int y_coord = static_cast<int>(y + k_TILE_SIZE);
  int new_x_coord = static_cast<int>(new_x + k_TILE_SIZE);
  int new_y_coord = static_cast<int>(new_y + k_TILE_SIZE);
  return (x_coord / k_TILE_SIZE != new_x_coord / k_TILE_SIZE) || (y_coord / k_TILE_SIZE != new_y_coord / k_TILE_SIZE);
}

bool World::is_actor_direction_valid(const GameObject& actor, const bool& is_checking_next_direction) const {
  int tile_index = get_current_tile_index(actor);
  const TileColliderComponent* tile_collider = static_cast<const TileColliderComponent*>(_tiles[tile_index]->get_collider_component());
  if (tile_collider != nullptr) {
    if (is_checking_next_direction) {
      return tile_collider->is_direction_valid(actor.get_rigidbody_component()->get_next_dir());
    }
    else {
      return tile_collider->is_direction_valid(actor.get_rigidbody_component()->get_curr_dir());
    }  
  }
  return false;
}

int World::get_current_tile_index(const GameObject& actor) const {
  int x = actor.get_int_x();
  int y = actor.get_int_y();
  RigidbodyComponent::Direction dir = actor.get_rigidbody_component()->get_curr_dir();
  if (dir == RigidbodyComponent::Direction::DOWN) {
    y += k_TILE_SIZE;
  }
  else if (dir == RigidbodyComponent::Direction::RIGHT) {
    x += k_TILE_SIZE;
  }
  return get_tile_index_from_world_coordinates(x, y);
}

void World::init_tiles() {
  const unsigned char* tiles = LevelDataManager::get_level_data(GameManager::get_level())->map;
  for (int j = 0; j < LevelDataManager::k_NUMBER_ROWS; ++j) {
    for (int i = 0; i < LevelDataManager::k_NUMBER_COLUMNS; ++i) {
      unsigned char tileType = tiles[get_tile_index_from_tile_coordinates(i, j)];
      float x = static_cast<float>(i * k_TILE_SIZE);
      float y = static_cast<float>(j * k_TILE_SIZE);
      TileColliderComponent* collider = new TileColliderComponent(static_cast<float>(k_HALF_TILE_SIZE), tileType);
      TileGraphicsComponent* graphics = nullptr;
      switch (tileType) {
      case 0:
        graphics = nullptr;
        break;
      case 1:
        graphics = new TileGraphicsComponent(ImageManager::get_image(1), 90.0f);
        break;
      case 2:
        graphics = new TileGraphicsComponent(ImageManager::get_image(1), 270.0f);
        break;
      case 3:
        graphics = new TileGraphicsComponent(ImageManager::get_image(2), 0.0f);
        break;
      case 4:
        graphics = new TileGraphicsComponent(ImageManager::get_image(1), 180.0f);
        break;
      case 5:
        graphics = new TileGraphicsComponent(ImageManager::get_image(4), 0.0f);
        break;
      case 6:
        graphics = new TileGraphicsComponent(ImageManager::get_image(4), 90.0f);
        break;
      case 7:
        graphics = new TileGraphicsComponent(ImageManager::get_image(3), 270.0f);
        break;
      case 8:
        graphics = new TileGraphicsComponent(ImageManager::get_image(1), 0.0f);
        break;
      case 9:
        graphics = new TileGraphicsComponent(ImageManager::get_image(4), 270.0f);
        break;
      case 10:
        graphics = new TileGraphicsComponent(ImageManager::get_image(4), 180.0f);
        break;
      case 11:
        graphics = new TileGraphicsComponent(ImageManager::get_image(3), 90.0f);
        break;
      case 12:
        graphics = new TileGraphicsComponent(ImageManager::get_image(2), 90.0f);
        break;
      case 13:
        graphics = new TileGraphicsComponent(ImageManager::get_image(3), 180.0f);
        break;
      case 14:
        graphics = new TileGraphicsComponent(ImageManager::get_image(3), 0.0f);
        break;
      case 15:
        graphics = new TileGraphicsComponent(ImageManager::get_image(0), 0.0f);
        break;
      }

      if (graphics == nullptr) {
        _tiles.push_back(nullptr);
      }
      else {
        _tiles.push_back(new GameObject(x, y, nullptr, collider, nullptr, graphics));
      }
    }
  }
}

void World::init_coins() {
  const unsigned char* coins = LevelDataManager::get_level_data(GameManager::get_level())->coin;
  std::vector<IImage*> coin_images{ ImageManager::get_image(9) };
  _left_coins = 0;
  for (int i = 0; i < LevelDataManager::k_NUMBER_TILES; ++i) {
    if (coins[i] == 0) {
      _coins.push_back(nullptr);
    }
    else {
      _coins.push_back(
        new GameObject(_tiles[i]->x, _tiles[i]->y,
          nullptr,
          new ColliderComponent(static_cast<float>(k_HALF_TILE_SIZE), k_RADIUS_COIN),
          nullptr,
          new CoinGraphicsComponent(coin_images)));
      ++_left_coins;
    }
  }
}

void World::deinit_whakman() {
  delete _whakman;
  _whakman = nullptr;
}

void World::check_coin_with_whakman(const int& tile_index) {
  GameObject* coin = _coins[tile_index];
  if (coin != nullptr && _whakman->get_collider_component()->is_colliding(*_whakman, *coin)) {
    delete coin;
    _coins[tile_index] = nullptr;
    GameManager::add_points(GameManager::k_POINTS_COIN);
    --_left_coins;
    if (_left_coins == 0) {
      GameManager::set_state(GameManager::State::LEVEL_BEATEN);
    }
  }
}

void World::check_items_with_whakman() {
  int whakman_x = _whakman->get_int_x();
  int whakman_y = _whakman->get_int_y();
  int tile_index = get_tile_index_from_world_coordinates(whakman_x, whakman_y);

  check_coin_with_whakman(tile_index);
  if (whakman_x + k_TILE_SIZE < k_WORLD_WIDTH) {
    check_coin_with_whakman(tile_index + 1);
  }
  if (whakman_y + k_TILE_SIZE < k_WORLD_HEIGHT) {
    check_coin_with_whakman(tile_index + LevelDataManager::k_NUMBER_COLUMNS);
  }
}

void World::check_ghosts_with_whakman() {
  for (auto ghost : _ghosts) {
    if (_whakman->get_collider_component()->is_colliding(*_whakman, *ghost)) {
      GameManager::set_state(GameManager::State::LIFE_LOST);
      break;
    }
  }
}

int World::get_tile_index_from_tile_coordinates(int x, int y) const {
  x = (x + LevelDataManager::k_NUMBER_COLUMNS) % LevelDataManager::k_NUMBER_COLUMNS;
  y = (y + LevelDataManager::k_NUMBER_ROWS) % LevelDataManager::k_NUMBER_ROWS;
  return y * LevelDataManager::k_NUMBER_COLUMNS + x;
}
