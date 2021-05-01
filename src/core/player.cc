#include <core/player.h>

namespace finalproject {
    
Player::Player() {
  score_ = 0;
}

void Player::MoveLeft() {
  curr_position_.x -= kMoveStep;
  direction_ = LEFT;
}

void Player::MoveRight() {
  curr_position_.x += kMoveStep;
  direction_ = RIGHT;
}

void Player::MoveUp() {
  curr_position_.y -= kMoveStep;
  direction_ = UP;
}

void Player::MoveDown() {
  curr_position_.y += kMoveStep;
  direction_ = DOWN;
}

void Player::SetPosition(const glm::vec2 &position) {
  curr_position_ = position;
}

void Player::SetColor(const cinder::Color &color) {
  color_ = color;
}

void Player::SetDirection(const Player::Direction &direction) {
  direction_ = direction;
}

ci::Color Player::GetColor() const {
  return color_;
}

glm::vec2 Player::GetPosition() const {
  return curr_position_;
}

size_t Player::GetScore() const {
  return score_;
}

Player::Direction Player::GetDirection() const {
  return direction_;
}

bool Player::GetPoweredUpStatus() const {
  return powered_up_;
}

void Player::SetScore(const size_t &score) {
  score_ = score;
}

void Player::SetPoweredUpStatus(const bool& boolean) {
  powered_up_ = boolean;
}

} // namespace finalproject