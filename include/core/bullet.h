#pragma once
#include <glm/vec2.hpp>
#include "core/player.h"

namespace finalproject {

/** Bullet shot out by tanks */
class Bullet {

public:
  /** Default constructor for bullet vector initialization */
  Bullet();
  
  /**
   * Constructor to create new bullet based off player who shot the bullet.
   * @param player The player who shot the bullet.
   */
  Bullet(const Player& player);
  
  /**
   * Calculates the velocity of a new bullet from the direction the player is facing.
   * @param direction The direction the player is facing.
   */
  void CalculateVelocityFromDirection(Player::Direction direction);
  
private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  size_t radius_;
  
  const float kDefaultLaunchSpeed = 10;
  const float kDefaultRadius = 5;
};
    
} // namespace finalproject