#include "core/map.h"

namespace finalproject {

Map::Map() {}

void Map::FillMapWithWalls(float percent_map_is_walls) {
  if (percent_map_is_walls < 0 || percent_map_is_walls > 1) {
    throw std::invalid_argument("Invalid percentage");
  }
}

std::vector<std::vector<std::vector<bool>>> Map::GetMapOfBooleans() const {
  return contains_walls_;
}

std::vector<std::vector<Wall>> Map::GetWalls() {
  return walls_in_map_;
}


}