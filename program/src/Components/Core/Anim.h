#ifndef ANIM_HPP
#define ANIM_HPP 1

#include <SFML/Graphics.hpp>

namespace eke
{
    class Anim
    {
    public:
        Anim(sf::Texture *texture, const unsigned int rows, unsigned int cols, const float switchTime);
        Anim(sf::Texture *texture, const sf::Vector2u imgCount, float switchTime);
        ~Anim();
        // This is required to show the correct subpicture
        sf::IntRect GetAnimRect() const;
        // Switching time between rectangles, 5.f means 5 seconds
        void SetSwitchTime(const float &time);
        // This is necessary if we have a spritesheet with a buch of small pictures in it, to "switch" animation instead of creating a new animation object
        void SetAnimationRow(const unsigned int &row);
        // MUST HAVE to call this in order to update our rectangle
        void Update(const int &row, const float &deltatime);

    public:
        sf::IntRect textureRect;

    private:
        sf::Vector2u imgCount;
        sf::Vector2u currImg;
        float totalTime;
        float switchTime;

    public:
        Anim() = delete;
        Anim(const Anim &other) = delete;
        Anim(Anim &&other) = delete;
        Anim &operator=(const Anim &other) = delete;
        Anim &operator=(Anim &&other) = delete;
    };
}

#endif