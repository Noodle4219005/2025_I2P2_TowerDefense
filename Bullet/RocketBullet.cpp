#include <random>
#include <iostream>

#include "RocketBullet.h"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "Enemy/Enemy.hpp"


RocketBullet::RocketBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent) :
    Bullet("play/bullet-3.png", 150, 3, position, forwardDirection, rotation + ALLEGRO_PI / 2, parent) {}

void RocketBullet::Update(float deltaTime) 
{
    PlayScene* scene=getPlayScene();
    float minDistance=FLT_MAX;
    if (Target) {
        Engine::Point diff = Target->Position - Position;
        if (diff.Magnitude() > CollisionRadius) {
            Target->lockedBullets.erase(m_iterInTarget);
            Target = nullptr;
            m_iterInTarget = std::list<Bullet*>::iterator();
        }
    }
    if (!Target) {
        minDistance=FLT_MAX;
        // Lock the nearest target
        for (auto &it : scene->EnemyGroup->GetObjects()) {
            Engine::Point diff = it->Position - Position;
            if (diff.Magnitude()<minDistance) {
                Target=dynamic_cast<Enemy *>(it);
                minDistance=diff.Magnitude();
            }
        }
        if (Target!=nullptr) {
            Target->lockedBullets.emplace_back(static_cast<Bullet*>(this));
            m_iterInTarget=prev(Target->lockedBullets.end());
        }
    }
    if (Target) {
        Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation = (Target->Position - Position).Normalize();
        float maxRotateRadian = kRotateRedian * deltaTime;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1) cosTheta = 1;
        else if (cosTheta < -1) cosTheta = -1;
        float radian = acos(cosTheta);
        Engine::Point rotation;
        if (abs(radian) <= maxRotateRadian)
            rotation = targetRotation;
        else
            rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
        // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
        Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        Velocity=Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2)).Normalize()*speed;
    }
    Bullet::Update(deltaTime);
}

void RocketBullet::OnExplode(Enemy *enemy) 
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(5, 15);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-2.png", dist(rng), enemy->Position.x, enemy->Position.y));
}
