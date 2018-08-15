#include <Windows.h>

#include "SBZLibraryScope.h"
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmd, int nshow) {
  SBZLibraryScope library_scope;
  ISBZLibrary* lib = library_scope.library();

  Application* application = new Application(lib);
  application->update();
  delete application;

  lib->destroy();

  return 0;
}
