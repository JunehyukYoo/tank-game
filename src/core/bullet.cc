#include <core/bullet.h>

namespace finalproject {
    
Bullet::Bullet() {}

Bullet::Bullet(const Player& player) {
  position_ = player.GetPosition();
  color_ = player.GetColor();
  radius_ = kDefaultRadius;
  Player::Direction direction = player.GetDirection();
  velocity_ = CalculateVelocityFromDirection(direction);
}

glm::vec2 Bullet::CalculateVelocityFromDirection(Player::Direction direction) {
  if (direction == Player::Direction::UP) {
    return glm::vec2(0, -1 * kDefaultLaunchSpeed);
  } else if (direction == Player::Direction::DOWN) {
    return glm::vec2(0, kDefaultLaunchSpeed);
  } else if (direction == Player::Direction::LEFT) {
    return glm::vec2(-1 * kDefaultLaunchSpeed, 0);
  } else if (direction == Player::Direction::RIGHT) {
    return glm::vec2(kDefaultLaunchSpeed, 0);
  } else {
    throw std::invalid_argument("Invalid direction for calculating bullet velocity");
  }
}

glm::vec2 Bullet::GetPosition() {
  return position_;
}

glm::vec2 Bullet::GetVelocity() {
  return velocity_;
}

ci::Color Bullet::GetColor() const {
  return color_;
}

float Bullet::GetRadius() const {
  return radius_;
}

void Bullet::SetPosition(const glm::vec2 &new_pos) {
  position_ = new_pos;
}

void Bullet::SetVelocity(const glm::vec2 &new_vel) {
  velocity_ = new_vel;
}

} // namespace finalproject