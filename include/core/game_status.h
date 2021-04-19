#pragma once
#include <vector>
#include "player.h"
#include "bullet.h"

namespace finalproject {
/** Represents the current status of the game */
class GameStatus {
public:
  const glm::vec2 kTopLeft = glm::vec2(100, 100);
  const glm::vec2 kBottomRight = glm::vec2(600, 600);
  const glm::vec2 kRedScoreDisplayLoc = glm::vec2(200, 50);
  const glm::vec2 kBlueScoreDisplayLoc = glm::vec2(400, 50);
  const ci::Color kColorPlayerRed = ci::Color("red");
  const ci::Color kColorPlayerBlue = ci::Color("blue");
  
  /** Initializes the game with the blue and red player. */
  GameStatus();
  
  /**
   * Method to shoot a bullet.
   * @param player The player who shot the bullet.
   */
  void ShootBullet(const Player& player);
  
  /** Advances one frame within the game. Used for bullet trajectory calculation. */
  void AdvanceOneFrame();
  
  /** Checks if bullets are coming into contact with the container, deletes bullet if occurs. */
  void CheckBulletContainerContact();
  
  /** Checks if bullets are coming into contact with players, and what to do then. */
  void CheckBulletPlayerContact();
  
  /**
   * Checks if tank can move in the desired direction.
   * @param player The player and relevant information.
   * @param desired_move_dir The direction to move in.
   * @return Whether you can move that way or not.
   */
  bool CanTankMoveInDir(const Player& player, const Player::Direction desired_move_dir) const;
  
  
  /** Getters */
  Player& GetRedPlayer();
  Player& GetBluePlayer();
  std::vector<Bullet> GetBulletsInGame();
  
private:
  Player player_red_;
  Player player_blue_;
  std::vector<Bullet> bullets_in_game_;

  const glm::vec2 kRedStart = glm::vec2(115, 115);
  const glm::vec2 kBlueStart = glm::vec2(585, 585);
};
    
}