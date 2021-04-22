#include "core/map.h"
#include "core/game_status.h"

namespace finalproject {

Map::Map() {}

Map::Map(glm::vec2 top_left, glm::vec2 bottom_right, float percent_map_is_walls) {
  container_top_left_ = top_left;
  container_bottom_right_ = bottom_right;
  size_t row_length = std::abs(container_top_left_.x - container_bottom_right_.x)/2;
  size_t col_length = std::abs(container_top_left_.y - container_bottom_right_.y)/2;
  std::vector<std::vector<Wall>> sized_array(row_length, std::vector<Wall>(col_length));
  std::vector<std::vector<bool>> sized_array_bool(row_length, std::vector<bool>(col_length));
  walls_in_map_ = sized_array;
  contains_walls_ = sized_array_bool;
  FillMapWithWalls(percent_map_is_walls);
  sized_array.clear();
  sized_array_bool.clear();
}

void Map::FillMapWithWalls(float percent_map_is_walls) {
  if (percent_map_is_walls < 0 || percent_map_is_walls > 1) {
    throw std::invalid_argument("Invalid percentage");
  }
  for (size_t row = container_top_left_.x; row < container_bottom_right_.x - kWallDimensions; row += kWallDimensions) {
    for (size_t col = container_top_left_.y; col < container_bottom_right_.y - kWallDimensions; col += kWallDimensions) {
      float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      if (random <= percent_map_is_walls) {
        contains_walls_[row][col] = true;
        walls_in_map_[row][col] = Wall(kWallDimensions, glm::vec2(row, col), kWallHealth);
      } 
    }
  }
}

std::vector<std::vector<bool>> Map::GetMapOfBooleans() const {
  return contains_walls_;
}

std::vector<std::vector<Wall>> Map::GetWalls() {
  return walls_in_map_;
}


}