#pragma once
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
  
  /** Getters and setters */
  glm::vec2 GetPosition();
  glm::vec2 GetVelocity();
  ci::Color GetColor() const;
  float GetRadius() const;
  
  
private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float radius_;
  
  constexpr const static float kDefaultLaunchSpeed = 10;
  constexpr const static float kDefaultRadius = 5;
};
    
} // namespace finalproject