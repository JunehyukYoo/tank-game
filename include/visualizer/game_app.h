#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game_status.h"

namespace finalproject {
    
namespace visualizer {

class GameApp : public ci::app::App {
public:
  GameApp();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;
  
  void DrawBullets();

  const double kWindowSize = 875;
  const double kMargin = 100;
  
private:
  GameStatus game_status_;
  
  const ci::Color kDefaultColor = ci::Color("white");
  const ci::Color kBackgroundColor = ci::Color("black");
};

} // namespace visualizer

} // namespace finalproject