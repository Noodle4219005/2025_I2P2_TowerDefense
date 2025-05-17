#pragma once
#include "Bullet.hpp"

class RocketBullet : public Bullet
{
private:
    Enemy* target;
    const int kRotateRedian=2*ALLEGRO_PI;
public:
    RocketBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void Update(float deltaTime) override;
    void OnExplode(Enemy* enemy);
};
