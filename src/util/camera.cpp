#include "camera.hpp"

#include "core/constants.hpp"

Camera::Camera() : m_pTarget(nullptr), m_position(0, 0) {}

v2 Camera::getPosition() {
  m_position.x = (m_pTarget->x + 32.0f / 2) - SCREEN_WIDTH / 2.0f;
  m_position.y = (m_pTarget->y + 32.0f / 2) - SCREEN_HEIGHT / 2.0f;

  // Keep the camera in bounds.
  if (m_position.x < 0) {
    m_position.x = 0;
  }
  if (m_position.y < 0) {
    m_position.y = 0;
  }
  if (m_position.x > LEVEL_WIDTH - SCREEN_WIDTH) {
    m_position.x = LEVEL_WIDTH - SCREEN_WIDTH;
  }
  if (m_position.y > LEVEL_HEIGHT - SCREEN_HEIGHT) {
    m_position.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
  }

  return m_position;
}
