#include <glm/vec2.hpp>
#include <string>
#include <cinder/Color.h>

namespace finalproject {

/** A tank/player with all the relevant information */
class Player {
  
public:
  /** Enum for direction the tank is currently pointing. Includes: UP, DOWN, LEFT, RIGHT */
  enum Direction {
      UP,
      DOWN,
      LEFT,
      RIGHT,
  };
  
  Player();
  
  /**
   * Creates a player and sets according variables with respect to color. If the color is not blue or red, throw an
   * invalid argument exception.
   * @param color The color the player is.
   */
  Player(ci::Color color);
  
  /** BIG 5 */
  //copy constructor
  Player(const Player& source);
  //move constructor
  Player(Player&& source) noexcept;
  //copy assignment operator
  Player& operator=(const Player& source);
  //move assignment operator
  Player& operator=(Player&& source) noexcept;
  //destructor
  ~Player();
  
  
  /** Methods to move character: Left, Right, Up, Down */
  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();

private:
  glm::vec2 curr_position_;
  size_t score_;
  ci::Color color_;
  Direction direction_;
  
  const ci::Color kRed = ci::Color("red");
  const ci::Color kBlue = ci::Color("blue");
  const glm::vec2 kRedStart = glm::vec2(105, 105);
  const glm::vec2 kBlueStart = glm::vec2(595, 595);
  const size_t kMoveStep = 2;
  const std::string kTankImagePath = "";
};

} // namespace finalproject