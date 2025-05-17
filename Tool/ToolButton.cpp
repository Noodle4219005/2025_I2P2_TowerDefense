#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "ToolButton.h"

PlayScene* ToolButton::getPlayScene() {
  return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

ToolButton::ToolButton(std::string img, std::string imgIn, Engine::Sprite _tool, float x, float y) : 
  ImageButton(img, imgIn, x, y), tool(_tool) {}

void ToolButton::Update(float deltaTime) {
  ImageButton::Update(deltaTime);
  Enabled = true;
  tool.Tint = al_map_rgba(255, 255, 255, 255);
}
void ToolButton::Draw() const {
  ImageButton::Draw();
  tool.Draw();
}
