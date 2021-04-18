#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace finalproject {
    
namespace visualizer {

class GameApp : public ci::app::App {
public:
  GameApp();

  void draw() override;

  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 875;
  const double kMargin = 100;
};

} // namespace visualizer

} // namespace finalproject