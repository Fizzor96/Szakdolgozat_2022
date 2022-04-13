#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Anim.h"
#include "GameObject.h"
#include "Globals.h"
#include "Hitbox.h"

#include <cmath>
#include <math.h>

#include <SFML/Graphics.hpp>

namespace eke
{
    class Hitbox;
    // Basic projectile class with the possibility of change
    class Projectile : public GameObject
    {
    public:
        Projectile(const char *texturepath, const float &rows, const float &cols, const float &switchtime, const sf::Vector2f &org, const float &rot, const float &damage, const float &velo);
        virtual ~Projectile();
        sf::FloatRect GetGlobalBounds() const;
        sf::RectangleShape *GetBoundingBox();
        sf::Vector2f GetPosition() const override;
        void PollEvents() override;
        void Update() override;
        void Draw() override;
        float GetDuration() const;
        void SetColor(const sf::Color &color);
        float GetDamage() const;

    private:
        sf::Sprite *sprite;
        sf::Texture *texture;
        eke::Hitbox *hitbox;
        eke::Anim *anim;
        float damage, velocity, dirx, diry;
        float lifetime; // in seconds 5.f is 5 seconds!
    };
} // namespace eke

#endif // __PROJECTILE_H__