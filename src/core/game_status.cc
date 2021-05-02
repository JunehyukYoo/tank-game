#include <core/game_status.h>
#include <core/player.h>
#include "core/bullet.h"
#include "core/map.h"
#include <cmath>

#define PI 3.14159265

namespace finalproject {

GameStatus::GameStatus() {
  player_red_.SetColor(kColorPlayerRed);
  player_red_.SetDirection(Player::RIGHT);
  player_red_.SetPosition(kRedStart); 
  player_blue_.SetColor(kColorPlayerBlue);
  player_blue_.SetDirection(Player::LEFT);
  player_blue_.SetPosition(kBlueStart);
}

void GameStatus::ShootBullet(const Player &player) {
  Bullet bullet(player);
  bullets_in_game_.push_back(bullet);
}

void GameStatus::ShootPowerUpBullet(const Player &player) {
  ShootBullet(player);
  Bullet bullet_angled_one(player);
  Bullet bullet_angled_two(player);
  glm::vec2 angled_vel_one = bullet_angled_one.GetVelocity();
  glm::vec2 angled_vel_two = bullet_angled_two.GetVelocity();
  ChangeAngleOfBullet(PI/6, angled_vel_one);
  ChangeAngleOfBullet(-PI/6, angled_vel_two);
  bullet_angled_one.SetVelocity(angled_vel_one);
  bullet_angled_two.SetVelocity(angled_vel_two);
  bullets_in_game_.push_back(bullet_angled_one);
  bullets_in_game_.push_back(bullet_angled_two);
}

void GameStatus::ChangeAngleOfBullet(const float &angle, glm::vec2 &original_vector) {
  float x = original_vector.x;
  float y = original_vector.y;
  auto magnitude = sqrt(pow(x,2) + pow(y,2));
  float altered_angle = atan(y/x) + angle;
  if (x < 0) {
    original_vector = glm::vec2(-1 * magnitude * cos(altered_angle), magnitude * sin(altered_angle));
  } else {
    original_vector = glm::vec2(magnitude * cos(altered_angle), magnitude * sin(altered_angle)); 
  }
}

void GameStatus::AdvanceOneFrame() {
  CheckBulletWallContact();
  CheckBulletPlayerContact();
  CheckPlayerPowerUpContact();
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
      bullet.SetPosition(pos + vel);
    }
    count++;
  }
}

void GameStatus::CheckBulletWallContact() {
  if (bullets_in_game_.empty() || map_.GetMapOfWallBooleans().empty()) {
    return;
  }

  size_t count = 0;
  std::vector<size_t> to_remove;
  for (Bullet& bullet : bullets_in_game_) {
    glm::vec2 bullet_pos = bullet.GetPosition();
    std::pair<bool, std::pair<size_t, size_t>> result = map_.ContainsWallAtPoint(bullet_pos);
    if (result.first) {
      size_t row = result.second.first;
      size_t col = result.second.second;
      to_remove.push_back(count);
      Wall& curr_wall = map_.GetWalls()[row][col];
      if (curr_wall.health_ == 1) {
        std::vector<std::vector<bool>>& bool_map = map_.GetMapOfWallBooleans();
        bool_map[row][col] = false;
        curr_wall.top_left_ = glm::vec2(0,0);
        curr_wall.bottom_right_ = glm::vec2(0, 0);
        curr_wall.health_ = 0;
      } else {
        curr_wall.health_--;
      }
    }
    count++;
  }
  
  if (!to_remove.empty()) {
    for (size_t i = to_remove.size(); i --> 0;) {
      bullets_in_game_.erase(bullets_in_game_.begin() + to_remove.at(i));
    }
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
    player_red_.SetPoweredUpStatus(false);
    player_blue_.SetPosition(kBlueStart);
    player_blue_.SetPoweredUpStatus(false);
    map_.FillMapWithPowerUps(kNumPowerUps);
  }
}

void GameStatus::CheckPlayerPowerUpContact() {
  std::vector<PowerUp>& power_ups = map_.GetPowerUps();
  if (power_ups.empty()) {
    return;
  }
  glm::vec2 red_pos = player_red_.GetPosition();
  glm::vec2 blue_pos = player_blue_.GetPosition();
  float player_radius = Player::kTankDimensions;
  for (size_t i = power_ups.size(); i --> 0;) {
    PowerUp power_up = power_ups[i];
    if (glm::distance(power_up.GetPosition(), red_pos) <= player_radius + power_up.GetRadius()) {
      player_red_.SetPoweredUpStatus(true);
      power_ups.erase(power_ups.begin() + i);
      
    } else if (glm::distance(power_up.GetPosition(), blue_pos) <= player_radius + power_up.GetRadius()) {
      player_blue_.SetPoweredUpStatus(true);
      power_ups.erase(power_ups.begin() + i);
    }
  }
}

bool GameStatus::CanTankMoveInDir(const Player &player, const Player::Direction desired_move_dir) const {
  glm::vec2 this_pos = player.GetPosition();
  Player other;
  float radius = Player::kTankDimensions;
  float step = Player::kMoveStep;
  if (player.GetColor() == kColorPlayerRed) {
    other = player_blue_;
  } else {
    other = player_red_;
  }
  glm::vec2 other_pos = other.GetPosition();
  
  if (desired_move_dir == Player::Direction::UP) {
    //Checking for north container collision
    if (this_pos.y <= kTopLeft.y + radius + step) {
      return false;
    }
    //Checking player/player collision if trying to move up
    if (std::abs(glm::distance(this_pos.x, other_pos.x)) < 2 * radius) {
      if (other_pos.y <= this_pos.y - radius && std::abs(glm::distance(this_pos.y, other_pos.y)) < step + 2 * radius) {
        return false;
      }
    }
    //Checking for player wall collision if trying to move up
    if (map_.ContainsWallAtPoint(this_pos - glm::vec2(0, radius + step/2)).first) {
      return false;
    }
  } else if (desired_move_dir == Player::Direction::DOWN) {
    //Checking for south container collision
    if (this_pos.y > kBottomRight.y - radius - step) {
      return false;
    }
    //Checking player/player collision if trying to move down
    if (std::abs(glm::distance(this_pos.x, other_pos.x)) < 2 * radius) {
      if (other_pos.y >= this_pos.y + radius && std::abs(glm::distance(this_pos.y, other_pos.y)) < step + 2 * radius) {
        return false;
      }
    }
    //Checking for player wall collision if trying to move down
    if (map_.ContainsWallAtPoint(this_pos + glm::vec2(0, radius + step/2)).first) {
      return false;
    }
  } else if (desired_move_dir == Player::Direction::LEFT) {
    //Checking for east container collision
    if (this_pos.x < kTopLeft.x + radius + step) {
      return false;
    }
    //Checking player/player collision if trying to move left
    if (std::abs(glm::distance(this_pos.y, other_pos.y)) < 2 * radius) {
      if (other_pos.x <= this_pos.x - radius && std::abs(glm::distance(this_pos.x, other_pos.x)) < step + 2 * radius) {
        return false;
      }
    }
    //Checking for player wall collision if trying to move left
    if (map_.ContainsWallAtPoint(this_pos - glm::vec2(radius + step/2,0)).first) {
      return false;
    }
  } else if (desired_move_dir == Player::Direction::RIGHT) {
    //Checking for west container collision
    if (this_pos.x > kBottomRight.x - radius - step) {
      return false;
    }
    //Checking player/player collision if trying to move right
    if (std::abs(glm::distance(this_pos.y, other_pos.y)) < 2 * radius) {
      if (other_pos.x >= this_pos.x + radius && std::abs(glm::distance(this_pos.x, other_pos.x)) < step + 2 * radius) {
        return false;
      }
    }
    //Checking for player wall collision if trying to move right
    if (map_.ContainsWallAtPoint(this_pos + glm::vec2(radius + step/2,0)).first) {
      return false;
    }
  }
  return true;
}

Player& GameStatus::GetRedPlayer() {
  return player_red_;
}

Player& GameStatus::GetBluePlayer() {
  return player_blue_;
}

std::vector<Bullet> GameStatus::GetBulletsInGame() {
  return bullets_in_game_;
}

Map& GameStatus::GetMap() {
  return map_;
}
} // namespace finalproject