#include "SmallSlimeEnemy.h"

SmallSlimeEnemy::SmallSlimeEnemy(int x, int y) : 
  Enemy("play/enemy-1.png", x, y, 1, 727/2, 1, 5) 
{
    Enemy::Tint=al_map_rgb(255, 0, 0);
}
