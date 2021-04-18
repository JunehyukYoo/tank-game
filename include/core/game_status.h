#include <glm/vec2.hpp>
#include <core/player.h>

namespace finalproject {
    
class GameStatus {
public:
  GameStatus();
  
  
  
private:
  Player player_red_;
  Player player_blue_;
  bool red_shot_;
  bool blue_shot_;
  
  const glm::vec2 kTopLeft = glm::vec2(100, 100);
  const glm::vec2 kTopRight = glm::vec2(600, 600);
};
    
}