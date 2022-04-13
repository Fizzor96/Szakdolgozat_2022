#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SFML/Graphics.hpp>

namespace eke
{
    class GameObject
    {
    public:
        GameObject() {}
        virtual ~GameObject() {}
        virtual void PollEvents() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual sf::Vector2f GetPosition() const = 0;
    };
} // namespace eke

#endif // __GAMEOBJECT_H__