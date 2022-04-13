#ifndef __CANDLE_H__
#define __CANDLE_H__

#include <SFML/Graphics.hpp>

#include "Core/Anim.h"
#include "Core/Globals.h"

namespace eke
{
    class Candle
    {
    private:
        eke::Anim *anim;
        sf::Texture *texture;
        sf::Sprite *sprite;

    public:
        Candle();
        ~Candle();
        void SetPosition(const float &posx, const float &posy);
        void SetPosition(const sf::Vector2f &pos);
        sf::Vector2f GetPosition() const;
        void SetScale(const sf::Vector2f &scale);
        void SetScale(const float &scalex, const float &scaley);
        sf::FloatRect GetGlobalBounds() const;
        void PollEvents();
        void Update();
        void Draw();
    };
} // namespace eke

#endif // __CANDLE_H__