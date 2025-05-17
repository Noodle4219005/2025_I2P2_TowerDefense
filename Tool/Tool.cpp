#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Scene/PlayScene.hpp"
#include "Tool.h"

PlayScene* Tool::getPlayScene()
{
  return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Tool::Tool(std::string imgBase) : Engine::Sprite(imgBase, 0., 0.) {}

void Tool::Update(float deltaTime)
{
  Sprite::Update(deltaTime);
  PlayScene* scene = getPlayScene();
}

void Tool::Draw() const 
{
  Sprite::Draw();
}
