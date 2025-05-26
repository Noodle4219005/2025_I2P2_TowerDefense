#include <functional>
#include <string>
#include <fstream>
#include <chrono>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/InputBox.h"
#include "WinScene.hpp"

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");

    inputBox=InputBox(halfW-250, halfH-50, 100, 500);

    // Handle the user score file
    // FIXME: file invalid check
    std::ifstream ifs;
    string name, date;
    double score;
    _lineCount=0;
    ifs.open("./Resource/scoreboard.txt");
    while (ifs>>name>>score>>date) {
        ++_lineCount;
    }
    ifs.close();
    inputBox.SetValue(name);
}
void WinScene::Terminate() 
{
    // TODO: Delete the last input and plugin the input that inputBox have
    std::ifstream ifs;
    std::ofstream ofs;
    ifs.open("./Resource/scoreboard.txt");
    std::list<std::tuple<string, double, string>> scores;
    for (int i=0; i<_lineCount; ++i) {
        string name, date;
        double score;
        ifs>>name>>score>>date;
        scores.emplace_back(name, score, date);
    }
    ofs.open("./Resource/scoreboard.txt", std::ofstream::trunc|std::ofstream::out);
    for (int i=0; i<_lineCount-1; ++i) {
        auto [name, score, date]=scores.front();
        ofs<<name<<" "<<score<<" "<<date<<std::endl;
        scores.pop_front();
    }
    auto [name, score, date]=scores.front();
    ofs<<inputBox.GetValue()<<" "<<score<<" "<<date<<std::endl;
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}

void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}

void WinScene::Draw() const
{
    IScene::Draw();
    inputBox.Draw();
}

void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void WinScene::OnKeyDown(int key)
{
    inputBox.UpdateKey(key);
}
