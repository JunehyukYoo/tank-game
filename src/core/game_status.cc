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

void GameStatus::ShootBullet(const Player &player) {
  Bullet bullet(player);
  bullets_in_game_.push_back(bullet);
}

void GameStatus::AdvanceOneFrame() {
  
}

void GameStatus::CheckContainerContact() {
  if (bullets_in_game_.empty()) {
    return;
  }
  for (Bullet& bullet : bullets_in_game_) {
    
  }
}

Player GameStatus::GetRedPlayer() {
  return player_red_;
}

Player GameStatus::GetBluePlayer() {
  return player_blue_;
}

} // namespace finalproject