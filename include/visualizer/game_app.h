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
  
  /** Draws the tank muzzles when not using textures */
  void DrawTankMuzzle(const Player& player);
  
  /** Draw walls */
  void DrawWalls();
  
  /**
   * Initializes the images with special coloring.
   * @param surface The surface/image to alter the color of.
   * @param color The color to alter to.
   * @param area The dimensions of the image.
   */
  void InitializeImageColors(ci::Surface& surface, const ci::Color& color, const ci::Area& area);

  const double kWindowSize = 700;
  const double kMargin = 100;
  
private:
  /** Tank image paths */
  const std::string kTankUpImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_up.png";
  const std::string kTankLeftImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_left.png";
  const std::string kTankRightImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_right.png";
  const std::string kTankDownImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/tanks/tank_down.png";
  const std::string kWallUncrackedImage = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/walls/wall_uncracked.jpg";
  const std::string kWallCracked1Image = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/walls/wall_cracked_1.jpg";
  const std::string kWallCracked2Image = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/walls/wall_cracked_2.jpg";
  const std::string kWallCracked3Image = "/Users/s200808/Documents/Cinder/my-projects/final-project-JunehyukYoo/data/walls/wall_cracked_3.jpg";

  GameStatus game_status_;
  std::unordered_map<Player::Direction, ci::gl::Texture2dRef,  std::hash<int>> red_tank_images;
  std::unordered_map<Player::Direction, ci::gl::Texture2dRef, std::hash<int>> blue_tank_images;
  std::unordered_map<size_t, ci::gl::Texture2dRef> wall_images;


  const ci::Color kDefaultColor = ci::Color("white");
  const ci::Color kBackgroundColor = ci::Color("black"); 
};

} // namespace visualizer

} // namespace finalproject