#include <SDL_main.h>

#include <exception>
#include <iostream>

#include "core/app.hpp"

int main(int argc, char *argv[]) {
  try {
    Application app;
    app.run();
  } catch (std::exception &e) {
    // The only exceptions we should get are from SDL.
    std::cout << e.what() << '\n';
    return 1;
  }
  return 0;
}
