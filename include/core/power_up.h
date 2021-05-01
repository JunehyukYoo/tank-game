#pragma once
#include "player.h"

namespace finalproject {
    
/** Power up that lets players shoot three bullets at a time */
class PowerUp {
public:
  PowerUp(const glm::vec2& position);
  
  /** Getters */
  glm::vec2 GetPosition() const;
  float GetRadius() const;
private:
  glm::vec2 position_;
  float radius_;

  constexpr const static float kDefaultRadius = 5;
};

} // namespace finalproject