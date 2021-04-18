#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game_status.h"
#include "core/bullet.h"
#include "core/player.h"

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
  GameStatus game_status_ = GameStatus();
  
  const ci::Color kBorderColor = ci::Color("black");
};

} // namespace visualizer

} // namespace finalproject