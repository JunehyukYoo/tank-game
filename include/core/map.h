#pragma once
#include <vector>
#include "wall.h"
#include "power_up.h"

namespace finalproject {
    
/** Map object that has walls and consumables */
class Map {
public:
  Map();
  
  /**
   * Creates a new map with the specified dimensions and a percentage of the map filled with walls.
   * @param top_left The top left coordinate of the map
   * @param bottom_right The bottom right coordinate of the map
   * @param percent_map_is_walls The percentage of the map being walls
   * @param num_power_ups The number of power ups to be in the map
   */
  Map(const glm::vec2& top_left, const glm::vec2& bottom_right, const float& percent_map_is_walls, const size_t& num_power_ups);
  
  /**
   * Fills the map with a certain percentage of walls.
   * @param percent_map_is_walls The desired percentage of walls to be filling the map
   */
  void FillMapWithWalls(const float& percent_map_is_walls);
  
  /**
   * Fills the map with a certain amount of power ups.
   * @param num_of_power_ups The number of power ups in the map
   */
  void FillMapWithPowerUps(const size_t& num_of_power_ups);
  
  /**
   * Returns if the current point is within spawn points for characters.
   * @param x The x-coordinate
   * @param y The y-coordinate
   * @param dimension_of_spawn The spawn dimensions 
   * @return True or false
   */
  bool LookingAtSpawns(const size_t& x, const size_t& y, const float& dimension_of_spawn);
  
  /**
   * A pair to check whether there is a wall at a certain point. If true, return the boolean and row & col of the 
   * specific wall. Otherwise return false and (0,0).
   * @param position The position to check
   * @return The bool and corresponding point within the Wall vector
   */
  std::pair<bool, std::pair<size_t, size_t>> ContainsWallAtPoint(const glm::vec2& position) const;
  
  /** Method to remove walls for testing purposes. */
  void RemoveWalls();
  
  /** Remove power ups for testing purposes. */
  void RemovePowerUps();
  
  /** Getters and setters */
  std::vector<std::vector<bool>>& GetMapOfWallBooleans();
  std::vector<std::vector<bool>>& GetMapOfPowerUpBooleans();
  std::vector<std::vector<Wall>>& GetWalls();
  std::vector<PowerUp>& GetPowerUps();

private:
  /** 2D vector of positions on the board and whether they are filled with a wall or not */
  std::vector<std::vector<bool>> contains_walls_;

  /** 2D vector of positions on the board and whether they are filled with a wall or not */
  std::vector<std::vector<bool>> contains_power_ups_;
  
  /** Map of walls and corresponding data */
  std::vector<std::vector<Wall>> walls_in_map_;
  
  /** Vector of all power ups */
  std::vector<PowerUp> power_ups_in_map;
  
  glm::vec2 container_top_left_;
  glm::vec2 container_bottom_right_;
  
  const size_t kWallDimensions = 25;
  const size_t kWallHealth = 4;
};
    
}