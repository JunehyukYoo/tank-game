#include <core/bullet.h>

namespace finalproject {
    
Bullet::Bullet() {}

Bullet::Bullet(const Player& player) {
  position_ = player.GetCurrPosition();
  color_ = player.GetColor();
  radius_ = kDefaultRadius;
  Player::Direction direction = player.GetDirection();
  CalculateVelocityFromDirection(direction);
}

void Bullet::CalculateVelocityFromDirection(Player::Direction direction) {
  if (direction == Player::Direction::UP) {
    velocity_ = glm::vec2(0, -1 * kDefaultLaunchSpeed);
  } else if (direction == Player::Direction::DOWN) {
    velocity_ = glm::vec2(0, kDefaultLaunchSpeed);
  } else if (direction == Player::Direction::LEFT) {
    velocity_ = glm::vec2(-1 * kDefaultLaunchSpeed, 0);
  } else if (direction == Player::Direction::RIGHT) {
    velocity_ = glm::vec2(kDefaultLaunchSpeed, 0);
  } else {
    throw std::invalid_argument("Invalid direction for calculating bullet velocity");
  }
}

} // namespace finalproject