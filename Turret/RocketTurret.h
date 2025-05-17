#pragma once
#include "Turret.hpp"

class RocketTurret : public Turret {
public:
    static const int Price;
    RocketTurret(float x, float y);
    void CreateBullet() override;
};
