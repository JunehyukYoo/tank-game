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

void Player::SetScore(const size_t &score) {
  score_ = score;
}

void Player::SetColor(const cinder::Color &color) {
  color_ = color;
}

void Player::SetDirection(const Player::Direction &direction) {
  direction_ = direction;
}

}