#pragma once

#include <vector>

#include "sbzwhakman.h"

class ImageManager {
public:
  static void init(ISBZLibrary* lib);
  static void deinit();

  inline static IImage* get_image(const int& index) { return _images[index]; }

private:
  static std::vector<IImage*> _images;
};
