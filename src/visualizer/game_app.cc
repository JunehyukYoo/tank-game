#include <visualizer/game_app.h>

namespace finalproject {
    
namespace visualizer {

GameApp::GameApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::draw() {}

void GameApp::keyDown(ci::app::KeyEvent event) {}


} // namespace visualizer

} // namespace finalproject