#include <glm/vec2.hpp>

namespace finalproject {
    
class GameStatus {
public:
  GameStatus();
  
private:
  
  
  const glm::vec2 kTopLeft = glm::vec2(100, 100);
  const glm::vec2 kTopRight = glm::vec2(600, 600);
};
    
}