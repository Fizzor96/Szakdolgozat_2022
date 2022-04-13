#ifndef __HITBOX_H__
#define __HITBOX_H__

#include <SFML/Graphics.hpp>

#include "Globals.h"

namespace eke
{
    // Helper class to easily create rectangle that represents a hitbox of any obj
    class Hitbox : public GameObject
    {
    public:
        Hitbox();
        Hitbox(const sf::Vector2f &size);
        Hitbox(const float &width, const float &height);
        ~Hitbox();

        // Inherited
    public:
        void Update() override;
        void PollEvents() override;
        void Draw() override;
        sf::Vector2f GetPosition() const override;

    public:
        void SetSize(const sf::Vector2f &size);
        void SetSize(const float &widht, const float &height);
        sf::Vector2f GetSize() const;
        void SetPosition(const sf::Vector2f &pos);
        void SetPosition(const float &x, const float &y);
        sf::RectangleShape *GetDrawable();

    private:
        sf::RectangleShape *hitbox;
    };
} // namespace eke

#endif // __HITBOX_H__