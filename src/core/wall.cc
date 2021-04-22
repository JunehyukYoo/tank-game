#include "core/wall.h"
#include <vector>

namespace finalproject {
    
Wall::Wall(float dimension, glm::vec2 position) {
  top_left_ = position;
  bottom_right_ = position + glm::vec2(dimension, dimension);
}

}