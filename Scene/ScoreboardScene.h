#ifndef SCOREBOARD_SCENE_H
#define SCOREBOARD_SCENE_H
#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"

class ScoreboardScene final : public Engine::IScene
{
private:
  struct _Score {
    std::string name;
    double score;
    std::string date;
  };
  typedef struct _Score Score;
  std::vector<Score> m_scores;
  Group* scoreGroup;
  std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
  const int kScoresPerPage=5;
  int page=0;
  int lineCount=0;

public:
  explicit ScoreboardScene() = default;
  void Initialize() override;
  void Terminate() override;
  void UpdateScene();
  void BackOnClick();
  void NextOnClick();
  void PrevOnClick();
};

#endif   // SCOREBOARD_SCENE_H
