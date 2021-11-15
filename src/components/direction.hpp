#ifndef NEWGAMEIMPROVED_DIRECTION_HPP
#define NEWGAMEIMPROVED_DIRECTION_HPP


#include <cstdint>

enum class Dir : uint8_t {
    RIGHT,
    LEFT
};


struct Direction {
    Dir dir;
};


#endif //NEWGAMEIMPROVED_DIRECTION_HPP
