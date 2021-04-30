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
  
  void setup() override;
  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;
  
  /** Draws the bullets in the game */
  void DrawBullets();
  
  /** Draws the tank muzzles */
  void DrawTankMuzzle(const Player& player);
  
  /** Draw walls */
  void DrawWalls();
  
  void InitializeImageColors(ci::Surface& surface, const ci::Color& color, const ci::Area& area);

  const double kWindowSize = 700;
  const double kMargin = 100;
  
private:
  const std::string kTankUpImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_up.png";
  const std::string kTankLeftImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_left.png";
  const std::string kTankRightImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_right.png";
  const std::string kTankDownImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_down.png";

  GameStatus game_status_;
  std::unordered_map<Player::Direction, ci::gl::Texture2dRef,  std::hash<int>> red_tank_images;
  //std::unordered_map<Player::Direction, ci::gl::Texture2dRef> blue_tank_images;

  
  const ci::Color kDefaultColor = ci::Color("white");
  const ci::Color kBackgroundColor = ci::Color("black"); 
};

} // namespace visualizer

} // namespace finalproject