#include <visualizer/game_app.h>
#include "core/bullet.h"
#include "core/player.h"

namespace finalproject {
    
namespace visualizer {

GameApp::GameApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::draw() {
  ci::Color background_color(kBackgroundColor);
  ci::gl::clear(background_color);

  Player red_player = game_status_.GetRedPlayer();
  Player blue_player = game_status_.GetBluePlayer();
  
  if (red_player.GetScore() == 10) {
    ci::gl::color(kDefaultColor);
    ci::gl::drawString("Red Player Wins!", glm::vec2((int) kWindowSize/2, (int) kWindowSize/2));
  } else if (blue_player.GetScore() == 10) {
    ci::gl::color(kDefaultColor);
    ci::gl::drawString("Blue Player Wins!", glm::vec2((int) kWindowSize/2, (int) kWindowSize/2));
  } else {
    ci::gl::color(kDefaultColor);
    ci::gl::drawStrokedRect(ci::Rectf(game_status_.kTopLeft, game_status_.kBottomRight));

    ci::gl::color(kDefaultColor);
    ci::gl::drawString("Red Player: " + std::to_string(red_player.GetScore()), game_status_.kRedScoreDisplayLoc);
    ci::gl::drawString("Blue Player: " + std::to_string(blue_player.GetScore()), game_status_.kBlueScoreDisplayLoc);

    ci::gl::color(red_player.GetColor());
    ci::gl::drawSolidCircle(red_player.GetPosition(), Player::kTankDimensions);

    ci::gl::color(blue_player.GetColor());
    ci::gl::drawSolidCircle(blue_player.GetPosition(), Player::kTankDimensions);

    DrawBullets(); 
  }
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  Player& red_player = game_status_.GetRedPlayer();
  Player& blue_player = game_status_.GetBluePlayer();
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w:
      if (game_status_.CanTankMoveInDir(red_player, Player::Direction::UP)) {
        red_player.MoveUp(); 
      }
      break;

    case ci::app::KeyEvent::KEY_a:
      if (game_status_.CanTankMoveInDir(red_player, Player::Direction::LEFT)) {
        red_player.MoveLeft();
      }
      
      break;
      
    case ci::app::KeyEvent::KEY_s:
      if (game_status_.CanTankMoveInDir(red_player, Player::Direction::DOWN)) {
        red_player.MoveDown();
      }
      break;

    case ci::app::KeyEvent::KEY_d:
      if (game_status_.CanTankMoveInDir(red_player, Player::Direction::RIGHT)) {
        red_player.MoveRight();
      }
      break;

    case ci::app::KeyEvent::KEY_i:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::UP)) {
        blue_player.MoveUp();
      }
      break;

    case ci::app::KeyEvent::KEY_j:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::LEFT)) {
        blue_player.MoveLeft();
      }
      break;

    case ci::app::KeyEvent::KEY_k:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::DOWN)) {
        blue_player.MoveDown();
      }
      break;

    case ci::app::KeyEvent::KEY_l:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::RIGHT)) {
        blue_player.MoveRight();
      }
      break;
      
    case ci::app::KeyEvent::KEY_SPACE:
      game_status_.ShootBullet(red_player);
      break;

    case ci::app::KeyEvent::KEY_UP:
      game_status_.ShootBullet(blue_player);
      break;
  }
}


void GameApp::update() {
  game_status_.AdvanceOneFrame();
}

void GameApp::DrawBullets() {
  if (game_status_.GetBulletsInGame().empty()) {
    return;
  }
  for (Bullet& bullet : game_status_.GetBulletsInGame()) {
    ci::gl::color(ci::Color(bullet.GetColor()));
    ci::gl::drawSolidCircle(bullet.GetPosition(), bullet.GetRadius());
  }
}


} // namespace visualizer

} // namespace finalproject