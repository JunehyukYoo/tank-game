#include <visualizer/game_app.h>

namespace finalproject {
    
namespace visualizer {

GameApp::GameApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::draw() {
  ci::Color background_color("white");
  ci::gl::clear(background_color);
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  
}


} // namespace visualizer

} // namespace finalproject