#ifndef NEWGAMEIMPROVED_DT_HPP
#define NEWGAMEIMPROVED_DT_HPP

inline float calc_dt() {
  static int first = 1;
  static double inv_freq;
  static uint64_t prev;

  uint64_t now = SDL_GetPerformanceCounter();

  if (first) {
    first = 0;
    prev = now;
    inv_freq = 1.0 / static_cast<double>(SDL_GetPerformanceFrequency());
  }

  auto dt = static_cast<float>((static_cast<double>((now - prev)) * inv_freq));

  if (dt > 0.05f) {
    dt = 0.05f;
  }

  prev = now;
  return dt;
}

inline float deltaTimeTicks() {
  static uint32_t mTicksCount;
  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }

  mTicksCount = SDL_GetTicks();

  return deltaTime;
}

#endif  // NEWGAMEIMPROVED_DT_HPP
