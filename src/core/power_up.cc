#include "core/power_up.h"

namespace finalproject {

PowerUp::PowerUp(const glm::vec2& position) {
  position_ = position;
  radius_ = kDefaultRadius;
}

glm::vec2 PowerUp::GetPosition() const {
  return position_;
}

float PowerUp::GetRadius() const {
  return radius_;
}

}