#ifndef __FIRE_H__
#define __FIRE_H__

#include <SFML/Graphics.hpp>

#include "Core/Anim.h"
#include "Core/Globals.h"

namespace eke
{
    class Fire
    {
    private:
        eke::Anim *anim;
        sf::Texture *texture;
        sf::Sprite *sprite;

    public:
        Fire();
        ~Fire();
        void SetPosition(const float &posx, const float &posy);
        void SetPosition(const sf::Vector2f &pos);
        void SetScale(const sf::Vector2f &scale);
        void SetScale(const float &scalex, const float &scaley);
        sf::FloatRect GetGlobalBounds() const;
        void PollEvents();
        void Update();
        void Draw();
    };
} // namespace eke

#endif // __FIRE_H__