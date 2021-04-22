#include "core/wall.h"
#include <vector>

namespace finalproject {
    
Wall::Wall(float dimension, glm::vec2 position, size_t health) {
  top_left_ = position;
  bottom_right_ = position + glm::vec2(dimension, dimension);
  health_ = health;
}

Wall::Wall() {
  top_left_ = glm::vec2(0,0);
  bottom_right_ = glm::vec2(0,0);
  health_ = 0;
}

}