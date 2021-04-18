#include <core/player.h>

namespace finalproject {
    
Player::Player() {}

Player::Player(ci::Color color) {
  color_ = color;
  score_ = 0;
  if (color == kRed) {
    curr_position_ = kRedStart;
    direction_ = RIGHT;
  } else if (color == kBlue) {
    curr_position_ = kBlueStart;
    direction_ = LEFT;
  } else {
    throw std::invalid_argument("Illegal color");
  }
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

Player::Player(const Player &source) {
  curr_position_ = source.curr_position_;
  score_ = source.score_;
  color_ = source.color_;
  direction_ = source.direction_;
}

Player::Player(Player &&source) noexcept {
  curr_position_ = source.curr_position_;
  score_ = source.score_;
  color_ = source.color_;
  direction_ = source.direction_;
  source.curr_position_ = glm::vec2(0, 0);
  source.score_ = 0;
  source.color_ = nullptr;
  direction_ = UP;
}

Player &Player::operator=(const Player &source) {
  curr_position_ = source.curr_position_;
  score_ = source.score_;
  color_ = source.color_;
  return *this;
}

Player &Player::operator=(Player &&source) noexcept {
  curr_position_ = source.curr_position_;
  score_ = source.score_;
  color_ = source.color_;
  source.curr_position_ = glm::vec2(0, 0);
  source.score_ = 0;
  source.color_ = nullptr;
  return *this;
}

Player::~Player() {
  curr_position_ = glm::vec2(0, 0);
  score_ = 0;
  color_ = ci::Color();
}

}