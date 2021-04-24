#pragma once
#include <vector>
#include "core/wall.h"

namespace finalproject {
    
/** Map object that has walls and consumables */
class Map {
public:
  Map();
  
  /**
   * Creates a new map with the specified dimensions and a percentage of the map filled with walls.
   * @param top_left The top left coordinate of the map
   * @param bottom_right The bottom right coordinate of the map
   * @param percent_map_is_walls The percentage of the map being walls.
   */
  Map(const glm::vec2& top_left, const glm::vec2& bottom_right, const float percent_map_is_walls);
  
  /**
   * Fills the map with a certain percentage of walls.
   * @param percent_map_is_walls The desired percentage of walls to be filling the map.
   */
  void FillMapWithWalls(const float& percent_map_is_walls);
  
  /**
   * Returns if the current point is within spawn points for characters.
   * @param x The x-coordinate
   * @param y The y-coordinate
   * @param dimension_of_spawn The spawn dimensions 
   * @return True or false
   */
  bool LookingAtSpawns(const size_t& x, const size_t& y, const float& dimension_of_spawn);
  
  std::pair<bool, std::pair<size_t, size_t>> ContainsWallAtPoint(const glm::vec2& position);
  
  
  /** Getters and setters */
  std::vector<std::vector<bool>>& GetMapOfBooleans();
  std::vector<std::vector<Wall>>& GetWalls();

private:
  /** 2D vector of positions on the board and whether they are filled with a wall or not */
  std::vector<std::vector<bool>> contains_walls_;
  
  /** Map of walls and corresponding data */
  std::vector<std::vector<Wall>> walls_in_map_;
  
  glm::vec2 container_top_left_;
  glm::vec2 container_bottom_right_;
  
  const size_t kWallDimensions = 25;
  const size_t kWallHealth = 4;
};
    
}