#include <core/game_status.h>
#include <core/player.h>

namespace finalproject {

GameStatus::GameStatus() {
  player_red_ =  Player(ci::Color("red"));
  player_blue_ = Player(ci::Color("blue"));
  red_shot_ = false;
  blue_shot_ = false;
}

} // namespace finalproject