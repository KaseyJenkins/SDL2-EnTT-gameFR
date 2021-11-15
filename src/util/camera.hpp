#ifndef NEWGAME_CAMERA_HPP
#define NEWGAME_CAMERA_HPP

#include "util/cute_math2d.h"

class Camera {
 public:
  static Camera &Instance() {
    static Camera s_pInstance;
    return s_pInstance;
  }

  Camera(const Camera &) = delete;
  Camera &operator=(const Camera &) = delete;

  void setTarget(v2 *target) { m_pTarget = target; }
  v2 &setPosition() { return m_position; }

  [[nodiscard]] v2 getPosition();

 private:
  Camera();
  ~Camera() = default;

  // The camera's target.
  v2 *m_pTarget;

  // The camera's position.
  v2 m_position;
};

#endif  // NEWGAME_CAMERA_HPP
