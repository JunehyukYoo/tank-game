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
  ci::gl::drawSolidRect(ci::Rectf(glm::vec2(game_status_.GetRedPlayer().GetCurrPosition()),
                                  glm::vec2(game_status_.GetRedPlayer().GetCurrPosition().x + 50,
                                            game_status_.GetRedPlayer().GetCurrPosition().y + 50)));
  
  ci::gl::color(game_status_.GetBluePlayer().GetColor());
  ci::gl::drawSolidRect(ci::Rectf(game_status_.GetBluePlayer().GetCurrPosition(),
                                  glm::vec2(game_status_.GetBluePlayer().GetCurrPosition().x - 5,
                                            game_status_.GetBluePlayer().GetCurrPosition().y - 5)));
  DrawBullets();
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w:
      game_status_.GetRedPlayer().MoveUp();
      break;

    case ci::app::KeyEvent::KEY_a:
      game_status_.GetRedPlayer().MoveLeft();
      break;
      
    case ci::app::KeyEvent::KEY_s:
      game_status_.GetRedPlayer().MoveDown();
      break;

    case ci::app::KeyEvent::KEY_d:
      game_status_.GetRedPlayer().MoveRight();
      break;

    case ci::app::KeyEvent::KEY_i:
      game_status_.GetBluePlayer().MoveUp();
      break;

    case ci::app::KeyEvent::KEY_j:
      game_status_.GetBluePlayer().MoveLeft();
      break;

    case ci::app::KeyEvent::KEY_k:
      game_status_.GetBluePlayer().MoveDown();
      break;

    case ci::app::KeyEvent::KEY_l:
      game_status_.GetBluePlayer().MoveRight();
      break;
      
    case ci::app::KeyEvent::KEY_SPACE:
      game_status_.ShootBullet(game_status_.GetRedPlayer());

    case ci::app::KeyEvent::KEY_COLON:
      game_status_.ShootBullet(game_status_.GetBluePlayer());
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