#include <catch2/catch.hpp>

#include "core/game_status.h"
#include "core/map.h"
#include "core/wall.h"

TEST_CASE("Sanity check 2") {
  REQUIRE(1 < 2);
}

TEST_CASE("Map is initialized correctly") {
  finalproject::GameStatus game;
  finalproject::Map map = game.GetMap();
  std::vector<std::vector<finalproject::Wall>> walls = map.GetWalls();
  REQUIRE(walls.size() == 50);
  REQUIRE(walls[0].size() == 50);
  REQUIRE(walls[0][0].bottom_right_ == glm::vec2(0,0));
  REQUIRE(walls[0][1].bottom_right_ == glm::vec2(0,0));
  REQUIRE(walls[1][0].bottom_right_ == glm::vec2(0,0));
  REQUIRE(walls[1][1].bottom_right_ == glm::vec2(0,0));

  REQUIRE(map.GetWalls().empty() == false);
}