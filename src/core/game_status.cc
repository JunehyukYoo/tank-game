#include <core/game_status.h>
#include <core/player.h>

namespace finalproject {

GameStatus::GameStatus() {
  player_red_.SetColor(ci::Color("red"));
  player_red_.SetDirection(Player::RIGHT);
  player_red_.SetCurrPosition(kRedStart);
  player_blue_.SetColor(ci::Color("blue"));
  player_blue_.SetDirection(Player::LEFT);
  player_blue_.SetCurrPosition(kBlueStart);
  red_shot_ = false;
  blue_shot_ = false;
}

} // namespace finalproject