#include <catch2/catch.hpp>

#include "core/game_status.h"
#include "core/power_up.h"

TEST_CASE("Test power up initialization") {
  finalproject::GameStatus game_status;
  finalproject::Map map = game_status.GetMap();
  SECTION("Number of power ups is correct") {
    std::vector<std::vector<bool>> contains_power_ups = map.GetMapOfPowerUpBooleans();
    size_t count = 0;
    for (size_t row = 0; row < contains_power_ups.size(); row++) {
      for (size_t col = 0; col < contains_power_ups[0].size(); col++) {
        if (contains_power_ups[row][col]) {
          count++;
        }
      }
    }
    REQUIRE(count == 5);
  }
   
  
  SECTION("Power up positions and radii are initialized correctly respective to each other") {
    std::vector<finalproject::PowerUp> power_ups = map.GetPowerUps();
    bool power_up_in_same_position = false;
    std::vector<glm::vec2> positions(5);
    size_t count = 0;
    for (const finalproject::PowerUp& power_up : power_ups) {
      REQUIRE(power_up.GetRadius() == 5);
      REQUIRE(power_up.GetPosition().x > 100);
      REQUIRE(power_up.GetPosition().y > 100);
      REQUIRE(power_up.GetPosition().x < 600);
      REQUIRE(power_up.GetPosition().y < 600);
      positions[count] = power_up.GetPosition();
      count++;
    }
    count = 0;
    for (const finalproject::PowerUp& power_up : power_ups) {
      for (size_t i = 0; i < 5; i++) {
        if (i != count && positions[i] == power_up.GetPosition()) {
          power_up_in_same_position = true;
        }
      }
      count++;
    }
    REQUIRE(power_up_in_same_position == false);
  }
  
  SECTION("Ensure power ups don't spawn inside walls") {
    std::vector<std::vector<bool>> contains_power_ups = map.GetMapOfPowerUpBooleans();
    std::vector<std::vector<bool>> contains_walls = map.GetMapOfWallBooleans();
    for (size_t row = 0; row < contains_power_ups.size(); row++) {
      for (size_t col = 0; col < contains_power_ups[0].size(); col++) {
        if (contains_power_ups[row][col]) {
          REQUIRE(contains_walls[row][col] == false);
        }
      }
    }
  }
}

TEST_CASE("Power up pickup and shooting") {
  finalproject::GameStatus game_status;
  finalproject::Player& red_player = game_status.GetRedPlayer();
  std::vector<finalproject::Bullet> bullets = game_status.GetBulletsInGame();
  finalproject::Map map = game_status.GetMap();
  std::vector<finalproject::PowerUp>& power_ups = map.GetPowerUps();
 
  //removing randomly generated walls and power ups
  map.RemoveWalls();
  map.RemovePowerUps();
  
  finalproject::PowerUp power_up(glm::vec2(300, 300));
  power_ups.push_back(power_up);
  red_player.SetPosition(glm::vec2(290, 300));
  
  REQUIRE(red_player.GetPoweredUpStatus() == false);
  REQUIRE(power_ups.size() == 1);
  
  red_player.MoveRight();
  game_status.AdvanceOneFrame();
  
  SECTION("Picking up power up") {
    REQUIRE(power_ups.size() == 0);
    REQUIRE(red_player.GetPoweredUpStatus());
  }
}