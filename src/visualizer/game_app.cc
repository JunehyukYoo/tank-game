#include <visualizer/game_app.h>

namespace finalproject {
    
namespace visualizer {

GameApp::GameApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::draw() {
  ci::Color background_color("white");
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color(game_status_.kBorderColor));
  ci::gl::drawStrokedRect(ci::Rectf(game_status_.kTopLeft, game_status_.kBottomRight));
  
  ci::gl::color(game_status_.GetRedPlayer().GetColor());
  ci::gl::drawSolidCircle(game_status_.GetRedPlayer().GetCurrPosition(), Player::kTankDimensions);
  
  ci::gl::color(game_status_.GetBluePlayer().GetColor());
  ci::gl::drawSolidCircle(glm::vec2(590, 590), Player::kTankDimensions);
  
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

    case ci::app::KeyEvent::KEY_COLON:
      game_status_.ShootBullet(blue_player);
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