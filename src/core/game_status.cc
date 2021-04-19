#include <core/game_status.h>
#include <core/player.h>
#include "core/bullet.h"

namespace finalproject {

GameStatus::GameStatus() {
  player_red_.SetColor(ci::Color("red"));
  player_red_.SetDirection(Player::RIGHT);
  player_red_.SetPosition(kRedStart); //glm::vec2(115, 115)
  player_blue_.SetColor(ci::Color("blue"));
  player_blue_.SetDirection(Player::LEFT);
  player_blue_.SetPosition(kBlueStart); //glm::vec2(585, 585)
}

void GameStatus::ShootBullet(const Player &player) {
  Bullet bullet(player);
  bullets_in_game_.push_back(bullet);
}

void GameStatus::AdvanceOneFrame() {
  CheckBulletPlayerContact();
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

void GameStatus::CheckBulletPlayerContact() {
  if (bullets_in_game_.empty()) {
    return;
  }
  glm::vec2 red_pos = player_red_.GetPosition();
  glm::vec2 blue_pos = player_blue_.GetPosition();
  float player_radius = player_red_.kTankDimensions;
  bool is_contact = false;
  
  for (Bullet& bullet : bullets_in_game_) {
    glm::vec2 bullet_pos = bullet.GetPosition();
    float bullet_radius = bullet.GetRadius();
    ci::Color bullet_color = bullet.GetColor();
    
    if ((std::abs(glm::distance(red_pos, bullet_pos)) <= player_radius + bullet_radius) && bullet_color == player_blue_.GetColor()) {
      player_blue_.SetScore(player_blue_.GetScore() + 1);
      is_contact = true;
      break;
    } else if ((std::abs(glm::distance(blue_pos, bullet_pos)) <= player_radius + bullet_radius) && bullet_color == player_red_.GetColor()) {
      player_red_.SetScore(player_red_.GetScore() + 1);
      is_contact = true;
      break;
    }
  }
  
  if (is_contact) {
    bullets_in_game_.clear();
    player_red_.SetPosition(kRedStart);
    player_blue_.SetPosition(kBlueStart);
  }
}

bool GameStatus::CanTankMoveInDir(const Player &player, const Player::Direction desired_move_dir) const {
  glm::vec2 pos = player.GetPosition();
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