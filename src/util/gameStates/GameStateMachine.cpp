#include "GameStateMachine.hpp"

#include "../../core/game.hpp"
#include "GameState.hpp"

void GameStateMachine::logic() {
  if (!m_gameStates.empty()) {
    m_gameStates.back()->logic(game);
  }
}

void GameStateMachine::render() {
  if (!m_gameStates.empty()) {
    m_gameStates.back()->render(game);
  }
}

void GameStateMachine::pushState(GameState const *pState) {
  m_gameStates.push_back(pState);
  m_gameStates.back()->onEnter(game);
}

void GameStateMachine::changeState(GameState const *pState) {
  if (!m_gameStates.empty()) {
    if (m_gameStates.back()->getStateID() == pState->getStateID()) {
      return;  // do nothing
    }

    if (m_gameStates.back()->onExit(game)) {
      delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }
  // Push back our new state.
  m_gameStates.push_back(pState);

  // Initialise it.
  m_gameStates.back()->onEnter(game);
}

void GameStateMachine::popState() {
  if (!m_gameStates.empty()) {
    if (m_gameStates.back()->onExit(game)) {
      delete m_gameStates.back();
      m_gameStates.pop_back();
    }
  }
}