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
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  
}


} // namespace visualizer

} // namespace finalproject