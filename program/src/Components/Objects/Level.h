#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "Core/BoundaryBox.h"
#include "Core/Collision.h"
#include "Core/GameObject.h"
#include "Core/Globals.h"
#include "Core/Timer.h"
#include "NPC/Warrior.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace eke
{
    class Player;
    class Warrior;
    class BoundaryBox;
    class Level : public GameObject
    {
    public:
        Level();
        ~Level();
        void PollEvents() override;
        void Update() override;
        void Draw() override;

    public:
        void AddWarrior();
        void Restart();
        eke::Player *GetPlayerInst();
        bool IsPlayerAlive();

    private:
        // Map
        float mapscale;
        std::vector<eke::BoundaryBox *> boundaryboxes;
        sf::Texture texture;
        sf::Sprite map;
        // GameObjects
        // Player
        eke::Player *player;
        // Enemies
        eke::Timer *enemyGenTimer;
        std::vector<eke::Warrior *> warriors;

    private:
        void InitMap();
        void InitMapEdges();
        void InitTimers();
        void InitPlayer();

    private:
        void UpdateMap();
        void UpdatePlayer();
        void UpdateTimers();
        void UpdateEnemies();

    private:
        void DrawMap();
        void DrawMapEdges();
        void DrawPlayer();
        void DrawEnemies();

    private:
        void CheckEnemyCollisions();
        void CheckProjectileIntersections();

    private:
        sf::Vector2f GetPosition() const override;
    };
} // namespace eke

#endif // __LEVEL_H__