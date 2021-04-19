#pragma once
#include <string>
#include <cinder/Color.h>

namespace finalproject {

/** A tank/player with all the relevant information */
class Player {
  
public:
  constexpr static const float kTankDimensions = 10;
  constexpr static const float kMuzzleWidth = 8;
  constexpr static const float kMuzzleLength = 16;
  constexpr static const float kMoveStep = 5;
  
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
  void SetPosition(const glm::vec2& position);
  void SetColor(const ci::Color& color);
  void SetDirection(const Direction& direction);
  void SetScore(const size_t& score);
  ci::Color GetColor() const;
  glm::vec2 GetPosition() const;
  size_t GetScore() const;
  Direction GetDirection() const;

private:
  glm::vec2 curr_position_;
  size_t score_;
  ci::Color color_;
  Direction direction_;
};

} // namespace finalproject