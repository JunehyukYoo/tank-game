#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"

namespace finalproject {
/** Represents the current status of the game */
class GameStatus {
public:
  const ci::Color kBorderColor = ci::Color("black");
  const glm::vec2 kTopLeft = glm::vec2(100, 100);
  const glm::vec2 kBottomRight = glm::vec2(600, 600);
  
  /** Initializes the game with the blue and red player. */
  GameStatus();
  
  /**
   * Method to shoot a bullet.
   * @param player The player who shot the bullet.
   */
  void ShootBullet(const Player& player);
  
  /**
   * Advances one frame within the game. Used for bullet trajectory calculation.
   */
  void AdvanceOneFrame();
  
  void CheckContainerContact();
  
  /** Getters and Setters */
  Player GetRedPlayer();
  Player GetBluePlayer();
  
private:
  Player player_red_;
  Player player_blue_;
  std::vector<Bullet> bullets_in_game_;

  const glm::vec2 kRedStart = glm::vec2(105, 105);
  const glm::vec2 kBlueStart = glm::vec2(595, 595);
};
    
}