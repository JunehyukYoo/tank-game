#include <visualizer/game_app.h>
#include "core/bullet.h"
#include "core/player.h"

namespace finalproject {
    
namespace visualizer {

GameApp::GameApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void GameApp::setup() {
  auto image_up = ci::loadImage(kTankUpImage);
  auto image_down = ci::loadImage(kTankDownImage);
  auto image_right = ci::loadImage(kTankRightImage);
  auto image_left = ci::loadImage(kTankLeftImage);

  ci::Surface bitmap_up(image_up);
  ci::Surface bitmap_down(image_down);
  ci::Surface bitmap_right(image_right);
  ci::Surface bitmap_left(image_left);

  ci::Area area(0, 0, 512, 492);
  InitializeImageColors(bitmap_up, ci::Color("red"), area);
  InitializeImageColors(bitmap_left, ci::Color("red"), area);
  InitializeImageColors(bitmap_right, ci::Color("red"), area);
  InitializeImageColors(bitmap_down, ci::Color("red"), area);
  
  red_tank_images.insert({Player::UP, ci::gl::Texture2d::create(bitmap_up)});
  red_tank_images.insert({Player::DOWN, ci::gl::Texture2d::create(bitmap_down)});
  red_tank_images.insert({Player::LEFT, ci::gl::Texture2d::create(bitmap_left)});
  red_tank_images.insert({Player::RIGHT, ci::gl::Texture2d::create(bitmap_right)});

  InitializeImageColors(bitmap_up, ci::Color("blue"), area);
  InitializeImageColors(bitmap_left, ci::Color("blue"), area);
  InitializeImageColors(bitmap_right, ci::Color("blue"), area);
  InitializeImageColors(bitmap_down, ci::Color("blue"), area);

  blue_tank_images.insert({Player::UP, ci::gl::Texture2d::create(bitmap_up)});
  blue_tank_images.insert({Player::DOWN, ci::gl::Texture2d::create(bitmap_down)});
  blue_tank_images.insert({Player::LEFT, ci::gl::Texture2d::create(bitmap_left)});
  blue_tank_images.insert({Player::RIGHT, ci::gl::Texture2d::create(bitmap_right)});
  
}

void GameApp::InitializeImageColors(ci::Surface &surface, const ci::Color& color, const ci::Area& area) {
  ci::Surface::Iter iter = surface.getIter(area);
  if (color == ci::Color("red")) {
    while (iter.line()) {
      while (iter.pixel()) {
        iter.r() = 255 - iter.r();
      }
    }
  } else {
    while (iter.line()) {
      while (iter.pixel()) {
        iter.b() = 255 - iter.b();
        iter.g() = 100 - iter.g();
      }
    } 
  }
}

void GameApp::draw() {
  ci::Color background_color(kBackgroundColor);
  ci::gl::clear(background_color);

  Player red_player = game_status_.GetRedPlayer();
  Player blue_player = game_status_.GetBluePlayer();
  
  if (red_player.GetScore() == 10) {
    ci::gl::color(kDefaultColor);
    ci::gl::drawString("Red Player Wins!", glm::vec2((int) kWindowSize/2, (int) kWindowSize/2));
  } else if (blue_player.GetScore() == 10) {
    ci::gl::color(kDefaultColor);
    ci::gl::drawString("Blue Player Wins!", glm::vec2((int) kWindowSize/2, (int) kWindowSize/2));
  } else {
    ci::gl::color(kDefaultColor);
    ci::gl::drawStrokedRect(ci::Rectf(game_status_.kTopLeft, game_status_.kBottomRight));

    ci::gl::color(kDefaultColor);
    ci::gl::drawString("Red Player: " + std::to_string(red_player.GetScore()), game_status_.kRedScoreDisplayLoc);
    ci::gl::drawString("Blue Player: " + std::to_string(blue_player.GetScore()), game_status_.kBlueScoreDisplayLoc);

    //ci::gl::color(red_player.GetColor());
    //ci::gl::drawSolidCircle(red_player.GetPosition(), Player::kTankDimensions);
    glm::vec2 tank_dim_as_vec(Player::kTankDimensions * 2, Player::kTankDimensions * 2);
    ci::gl::Texture2dRef texture_red = red_tank_images.find(red_player.GetDirection())->second;
    ci::Rectf dimensions_red(red_player.GetPosition() - tank_dim_as_vec, red_player.GetPosition() + tank_dim_as_vec);
    ci::gl::draw(texture_red, dimensions_red);

    //ci::gl::color(blue_player.GetColor());
    //ci::gl::drawSolidCircle(blue_player.GetPosition(), Player::kTankDimensions);
    ci::gl::Texture2dRef texture_blue = blue_tank_images.find(blue_player.GetDirection())->second;
    ci::Rectf dimensions_blue(blue_player.GetPosition() - tank_dim_as_vec, blue_player.GetPosition() + tank_dim_as_vec);
    ci::gl::draw(texture_blue, dimensions_blue);

    DrawBullets(); 
    //DrawTankMuzzle(red_player);
    //DrawTankMuzzle(blue_player);
    DrawWalls();
  }
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  Player& red_player = game_status_.GetRedPlayer();
  Player& blue_player = game_status_.GetBluePlayer();
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_w:
      if (game_status_.CanTankMoveInDir(red_player, Player::UP)) {
        red_player.MoveUp(); 
      }
      red_player.SetDirection(Player::UP);
      break;
    case ci::app::KeyEvent::KEY_a:
      if (game_status_.CanTankMoveInDir(red_player, Player::LEFT)) {
        red_player.MoveLeft();
      }
      red_player.SetDirection(Player::LEFT);
      break;
      
    case ci::app::KeyEvent::KEY_s:
      if (game_status_.CanTankMoveInDir(red_player, Player::DOWN)) {
        red_player.MoveDown();
      }
      red_player.SetDirection(Player::DOWN);
      break;

    case ci::app::KeyEvent::KEY_d:
      if (game_status_.CanTankMoveInDir(red_player, Player::RIGHT)) {
        red_player.MoveRight();
      }
      red_player.SetDirection(Player::RIGHT);
      break;

    case ci::app::KeyEvent::KEY_i:
      if (game_status_.CanTankMoveInDir(blue_player, Player::UP)) {
        blue_player.MoveUp();
      }
      blue_player.SetDirection(Player::UP);
      break;

    case ci::app::KeyEvent::KEY_j:
      if (game_status_.CanTankMoveInDir(blue_player, Player::LEFT)) {
        blue_player.MoveLeft();
      }
      blue_player.SetDirection(Player::LEFT);
      break;

    case ci::app::KeyEvent::KEY_k:
      if (game_status_.CanTankMoveInDir(blue_player, Player::DOWN)) {
        blue_player.MoveDown();
      }
      blue_player.SetDirection(Player::DOWN);
      break;

    case ci::app::KeyEvent::KEY_l:
      if (game_status_.CanTankMoveInDir(blue_player, Player::RIGHT)) {
        blue_player.MoveRight();
      }
      blue_player.SetDirection(Player::RIGHT);
      break;
      
    case ci::app::KeyEvent::KEY_SPACE:
      game_status_.ShootBullet(red_player);
      break;

    case ci::app::KeyEvent::KEY_UP:
      game_status_.ShootBullet(blue_player);
      break;
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

void GameApp::DrawTankMuzzle(const Player& player) {
  ci::gl::color(player.GetColor());
  if (player.GetDirection() == Player::UP) {
    glm::vec2 top_left(player.GetPosition().x - Player::kMuzzleWidth / 2, player.GetPosition().y - Player::kMuzzleLength);
    glm::vec2 bottom_right(player.GetPosition().x + Player::kMuzzleWidth / 2, player.GetPosition().y);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
    
  } else if (player.GetDirection() == Player::DOWN) {
    glm::vec2 top_left(player.GetPosition().x - Player::kMuzzleWidth / 2, player.GetPosition().y);
    glm::vec2 bottom_right(player.GetPosition().x + Player::kMuzzleWidth / 2, player.GetPosition().y + Player::kMuzzleLength);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
    
  } else if (player.GetDirection() == Player::LEFT) {
    glm::vec2 top_left(player.GetPosition().x - Player::kMuzzleLength, player.GetPosition().y - Player::kMuzzleWidth / 2);
    glm::vec2 bottom_right(player.GetPosition().x, player.GetPosition().y + Player::kMuzzleWidth / 2);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
    
  } else if (player.GetDirection() == Player::RIGHT) {
    glm::vec2 top_left(player.GetPosition().x, player.GetPosition().y - Player::kMuzzleWidth / 2);
    glm::vec2 bottom_right(player.GetPosition().x + Player::kMuzzleLength, player.GetPosition().y + Player::kMuzzleWidth / 2);
    ci::gl::drawSolidRect(ci::Rectf(top_left, bottom_right));
    
  }
}

void GameApp::DrawWalls() {
  std::vector<std::vector<Wall>> map = game_status_.GetMap().GetWalls();
  if (map.empty()) {
    return;
  }
  ci::gl::color(kDefaultColor);
  for (size_t row = 0; row < map.size(); row++) {
    for (size_t col = 0; col < map[0].size(); col++) {
      Wall wall = map[row][col];
      ci::gl::drawSolidRect(ci::Rectf(wall.top_left_, wall.bottom_right_));
    }
  }
}

} // namespace visualizer

} // namespace finalproject