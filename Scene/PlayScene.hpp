#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"

class Turret;
class Tool;
namespace Engine {
  class Group;
  class Image;
  class Label;
  class Sprite;
}   // namespace Engine

class PlayScene final : public Engine::IScene {
private:
  enum TileType {
    TILE_DIRT,
    TILE_FLOOR,
    TILE_OCCUPIED,
  };
  ALLEGRO_SAMPLE_ID bgmId;
  std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
  const std::vector<std::pair<int, int>> kMoves={{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

protected:
  const int kFullLives=10;
  int lives;
  int money;
  int SpeedMult;

public:
  static bool DebugMode;
  static const std::vector<Engine::Point> directions;
  static const int MapWidth, MapHeight;
  static const int BlockSize;
  static const float DangerTime;
  static const Engine::Point SpawnGridPoint;
  static const Engine::Point EndGridPoint;
  static const std::vector<int> code[2];
  int MapId;
  float ticks;
  float deathCountDown;
  // Map tiles.
  Group* TileMapGroup;
  Group* GroundEffectGroup;
  Group* DebugIndicatorGroup;
  Group* BulletGroup;
  Group* TowerGroup;
  Group* EnemyGroup;
  Group* EffectGroup;
  Group* UIGroup;
  Engine::Label* UIMoney;
  Engine::Label* UILives;
  Engine::Image* imgTarget;
  Engine::Sprite* dangerIndicator;
  Turret* preview;
  Tool* toolPreview;
  std::vector<std::vector<TileType>> mapState;
  std::vector<std::vector<int>> mapDistance;
  std::list<std::pair<int, float>> enemyWaveData;
  std::list<int> keyStrokes;
  static Engine::Point GetClientSize();
  explicit PlayScene() = default;
  void Initialize() override;
  void Terminate() override;
  void Update(float deltaTime) override;
  void Draw() const override;
  void OnMouseDown(int button, int mx, int my) override;
  void OnMouseMove(int mx, int my) override;
  void OnMouseUp(int button, int mx, int my) override;
  void OnKeyDown(int keyCode) override;
  void Hit();
  int GetMoney() const;
  void EarnMoney(int money);
  void ReadMap();
  void ReadEnemyWave();
  void ConstructUI();
  void UIBtnClicked(int id);
  bool CheckSpaceValid(int x, int y);
  std::vector<std::vector<int>> CalculateBFSDistance();
  // void ModifyReadMapTiles();
};
#endif   // PLAYSCENE_HPP

class RandomNameGenerator
{
private:

  RandomNameGenerator()
  {
    std::srand(std::time({}));
  };

  const std::vector<std::string> m_adjList=
  {
    "furry","ferocious","dangerous","poisonous","tame","agile","clever","aggressive","tiny","domestic","wild","herbivorous","carnivorous","Adorable","Aggressive","Agile","Beautiful","Bossy","Candid","Carnivorous","Clever","Cold","Cold-Blooded","Colorful","Cuddly","Curious","Cute","Dangerous","Deadly","Domestic","Dominant","Energetic","Fast","Feisty","Ferocious","Fierce","Fluffy","Friendly","Furry","Fuzzy","Grumpy","Hairy","Heavy","Herbivorous","Jealous","Large","Lazy","Loud","Lovable","Loving","Malicious","Maternal","Mean","Messy","Nocturnal","Noisy","Nosy","Picky","Playful","Poisonous","Quick","Rough","Sassy","Scaly","Short","Shy","Slimy","Slow","Small","Smart","Smelly","Soft","Spikey","Stinky","Strong","Stubborn","Submissive","Tall","Tame","Tenacious","Territorial","Tiny","Vicious","Warm","Wild"
  };

  const std::vector<std::string> m_nameList=
  {
    "Aardvark", "Albatross", "Alligator", "Alpaca", "Ant", "Anteater", "Antelope", "Ape", "Armadillo", "Donkey", "Baboon", "Badger", "Barracuda", "Bat", "Bear", "Beaver", "Bee", "Bison", "Boar", "Buffalo", "Butterfly", "Camel", "Capybara", "Caribou", "Cassowary", "Cat", "Caterpillar", "Cattle", "Chamois", "Cheetah", "Chicken", "Chimpanzee", "Chinchilla", "Chough", "Clam", "Cobra", "Cockroach", "Cod", "Cormorant", "Coyote", "Crab", "Crane", "Crocodile", "Crow", "Curlew", "Deer", "Dinosaur", "Dog", "Dogfish", "Dolphin", "Dotterel", "Dove", "Dragonfly", "Duck", "Dugong", "Dunlin", "Eagle", "Echidna", "Eel", "Eland", "Elephant", "Elk", "Emu", "Falcon", "Ferret", "Finch", "Fish", "Flamingo", "Fly", "Fox", "Frog", "Gaur", "Gazelle", "Gerbil", "Giraffe", "Gnat", "Gnu", "Goat", "Goldfinch", "Goldfish", "Goose", "Gorilla", "Goshawk", "Grasshopper", "Grouse", "Guanaco", "Gull", "Hamster", "Hare", "Hawk", "Hedgehog", "Heron", "Herring", "Hippopotamus", "Hornet", "Horse", "Human", "Hummingbird", "Hyena", "Ibex", "Ibis", "Jackal", "Jaguar", "Jay", "Jellyfish", "Kangaroo", "Kingfisher", "Koala", "Kookabura", "Kouprey", "Kudu", "Lapwing", "Lark", "Lemur", "Leopard", "Lion", "Llama", "Lobster", "Locust", "Loris", "Louse", "Lyrebird", "Magpie", "Mallard", "Manatee", "Mandrill", "Mantis", "Marten", "Meerkat", "Mink", "Mole", "Mongoose", "Monkey", "Moose", "Mosquito", "Mouse", "Mule", "Narwhal", "Newt", "Nightingale", "Octopus", "Okapi", "Opossum", "Oryx", "Ostrich", "Otter", "Owl", "Oyster", "Panther", "Parrot", "Partridge", "Peafowl", "Pelican", "Penguin", "Pheasant", "Pig", "Pigeon", "Pony", "Porcupine", "Porpoise", "Quail", "Quelea", "Quetzal", "Rabbit", "Raccoon", "Rail", "Ram", "Rat", "Raven", "Red deer", "Red panda", "Reindeer", "Rhinoceros", "Rook", "Salamander", "Salmon", "Sand Dollar", "Sandpiper", "Sardine", "Scorpion", "Seahorse", "Seal", "Shark", "Sheep", "Shrew", "Skunk", "Snail", "Snake", "Sparrow", "Spider", "Spoonbill", "Squid", "Squirrel", "Starling", "Stingray", "Stinkbug", "Stork", "Swallow", "Swan", "Tapir", "Tarsier", "Termite", "Tiger", "Toad", "Trout", "Turkey", "Turtle", "Viper", "Vulture", "Wallaby", "Walrus", "Wasp", "Weasel", "Whale", "Wildcat", "Wolf", "Wolverine", "Wombat", "Woodcock", "Woodpecker", "Worm", "Wren", "Yak", "Zebra"
  };

public:

  RandomNameGenerator(RandomNameGenerator const&)=delete;

  static RandomNameGenerator& GetInstance()
  {
    static RandomNameGenerator INSTANCE;
    return INSTANCE;
  }

  std::string Generate()
  {
    int randValue=std::rand();
    return m_adjList[randValue%m_adjList.size()]+"-"+m_nameList[randValue%m_nameList.size()];
  }
};
