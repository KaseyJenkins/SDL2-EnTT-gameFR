#ifndef NEWGAME_SDL_CHECK_HPP
#define NEWGAME_SDL_CHECK_HPP

#include <SDL_error.h>

#include <stdexcept>

namespace SDL {

[[noreturn]] inline void raise() {
  const char *error = SDL_GetError();
  throw std::runtime_error{error};
}

template <typename Ptr>
[[nodiscard]] Ptr *check(Ptr *ptr) {
  if (ptr == nullptr) raise();
  return ptr;
}

inline int check(const int code) {
  if (code < 0) raise();
  return code;
}

}  // namespace SDL

#ifdef DISABLE_SDL_ERROR_CHECK
#define SDL_CHECK(EXPR) EXPR
#else
#define SDL_CHECK(EXPR) ::SDL::check(EXPR)
#endif

#endif  // NEWGAME_SDL_CHECK_HPP
