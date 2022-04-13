#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include <SFML/Graphics.hpp>

#include "Core/Anim.h"
#include "Core/Creature.h"
#include "Core/GameObject.h"
#include "Core/Globals.h"
#include "Core/Hitbox.h"
#include "Core/Projectile.h"
#include "Core/Timer.h"
#include "Objects/Healthbar.h"
#include "Objects/Player.h"

#include <cmath>
#include <math.h>
#include <vector>

namespace eke
{
    class Player;
    class Timer;

    class Warrior : public Creature, GameObject
    {
    public:
        Warrior(eke::Player *target = nullptr);
        Warrior(sf::Vector2f spawnposition, eke::Player *target = nullptr);
        Warrior(float spawnx, float spawny, eke::Player *target = nullptr);
        ~Warrior();

        // Warrior specific
    public:
        void SetHealth(const float &val);
        void Damage(const float &val);
        float GetRegen() const;
        void SetRegen(const float &val);
        void SetTarget(eke::Player *target);
        void DelTarget();
        void SetPosition(const sf::Vector2f &pos);
        void SetPosition(const float &posx, const float &posy);
        std::vector<eke::Projectile *> *GetProjectiles();
        void RemoveProjectileFromNthPlace(int i);

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
        sf::RectangleShape *GetBoundingBox() override;

    private:
        bool shootIsRdy;
        const char *defprojpath;
        float spritescale, maxhealth, health, velocity, shootinterval, regen, projectilevelocity, mindamage, maxdamage;
        eke::Timer *shootTimer, *regenTimer;
        sf::Sprite sprite;
        sf::Texture texture;
        eke::Healthbar *healthbar;
        eke::Anim *animation;
        eke::Hitbox *hitbox;
        eke::Player *target;
        std::vector<eke::Projectile *> projectiles;

    private:
        void Shoot();
        void Movement();
        float CalculateDamage();

    private:
        void InitDefaultValues();
        void InitWarriorBody(sf::Vector2f spawnposition);
        void InitWarriorBody(float spawnx, float spawny);
        void InitShoot();
        void InitRegen();

    private:
        void UpdateWarriorBody();
        void UpdateTimers();
        void UpdateProjectiles();

    private:
        void DrawProjectiles();
        void DrawWarriorBody();

    public:
        Warrior(const eke::Warrior &other) = delete;
        Warrior(eke::Warrior &&other) = delete;
        Warrior &operator=(const eke::Warrior &other) = delete;
        Warrior &operator=(eke::Warrior &&other) = delete;
    };
} // namespace eke

#endif // __WARRIOR_H__