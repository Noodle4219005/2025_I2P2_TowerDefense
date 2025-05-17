#ifndef TOOL_H
#define TOOL_H
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class PlayScene;

enum ToolType {
  SHOVEL=0,
  BOMB
};

class Tool : public Engine::Sprite {
protected:
  PlayScene* getPlayScene();
  int m_type=SHOVEL;

public:
  Tool(std::string img);
  void Update(float deltaTime) override;
  void Draw() const override;

  int GetType()
  {
    return m_type;
  }
};
#endif   // TOOL_H
