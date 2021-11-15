#ifndef NEWGAMEIMPROVED_STATE_HPP
#define NEWGAMEIMPROVED_STATE_HPP

#include <cstdint>

enum class plState : uint8_t {
    IDLE,
    RUN,
    JUMP,
    FALL
};


struct State {
    plState state;
};


#endif //NEWGAMEIMPROVED_STATE_HPP
