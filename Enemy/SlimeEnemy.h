#pragma once
#include "Enemy.hpp"

class SlimeEnemy : public Enemy {
private:
    void OnExplode() override;
public:
    SlimeEnemy(int x, int y);
};

