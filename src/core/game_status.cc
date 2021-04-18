#include <core/game_status.h>
#include <core/player.h>
#include "core/bullet.h"

namespace finalproject {

GameStatus::GameStatus() {
  player_red_.SetColor(ci::Color("red"));
  player_red_.SetDirection(Player::RIGHT);
  player_red_.SetCurrPosition(kRedStart);
  player_blue_.SetColor(ci::Color("blue"));
  player_blue_.SetDirection(Player::LEFT);
  player_blue_.SetCurrPosition(kBlueStart);
}

void GameStatus::ShootBullet(Player &player) {
  Bullet bullet(player);
  bullets_in_game_.push_back(bullet);
}

void GameStatus::AdvanceOneFrame() {
  CheckBulletContainerContact();
}

void GameStatus::CheckBulletContainerContact() {
  if (bullets_in_game_.empty()) {
    return;
  }
  size_t count = 0;
  for (Bullet& bullet : bullets_in_game_) {
    glm::vec2 pos = bullet.GetPosition();
    glm::vec2 vel = bullet.GetVelocity();
    float radius = bullet.GetRadius();
    if (pos.x <= kTopLeft.x + radius || 
        pos.x >= kBottomRight.x - radius || 
        pos.y <= kTopLeft.y + radius || 
        pos.y >= kBottomRight.y - radius) {
      bullets_in_game_.erase(bullets_in_game_.begin() + count);
    } else {
      pos += vel;
    }
    count++;
  }
}

bool GameStatus::CanTankMoveInDir(const Player &player, const Player::Direction desired_move_dir) const {
  glm::vec2 pos = player.GetCurrPosition();
  float radius = Player::kTankDimensions;
  float step = Player::kMoveStep;
  if (desired_move_dir == Player::Direction::UP) {
    if (pos.y <= kTopLeft.y + radius + step) {
      return false;
    } else {
      return true;
    }
  } else if (desired_move_dir == Player::Direction::DOWN) {
    if (pos.y >= kBottomRight.y - radius - step) {
      return false;
    } else {
      return true;
    }
  } else if (desired_move_dir == Player::Direction::LEFT) {
    if (pos.x <= kTopLeft.x + radius + step) {
      return false;
    } else {
      return true;
    }
  } else if (desired_move_dir == Player::Direction::RIGHT) {
    if (pos.x >= kBottomRight.x - radius - step) {
      return false;
    } else {
      return true;
    }
  } else {
    throw std::invalid_argument("Invalid direction to move in for CanTankMoveInDir()");
  }
}

Player GameStatus::GetRedPlayer() {
  return player_red_;
}

Player GameStatus::GetBluePlayer() {
  return player_blue_;
}

std::vector<Bullet> GameStatus::GetBulletsInGame() {
  return bullets_in_game_;
}

} // namespace finalproject