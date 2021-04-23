#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game_status.h"

namespace finalproject {
    
namespace visualizer {
    
/** The application for the Tank Game */
class GameApp : public ci::app::App {
public:
  GameApp();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;
  
  /** Draws the bullets in the game */
  void DrawBullets();
  
  /** Draws the tank muzzles */
  void DrawTankMuzzle(const Player& player);
  
  void DrawWalls();

  const double kWindowSize = 700;
  const double kMargin = 100;
  
private:
  GameStatus game_status_;
  
  const ci::Color kDefaultColor = ci::Color("white");
  const ci::Color kBackgroundColor = ci::Color("black");
};

} // namespace visualizer

} // namespace finalproject