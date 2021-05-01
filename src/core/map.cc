#include "core/map.h"
#include "core/game_status.h"
#include "core/power_up.h"

namespace finalproject {

Map::Map() {}

Map::Map(const glm::vec2& top_left, const glm::vec2& bottom_right, const float& percent_map_is_walls, const size_t& num_power_ups) {
  container_top_left_ = top_left;
  container_bottom_right_ = bottom_right;
  size_t row_length = std::abs(container_top_left_.x - container_bottom_right_.x)/kWallDimensions;
  size_t col_length = std::abs(container_top_left_.y - container_bottom_right_.y)/kWallDimensions;
  std::vector<std::vector<Wall>> sized_array(row_length, std::vector<Wall>(col_length));
  std::vector<std::vector<bool>> sized_array_bool(row_length, std::vector<bool>(col_length));
  //std::vector<PowerUp> sized_array_power_ups(num_power_ups);
  walls_in_map_ = sized_array;
  contains_walls_ = sized_array_bool;
  contains_power_ups_ = sized_array_bool;
  //power_ups_in_map = sized_array_power_ups;
  FillMapWithWalls(percent_map_is_walls);
  FillMapWithPowerUps(num_power_ups);
  sized_array.clear();
  sized_array_bool.clear();
  //sized_array_power_ups.clear();
}

void Map::FillMapWithWalls(const float& percent_map_is_walls) {
  if (percent_map_is_walls < 0 || percent_map_is_walls > 1) {
    throw std::invalid_argument("Invalid percentage");
  }
  size_t vector_row = 0;
  size_t vector_col = 0;
  float dimension_of_spawn = 1;
  while (dimension_of_spawn * kWallDimensions < Player::kTankDimensions) {
    dimension_of_spawn += 1;
  }
  dimension_of_spawn *= kWallDimensions;
  for (size_t row = container_top_left_.x; row < container_bottom_right_.x; row += kWallDimensions) {
    for (size_t col = container_top_left_.y; col < container_bottom_right_.y; col += kWallDimensions) {
      float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      if (random <= percent_map_is_walls && !LookingAtSpawns(row, col, dimension_of_spawn)) {
        contains_walls_[vector_row][vector_col] = true;
        walls_in_map_[vector_row][vector_col] = Wall(kWallDimensions, glm::vec2(row, col), kWallHealth);
      } 
      vector_row++;
    }
    vector_col++;
    vector_row = 0;
  }
}

void Map::FillMapWithPowerUps(const size_t &num_of_power_ups) {
  size_t count_empty_spaces = 0;
  size_t num_power_ups_left = num_of_power_ups;
  for (size_t row = 0; row < contains_walls_.size(); row++) {
    for (size_t col = 0; col < contains_walls_[0].size(); col++) {
      if (!contains_walls_[row][col]) {
        count_empty_spaces++;
      }
    }
  }
  
  if (num_of_power_ups > count_empty_spaces) {
    throw std::invalid_argument("Trying to insert too many power ups.");
  }

  size_t vector_row = 0;
  size_t vector_col = 0;
  float dimension_of_spawn = 1;
  while (dimension_of_spawn * kWallDimensions < Player::kTankDimensions) {
    dimension_of_spawn += 1;
  }
  dimension_of_spawn *= kWallDimensions;
  for (size_t row = container_top_left_.x; row < container_bottom_right_.x; row += kWallDimensions) {
    for (size_t col = container_top_left_.y; col < container_bottom_right_.y; col += kWallDimensions) {
      if (num_power_ups_left == 0) {
        break;
      }
      float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      if (random <= 0.03 && !LookingAtSpawns(row, col, dimension_of_spawn) &&
          !contains_walls_[vector_row][vector_col] && !contains_power_ups_[vector_row][vector_col]) {
        power_ups_in_map.emplace_back(glm::vec2(row + kWallDimensions/2, col + kWallDimensions/2));
        num_power_ups_left--;
        contains_power_ups_[vector_row][vector_col] = true;
      }
      vector_row++;
    }
    vector_col++;
    vector_row = 0;
  }
}

bool Map::LookingAtSpawns(const size_t& x, const size_t& y, const float& dimension_of_spawn) {
   if (x <= container_top_left_.x + dimension_of_spawn && y <= container_top_left_.y + dimension_of_spawn ) {
     return true;
   } else if (x >= container_bottom_right_.x - 2 * dimension_of_spawn && y >= container_bottom_right_.y - 2 * dimension_of_spawn) {
     return true;
   } else {
     return false;
   }
}

std::pair<bool, std::pair<size_t, size_t>> Map::ContainsWallAtPoint(const glm::vec2 &position) const{
  if (walls_in_map_.empty()) {
    return {false, {0,0}};
  }
  for (size_t row = 0; row < walls_in_map_.size( ); row++) {
    for (size_t col = 0; col < walls_in_map_[0].size(); col++) {
      if (contains_walls_[row][col]) {
        Wall curr_wall = walls_in_map_[row][col];
        if (position.x >= curr_wall.top_left_.x &&
            position.x <= curr_wall.bottom_right_.x &&
            position.y >= curr_wall.top_left_.y &&
            position.y <= curr_wall.bottom_right_.y) {
          return {true, {row, col}};
        }
      }
    }
  }
  return {false, {0,0}};
}

void Map::EmptyMap() {
  for (size_t row = 0; row < contains_walls_.size(); row++) {
    for (size_t col = 0; col < contains_walls_[0].size(); col++) {
      contains_walls_[row][col] = false;
      walls_in_map_[row][col].health_ = 0;
      walls_in_map_[row][col].top_left_ = glm::vec2(0, 0);
      walls_in_map_[row][col].bottom_right_ = glm::vec2(0, 0);
    }
  }
}

std::vector<std::vector<bool>>& Map::GetMapOfWallBooleans() {
  return contains_walls_;
}

std::vector<std::vector<Wall>>& Map::GetWalls() {
  return walls_in_map_;
}

std::vector<PowerUp> &Map::GetPowerUps() {
  return power_ups_in_map;
}

std::vector<std::vector<bool>> &Map::GetMapOfPowerUpBooleans() {
  return contains_power_ups_;
}

} // namespace finalproject