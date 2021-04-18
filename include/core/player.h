#pragma once
#include <glm/vec2.hpp>
#include <string>
#include <cinder/Color.h>

namespace finalproject {

/** A tank/player with all the relevant information */
class Player {
  
public:
  const size_t kTankDimensions = 15;
  
  /** Enum for direction the tank is currently pointing. Includes: UP, DOWN, LEFT, RIGHT */
  enum Direction {
      UP,
      DOWN,
      LEFT,
      RIGHT,
  };
  
  /** Initializes a new player with a score of 0. Other variables initialized in GameStatus */
  Player();
  
  /** Methods to move character: Left, Right, Up, Down */
  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();
  
  /** Setters and Getters */
  void SetCurrPosition(const glm::vec2& position);
  void SetScore(const size_t& score);
  void SetColor(const ci::Color& color);
  void SetDirection(const Direction& direction);
  ci::Color GetColor() const;
  glm::vec2 GetCurrPosition() const;
  size_t GetScore() const;
  Direction GetDirection() const;

private:
  glm::vec2 curr_position_;
  size_t score_;
  ci::Color color_;
  Direction direction_;
  
  const size_t kMoveStep = 2;
  const std::string kTankImagePath = "";
};

} // namespace finalproject