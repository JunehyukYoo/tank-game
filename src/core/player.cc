#include <core/player.h>

namespace finalproject {
    
Player::Player() {
  score_ = 0;
}

void Player::MoveLeft() {
  curr_position_.x += -kMoveStep;
  direction_ = LEFT;
}

void Player::MoveRight() {
  curr_position_.x += kMoveStep;
  direction_ = RIGHT;
}

void Player::MoveUp() {
  curr_position_.y += -kMoveStep;
  direction_ = UP;
}

void Player::MoveDown() {
  curr_position_.y += +kMoveStep;
  direction_ = DOWN;
}

void Player::SetCurrPosition(const glm::vec2 &position) {
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

glm::vec2 Player::GetCurrPosition() const {
  return curr_position_;
}

size_t Player::GetScore() const {
  return score_;
}

Player::Direction Player::GetDirection() const {
  return direction_;
}

}