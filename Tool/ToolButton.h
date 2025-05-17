#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H
#include <string>

#include "Engine/Sprite.hpp"
#include "UI/Component/ImageButton.hpp"

class PlayScene;

class ToolButton : public Engine::ImageButton 
{
protected:
    PlayScene *getPlayScene();

public:
    Engine::Sprite tool;
    ToolButton(std::string img, std::string imgIn, Engine::Sprite tool, float x, float y);
    void Update(float deltaTime) override;
    void Draw() const override;
};
#endif   // TOOLBUTTON_H
