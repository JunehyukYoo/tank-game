#include <glm/vec2.hpp>
#include <string>

namespace finalproject {

/** A tank/player with all the relevant information */
class Player {
  
public:
  Player();

private:
  glm::vec2 curr_position_;
  size_t score_;
  
  const std::string kTankImagePath = "";
};

} // namespace finalproject