#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Core/GameObject.h"
#include <SFML/Graphics.hpp>

namespace eke
{
    // Creature decl - "INTERFACE"
    class Creature
    {
    public:
        Creature() {}
        virtual ~Creature() {}
        virtual float GetHealth() const = 0;
        virtual float GetMaxHealth() const = 0;
        virtual sf::RectangleShape *GetBoundingBox() = 0;
    };
} // namespace eke

#endif // __CREATURE_H__