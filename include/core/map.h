#pragma once
#include <vector>
#include "core/wall.h"

namespace finalproject {
    
/** Map object that has walls and consumables */
class Map {
public:
  Map();
  
  void FillMapWithWalls(float percent_map_is_walls);
  
  /** Getters and setters */
  std::vector<std::vector<std::vector<bool>>> GetMapOfBooleans() const;
  std::vector<std::vector<Wall>> GetWalls();

private:
  /** 2D vector of positions on the board and whether they are filled with a wall or not */
  std::vector<std::vector<std::vector<bool>>> contains_walls_;
  
  /** Map of walls and corresponding data */
  std::vector<std::vector<Wall>> walls_in_map_;
  
  const size_t kWallDimensions = 10;
  const size_t kWallHealth = 4;
};
    
}