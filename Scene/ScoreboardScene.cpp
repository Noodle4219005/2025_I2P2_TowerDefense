#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "ScoreboardScene.h"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

using std::ofstream;

void ScoreboardScene::Initialize()
{
  std::ifstream ifs;
  std::ofstream ofs;
  std::string name;
  double score;
  int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
  int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
  int halfW = w / 2;
  int halfH = h / 2;
  Engine::ImageButton* btn;

  page=0;
  lineCount=0;
  scoreGroup=new Group{};
  // FIXME: file invalid check
  m_scores.clear();
  ifs.open("./Resource/scoreboard.txt");
  while (ifs>>name>>score) {
    m_scores.emplace_back(Score{name, score});
    ++lineCount;
  }
  ifs.close();
  // sort and write back to the file
  std::sort(m_scores.begin(), m_scores.end(), [](Score A, Score B) { return A.score>B.score;  });
  ofs.open("./Resource/scoreboard.txt", ofstream::trunc|ofstream::out);
  for (auto& i : m_scores) {
    ofs<<i.name<<" "<<static_cast<int>(i.score)<<std::endl;
  }
  ofs.close();
  
  AddNewObject(scoreGroup);
  
  AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH - 350, 0, 255, 0, 255, 0.5, 0.5));

  // initialize buttons
  btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2, 400, 100);
  btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this));
  AddNewControlObject(btn);
  AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

  btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 - 500, halfH * 3 / 2, 400, 100);
  btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this));
  AddNewControlObject(btn);
  AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

  btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 + 500, halfH * 3 / 2, 400, 100);
  btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this));
  AddNewControlObject(btn);
  AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

  UpdateScene();

  // Not safe if release resource while playing, however we only free while change scene, so it's fine.
  bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}

void ScoreboardScene::UpdateScene()
{
  int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
  int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
  int halfW = w / 2;
  int halfH = h / 2;
  std::ifstream ifs;
  std::string name;
  int score;
  int offset;
  const int kScoreDisplayLowerBound=Engine::GameEngine::GetInstance().GetScreenSize().y / 4;
  const int kScoreDisplayHeight=Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

  ifs.open("./Resource/scoreboard.txt");
  ifs.clear();
  ifs.seekg(0);
  for (int i=0; (i<kScoresPerPage*page)&&(ifs>>name>>score); ++i);
  for (int i=0; (i<kScoresPerPage)&&(ifs>>name>>score); ++i) {
    scoreGroup->AddNewObject(new Engine::Label(name, "pirulen.ttf", 36,
                                              halfW*1/2, kScoreDisplayLowerBound+kScoreDisplayHeight/kScoresPerPage*i,
                                              0, 255, 0, 255, 0.5, 0.5));
    scoreGroup->AddNewObject(new Engine::Label(std::to_string(score), "pirulen.ttf", 36,
                                              halfW*3/2, kScoreDisplayLowerBound+kScoreDisplayHeight/kScoresPerPage*i,
                                              0, 255, 0, 255, 0.5, 0.5));
  }
  for (auto& i : scoreGroup->GetObjects()) {
    i->Draw();
  }
  ifs.close();
}

void ScoreboardScene::Terminate()
{
  for (auto& i : scoreGroup->GetObjects()) {
    scoreGroup->RemoveObject(i->GetObjectIterator());
  }
  AudioHelper::StopSample(bgmInstance);
  bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
  IScene::Terminate();
}

void ScoreboardScene::BackOnClick()
{
  Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreboardScene::NextOnClick()
{
  for (auto& i : scoreGroup->GetObjects()) {
    scoreGroup->RemoveObject(i->GetObjectIterator());
  }
  if (kScoresPerPage*(page+1)<lineCount) ++page;
  UpdateScene();
}

void ScoreboardScene::PrevOnClick()
{
  for (auto& i : scoreGroup->GetObjects()) {
    scoreGroup->RemoveObject(i->GetObjectIterator());
  }
  if (kScoresPerPage*page>0) --page;
  UpdateScene();
}
