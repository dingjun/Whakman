#pragma once

#include <Windows.h>

#include "sbzwhakman.h"

class SBZLibraryScope {
public:
  typedef ISBZLibrary*(*CreateLibraryFunc)();

  SBZLibraryScope();
  ~SBZLibraryScope();

  inline ISBZLibrary* library() const { return _library; }

private:
  HMODULE _dll;
  ISBZLibrary* _library;
};
