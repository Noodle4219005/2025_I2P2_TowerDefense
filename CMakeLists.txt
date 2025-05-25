cmake_minimum_required(VERSION 3.27)
project(2025_I2P2_TowerDefense)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(Resource)
include_directories("Resource/audios")
include_directories("Resource/fonts")
include_directories("Resource/images")

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2025_I2P2_TowerDefense
    Bullet/Bullet.cpp
    Bullet/Bullet.hpp
    Bullet/FireBullet.cpp
    Bullet/FireBullet.hpp
    Bullet/LaserBullet.cpp
    Bullet/LaserBullet.hpp

    Enemy/Enemy.cpp
    Enemy/Enemy.hpp
    Enemy/SoldierEnemy.cpp
    Enemy/SoldierEnemy.hpp
    Enemy/TankEnemy.cpp
    Enemy/TankEnemy.hpp 
    "Enemy/PlaneEnemy.cpp" 
    "Enemy/PlaneEnemy.h"

    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    
    Scene/LoseScene.cpp
    Scene/LoseScene.hpp
    Scene/PlayScene.cpp
    Scene/PlayScene.hpp
    Scene/SettingsScene.cpp
    Scene/SettingsScene.hpp
    Scene/StageSelectScene.cpp
    Scene/StageSelectScene.hpp
    Scene/StartScene.cpp
    Scene/StartScene.h
    Scene/WinScene.cpp
    Scene/WinScene.hpp
    "Scene/ScoreboardScene.cpp"
    "Scene/ScoreboardScene.h"

    Turret/LaserTurret.cpp
    Turret/LaserTurret.hpp
    Turret/MachineGunTurret.cpp
    Turret/MachineGunTurret.hpp
    Turret/Turret.cpp
    Turret/Turret.hpp
    Turret/TurretButton.cpp
    Turret/TurretButton.hpp
     
     

    UI/Animation/DirtyEffect.cpp
    UI/Animation/DirtyEffect.hpp
    UI/Animation/ExplosionEffect.cpp
    UI/Animation/ExplosionEffect.hpp
    UI/Animation/Plane.cpp
    UI/Animation/Plane.hpp

    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp

    "Tool/ToolButton.h"
    "Tool/ToolButton.cpp" 
    "Tool/Tool.h"
    "Tool/Tool.cpp"
    "Tool/Shovel.cpp"
    "Tool/Shovel.h"

    main.cpp
 "Bullet/RocketBullet.cpp" "Bullet/RocketBullet.h" "Turret/RocketTurret.cpp" "Turret/RocketTurret.h" "Enemy/SlimeEnemy.h"  "Enemy/SmallSlimeEnemy.h" "Enemy/SlimeEnemy.cpp" "Enemy/SmallSlimeEnemy.cpp" "UI/Component/InputBox.cpp" "UI/Component/InputBox.h")

find_package(allegro CONFIG REQUIRED)
target_link_libraries(2025_I2P2_TowerDefense Allegro::allegro Allegro::allegro_main Allegro::allegro_font Allegro::allegro_dialog 
                      Allegro::allegro_primitives Allegro::allegro_image Allegro::allegro_ttf 
                      Allegro::allegro_audio Allegro::allegro_acodec)