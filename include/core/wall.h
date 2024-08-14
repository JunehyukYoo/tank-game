#pragma once
#include "bullet.h"

namespace finalproject {
/** Represents square walls with its respective variables */
struct Wall {
    Wall();
    /**
     * Initializes a square wall at a position
     * @param dimension The dimensions of the wall.
     * @param position The top left position of the wall.
     */
    Wall(float dimension, glm::vec2 position, size_t health);

    glm::vec2 top_left_;
    glm::vec2 bottom_right_;
    size_t health_;
};

} // namespace finalproject