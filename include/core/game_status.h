#pragma once
#include <glm/vec2.hpp>
#include "player.h"

namespace finalproject {
/** Represents the current status of the game */
class GameStatus {
public:
  const ci::Color kBorderColor = ci::Color("black");
  const glm::vec2 kTopLeft = glm::vec2(100, 100);
  const glm::vec2 kBottomRight = glm::vec2(600, 600);
  
  /** Initializes the game with the blue and red player. */
  GameStatus();
  
  
  
private:
  Player player_red_;
  Player player_blue_;
  bool red_shot_;
  bool blue_shot_;

  const glm::vec2 kRedStart = glm::vec2(105, 105);
  const glm::vec2 kBlueStart = glm::vec2(595, 595);
};
    
}