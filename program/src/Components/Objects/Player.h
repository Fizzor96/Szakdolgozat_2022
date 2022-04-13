#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Core/Anim.h"
#include "Core/Camera.h"
#include "Core/Creature.h"
#include "Core/Globals.h"
#include "Core/Hitbox.h"
#include "Core/Projectile.h"
#include "Core/Timer.h"

#include "Healthbar.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <math.h>
#include <string>
#include <vector>

namespace eke
{
    class Projectile;
    class Healthbar;
    class Camera;
    class Timer;
    class Hitbox;

    // Class that represents our player with following camera and healthbar
    class Player : public Creature, GameObject
    {
    public:
        Player();
        Player(const sf::Vector2f &spawnposition);
        Player(const float &spawnx, const float &spawny);
        virtual ~Player();

        // Player specific
    public:
        void SetPosition(const sf::Vector2f &position);
        void SetPosition(const float &posx, const float &posy);
        void SetHealth(const float &val);
        void Damage(float val);
        float GetRegen() const;
        void SetRegen(const float &val);
        float GetVelocity() const;
        void SetVelocity(const float &val);
        std::vector<eke::Projectile *> *GetProjectiles();
        void RemoveProjectileFromNthPlace(int i);
        void Reset();

        // Inherited from GameObject
    public:
        void PollEvents() override;
        void Update() override;
        void Draw() override;
        sf::Vector2f GetPosition() const override;

        // Inherited from Creature
    public:
        float GetHealth() const override;
        float GetMaxHealth() const override;
        sf::RectangleShape *GetBoundingBox();

    private:
        const char *defprojpath;
        bool shootIsRdy;
        float spritescale, maxhealth, health, velocity, shootinterval, regen, projectilevelocity, mindamage, maxdamage;
        eke::Timer *shootTimer, *regenTimer;
        sf::Sprite sprite;
        sf::Texture texture;
        eke::Anim *animation;
        eke::Camera *cam;
        eke::Hitbox *hitbox;
        eke::Healthbar *healthbar;
        std::vector<eke::Projectile *> projectiles;

    private:
        void Shoot();
        void Movement();
        float CalculateDamage();

    private:
        void InitDefaultValues();
        void InitPlayerBody(const sf::Vector2f &spawnpos);
        void InitRegen();
        void InitShoot();

    private:
        void UpdatePlayerBody();
        void UpdateCamera();
        void UpdateTimers();
        void UpdateProjectiles();

    private:
        void DrawProjectiles();
        void DrawPlayerBody();

    public:
        Player(const eke::Player &other) = delete;
        Player(eke::Player &&other) = delete;
        Player &operator=(const eke::Player &other) = delete;
        Player &operator=(eke::Player &&other) = delete;
    };
}

#endif // __PLAYER_H__