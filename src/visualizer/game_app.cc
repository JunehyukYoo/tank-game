#include <visualizer/game_app.h>
#include "core/bullet.h"
#include "core/player.h"

namespace finalproject {
    
namespace visualizer {

GameApp::GameApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color(kBorderColor));
  ci::gl::drawStrokedRect(ci::Rectf(game_status_.kTopLeft, game_status_.kBottomRight));
  
  ci::gl::color(game_status_.GetRedPlayer().GetColor());
  ci::gl::drawSolidCircle(game_status_.GetRedPlayer().GetPosition(), Player::kTankDimensions);
  std::cout << game_status_.GetRedPlayer().GetPosition() << std::endl;
  //std::cout << game_status_.GetBulletsInGame().size() << std::endl;
  
  ci::gl::color(game_status_.GetBluePlayer().GetColor());
  ci::gl::drawSolidCircle(game_status_.GetBluePlayer().GetPosition(), Player::kTankDimensions);
  
  DrawBullets();
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  Player red_player = game_status_.GetRedPlayer();
  Player blue_player = game_status_.GetBluePlayer();
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
        //std::cout << "move right" << std::endl;
        red_player.MoveRight();
      }
      break;

    case ci::app::KeyEvent::KEY_i:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::UP)) {
        blue_player.MoveUp();
      }
      std::cout << "up blue" << std::endl;
      break;

    case ci::app::KeyEvent::KEY_j:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::LEFT)) {
        blue_player.MoveLeft();
      }
      std::cout << "left blue" << std::endl;
      break;

    case ci::app::KeyEvent::KEY_k:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::DOWN)) {
        blue_player.MoveDown();
      }
      std::cout << "down blue" << std::endl;
      break;

    case ci::app::KeyEvent::KEY_l:
      if (game_status_.CanTankMoveInDir(blue_player, Player::Direction::RIGHT)) {
        blue_player.MoveRight();
      }
      std::cout << "right blue" << std::endl;
      break;
      
    case ci::app::KeyEvent::KEY_SPACE:
      std::cout << "shoot red" << std::endl;
      game_status_.ShootBullet(red_player);
      break;

    case ci::app::KeyEvent::KEY_UP:
      std::cout << "shoot blue" << std::endl;
      game_status_.ShootBullet(blue_player);
      break;
  }
}


void GameApp::update() {
  game_status_.AdvanceOneFrame();
}

void GameApp::DrawBullets() {
  if (game_status_.GetBulletsInGame().empty()) {
    //std::cout << "is empty" << std::endl;
    return;
  }
  for (Bullet& bullet : game_status_.GetBulletsInGame()) {
    ci::gl::color(ci::Color(bullet.GetColor()));
    ci::gl::drawSolidCircle(bullet.GetPosition(), bullet.GetRadius());
  }
}


} // namespace visualizer

} // namespace finalproject