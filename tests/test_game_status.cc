#include <catch2/catch.hpp>

#include "core/game_status.h"
#include "core/bullet.h"
#include "core/player.h"

TEST_CASE("Sanity check") {
  REQUIRE(1 < 2);
}

TEST_CASE("Testing player spawning") {
  finalproject::GameStatus game;
  
  SECTION("Red player") {
    finalproject::Player red_player = game.GetRedPlayer();
    REQUIRE(red_player.GetColor() == ci::Color("red"));
    REQUIRE(red_player.GetDirection() == finalproject::Player::RIGHT);
    REQUIRE(red_player.GetScore() == 0);
    REQUIRE(red_player.GetCurrPosition() == glm::vec2(105, 105));
  }

  SECTION("Blue player") {
    finalproject::Player blue_player = game.GetBluePlayer();
    REQUIRE(blue_player.GetColor() == ci::Color("blue"));
    REQUIRE(blue_player.GetDirection() == finalproject::Player::LEFT);
    REQUIRE(blue_player.GetScore() == 0);
    REQUIRE(blue_player.GetCurrPosition() == glm::vec2(595, 595));
  }
}

TEST_CASE("Test player movement") {
  finalproject::GameStatus game;
  finalproject::Player red_player = game.GetRedPlayer();
  red_player.SetCurrPosition(glm::vec2(300, 300));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::DOWN));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::LEFT));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::RIGHT));
  REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::UP));
  
  SECTION("Against wall check movement (up and left)") {
    red_player.SetCurrPosition(glm::vec2(110, 110));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::UP) == false);
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::LEFT) == false);
  }

  SECTION("Against wall check movement (down and right)") {
    red_player.SetCurrPosition(glm::vec2(590, 590));
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::DOWN) == false);
    REQUIRE(game.CanTankMoveInDir(red_player, finalproject::Player::RIGHT) == false);
  }
}

TEST_CASE("Testing general bullet functionality") {
  finalproject::GameStatus game;
  finalproject::Player player;
  player.SetColor(ci::Color("red"));
  player.SetDirection(finalproject::Player::RIGHT);
  player.SetCurrPosition(glm::vec2(300, 300));
  
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
    REQUIRE(bullet.GetVelocity() == glm::vec2(10, 0));
  }
}