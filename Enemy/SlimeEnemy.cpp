#include <iostream>

#include "SlimeEnemy.h"
#include "SmallSlimeEnemy.h"
#include "Scene/PlayScene.hpp"

SlimeEnemy::SlimeEnemy(int x, int y) : 
  Enemy("play/enemy-10.png", x, y, 10, 20, 20, 15) {
}

void SlimeEnemy::OnExplode() 
{
    Enemy::OnExplode();
    Enemy* enemy;
    std::cout<<Position.x<<" "<<Position.y<<std::endl;
    const Engine::Point SpawnCoordinate = Engine::Point(Position.x, Position.y);
    for (int i=0; i<3; ++i) {
        getPlayScene()->EnemyGroup->AddNewObject(enemy = new SmallSlimeEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
        enemy->UpdatePath(getPlayScene()->mapDistance);
        enemy->Update(1.*i/10);
    }
}
