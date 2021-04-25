#include <catch2/catch.hpp>

#include "core/game_status.h"
#include "core/bullet.h"
#include "core/player.h"

TEST_CASE("Testing game initialization") {
  finalproject::GameStatus game;
  REQUIRE(game.GetBulletsInGame().size() == 0);
  
  SECTION("Red player") {
    finalproject::Player red_player = game.GetRedPlayer();
    REQUIRE(red_player.GetColor() == ci::Color("red"));
    REQUIRE(red_player.GetDirection() == finalproject::Player::RIGHT);
    REQUIRE(red_player.GetScore() == 0);
    REQUIRE(red_player.GetPosition() == glm::vec2(115, 115));
  }

  SECTION("Blue player") {
    finalproject::Player blue_player = game.GetBluePlayer();
    REQUIRE(blue_player.GetColor() == ci::Color("blue"));
    REQUIRE(blue_player.GetDirection() == finalproject::Player::LEFT);
    REQUIRE(blue_player.GetScore() == 0);
    REQUIRE(blue_player.GetPosition() == glm::vec2(585, 585));
  }
  
}

TEST_CASE("Test player movement") {
  finalproject::GameStatus game;
  finalproject::Player red_player = game.GetRedPlayer();
  red_player.SetPosition(glm::vec2(300, 300));
  
  //code to ignore walls
  finalproject::Map& map = game.GetMap();
  map.EmptyMap();

  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::DOWN));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::LEFT));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::RIGHT));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::UP));
  REQUIRE(red_player.GetDirection() == finalproject::Player::RIGHT);
  red_player.MoveRight();
  REQUIRE(red_player.GetPosition() == glm::vec2(310, 300));
  REQUIRE(red_player.GetDirection() == finalproject::Player::RIGHT);
  red_player.MoveUp();
  REQUIRE(red_player.GetPosition() == glm::vec2(310, 290));
  REQUIRE(red_player.GetDirection() == finalproject::Player::UP);
  red_player.MoveDown();
  REQUIRE(red_player.GetPosition() == glm::vec2(310, 300));
  REQUIRE(red_player.GetDirection() == finalproject::Player::DOWN);
  red_player.MoveLeft();
  REQUIRE(red_player.GetPosition() == glm::vec2(300, 300));
  REQUIRE(red_player.GetDirection() == finalproject::Player::LEFT);
  
  SECTION("Against wall check movement (up and left)") {
    red_player.SetPosition(glm::vec2(110, 110));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::UP) == false);
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::LEFT) == false);
  }

  SECTION("Against wall check movement (down and right)") {
    red_player.SetPosition(glm::vec2(590, 590));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::DOWN) == false);
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::RIGHT) == false);
  }
}

TEST_CASE("Testing bullet functionality") {
  finalproject::GameStatus game;
  finalproject::Player player;
  player.SetColor(ci::Color("red"));
  player.SetDirection(finalproject::Player::RIGHT);
  player.SetPosition(glm::vec2(300, 300));

  //code to ignore walls
  finalproject::Map& map = game.GetMap();
  map.EmptyMap();
  
  SECTION("Adding/shooting bullets") {
    REQUIRE(game.GetBulletsInGame().size() == 0);
    game.ShootBullet(player);
    REQUIRE(game.GetBulletsInGame().size() == 1);
  }
  
  SECTION("Bullet variables are initialized correctly") {
    game.ShootBullet(player);
    finalproject::Bullet bullet = game.GetBulletsInGame()[0];
    REQUIRE(bullet.GetRadius() == 5);
    REQUIRE(bullet.GetPosition() == glm::vec2(300, 300));
    REQUIRE(bullet.GetColor() == ci::Color("red"));
    REQUIRE(bullet.GetVelocity() == glm::vec2(6, 0));
  }
  
  SECTION("Bullet hits container") {
    player.SetPosition(glm::vec2(595, 300));
    game.ShootBullet(player);
    REQUIRE(game.GetBulletsInGame().size() == 1);
    game.AdvanceOneFrame();
    REQUIRE(game.GetBulletsInGame().size() == 0);
  }
  
  SECTION("Bullet hits opponent") {
    player.SetPosition(glm::vec2(580, 585));
    game.ShootBullet(player);
    REQUIRE(game.GetBulletsInGame().size() == 1);
    game.AdvanceOneFrame();
    REQUIRE(game.GetBulletsInGame().size() == 0);
    REQUIRE(game.GetRedPlayer().GetPosition() == glm::vec2(115, 115));
    REQUIRE(game.GetBluePlayer().GetPosition() == glm::vec2(585, 585));
    REQUIRE(game.GetRedPlayer().GetScore() == 1);
    REQUIRE(game.GetBluePlayer().GetScore() == 0);
  }
}