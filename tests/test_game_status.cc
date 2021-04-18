#include <catch2/catch.hpp>

#include "core/game_status.h"
#include "core/bullet.h"
#include "core/player.h"

TEST_CASE("Sanity check") {
  REQUIRE(1 < 2);
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
  
  SECTION("Bullet variables are correct") {
    game.ShootBullet(player);
    finalproject::Bullet bullet = game.GetBulletsInGame()[0];
    REQUIRE(bullet.GetRadius() == 5);
    REQUIRE(bullet.GetPosition() == glm::vec2(300, 300));
    REQUIRE(bullet.GetColor() == ci::Color("red"));
    REQUIRE(bullet.GetVelocity() == glm::vec2(10, 0));
  }
}