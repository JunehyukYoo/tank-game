#include <catch2/catch.hpp>

#include "core/game_status.h"
#include "core/map.h"
#include "core/wall.h"

TEST_CASE("Map is initialized correctly") {
  finalproject::GameStatus game;
  finalproject::Map map = game.GetMap();
  std::vector<std::vector<finalproject::Wall>> walls = map.GetWalls();
  std::vector<std::vector<bool>> bool_map = map.GetMapOfWallBooleans();
  REQUIRE(walls.size() == 20);
  REQUIRE(walls[0].size() == 20);
  REQUIRE(map.GetWalls().empty() == false);
  
  SECTION("Red player spawn is not filled up") {
    REQUIRE(walls[0][0].bottom_right_ == glm::vec2(0,0));
    REQUIRE(walls[0][1].bottom_right_ == glm::vec2(0,0));
    REQUIRE(walls[1][0].bottom_right_ == glm::vec2(0,0));
    REQUIRE(walls[1][1].bottom_right_ == glm::vec2(0,0));
  }
  
  SECTION("Blue player spawn is not filled up") {
    REQUIRE(walls[19][19].bottom_right_ == glm::vec2(0,0));
    REQUIRE(walls[19][18].bottom_right_ == glm::vec2(0,0));
    REQUIRE(walls[18][19].bottom_right_ == glm::vec2(0,0));
    REQUIRE(walls[18][18].bottom_right_ == glm::vec2(0,0));
  }

  SECTION("Percentage map filled with walls") {
    float count_wall = 0;
    float count_total = 0;
    for (size_t row = 0; row < bool_map.size(); row++) {
      for (size_t col = 0; col < bool_map[0].size(); col++) {
        if (bool_map[row][col]) {
          count_wall++;
        }
        count_total++;
      }
    }
    float percentage = count_wall/count_total;
    REQUIRE(percentage == Approx(0.4).margin(0.05)); 
  }
}

TEST_CASE("Bullet wall collision") {
  finalproject::GameStatus game;
  finalproject::Player red_player = game.GetRedPlayer();

  //removing randomly generated walls
  finalproject::Map& map = game.GetMap();
  map.EmptyMap();
  
  //Adding in walls in top left and bottom right corners
  std::vector<std::vector<bool>>& bool_map = map.GetMapOfWallBooleans();
  std::vector<std::vector<finalproject::Wall>>& walls = map.GetWalls();
  bool_map[0][0] = true;
  bool_map[19][19] = true;
  walls[0][0].top_left_ = glm::vec2(100, 100);
  walls[0][0].bottom_right_ = glm::vec2(125, 125);
  walls[0][0].health_ = 4;
  walls[19][19].top_left_ = glm::vec2(575, 575);
  walls[19][19].bottom_right_ = glm::vec2(600, 600);
  walls[19][19].health_ = 4;
  
  SECTION("Shooting up at a wall") {
    red_player.SetPosition(glm::vec2(115, 131));
    red_player.SetDirection(finalproject::Player::UP);
    REQUIRE(walls[0][0].health_ == 4);
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    REQUIRE(walls[0][0].health_ == 3);
  }

  SECTION("Shooting left at a wall") {
    red_player.SetPosition(glm::vec2(131, 115));
    red_player.SetDirection(finalproject::Player::LEFT);
    REQUIRE(walls[0][0].health_ == 4);
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    REQUIRE(walls[0][0].health_ == 3);
  }
  
  SECTION("Shooting down at a wall") {
    red_player.SetPosition(glm::vec2(580, 569));
    red_player.SetDirection(finalproject::Player::DOWN);
    REQUIRE(walls[19][19].health_ == 4);
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    REQUIRE(walls[19][19].health_ == 3);
  }

  SECTION("Shooting right at a wall") {
    red_player.SetPosition(glm::vec2(569, 580));
    red_player.SetDirection(finalproject::Player::RIGHT);
    REQUIRE(walls[19][19].health_ == 4);
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    REQUIRE(walls[19][19].health_ == 3);
  }
  
  SECTION("Wall breaks properly") {
    red_player.SetPosition(glm::vec2(115, 131));
    red_player.SetDirection(finalproject::Player::UP);
    REQUIRE(walls[0][0].health_ == 4);
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    game.ShootBullet(red_player);
    game.AdvanceOneFrame();
    game.AdvanceOneFrame();
    REQUIRE(bool_map[0][0] == false);
    REQUIRE(walls[0][0].health_ == 0);
    REQUIRE(walls[0][0].top_left_ == glm::vec2(0, 0));
    REQUIRE(walls[0][0].bottom_right_ == glm::vec2(0, 0));
  }
}

TEST_CASE("Player movement against walls") {
  finalproject::GameStatus game;
  finalproject::Player red_player = game.GetRedPlayer();

  //removing randomly generated walls
  finalproject::Map& map = game.GetMap();
  map.EmptyMap();

  //Adding in walls in top left and bottom right corners
  std::vector<std::vector<bool>>& bool_map = map.GetMapOfWallBooleans();
  std::vector<std::vector<finalproject::Wall>>& walls = map.GetWalls();
  bool_map[0][0] = true;
  bool_map[19][19] = true;
  walls[0][0].top_left_ = glm::vec2(100, 100);
  walls[0][0].bottom_right_ = glm::vec2(125, 125);
  walls[0][0].health_ = 4;
  walls[19][19].top_left_ = glm::vec2(575, 575);
  walls[19][19].bottom_right_ = glm::vec2(600, 600);
  walls[19][19].health_ = 4;
  
  SECTION("Move up against wall") {
    red_player.SetPosition(glm::vec2(115, 131));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::UP) == false);
  }

  SECTION("Move left against wall") {
    red_player.SetPosition(glm::vec2(131, 115));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::LEFT) == false);
  }
  
  SECTION("Move right against wall") {
    red_player.SetPosition(glm::vec2(569, 580));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::RIGHT) == false);
  }

  SECTION("Move down against wall") {
    red_player.SetPosition(glm::vec2(580, 569));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::DOWN) == false);
  }
}