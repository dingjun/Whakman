#include "ImageManager.h"

std::vector<IImage*> ImageManager::_images;

void ImageManager::init(ISBZLibrary* lib) {
  _images.push_back(lib->load_image("images/wall_cross.png"));
  _images.push_back(lib->load_image("images/wall_end.png"));
  _images.push_back(lib->load_image("images/wall_straight.png"));
  _images.push_back(lib->load_image("images/wall_t.png"));
  _images.push_back(lib->load_image("images/wall_turn.png"));
  _images.push_back(lib->load_image("images/whakman_01.png"));
  _images.push_back(lib->load_image("images/whakman_02.png"));
  _images.push_back(lib->load_image("images/ghost_01.png"));
  _images.push_back(lib->load_image("images/ghost_02.png"));
  _images.push_back(lib->load_image("images/coin.png"));
  _images.push_back(lib->load_image("images/osd_whakman.png"));
}

void ImageManager::deinit() {
  for (auto image : _images) {
    image->destroy();
  }
  _images.clear();
}
