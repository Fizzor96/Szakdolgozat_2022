#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

namespace eke
{
    // AABB (Axis-Aligned Bounding Box) collision, cuz it's EZ
    // Must have to set the origin to the center of the objects!!
    class Collision
    {
    public:
        // Check the collision between 2 objects, the second one will move with the velo of the first multiplied by push
        // Make it static cuz we don't want to instantiate this class to test collision independently from any object therefore def ctor, copy and move ctors are deleted with belonging operators
        static bool CheckColl(sf::RectangleShape *first, sf::RectangleShape *second, float thrust);

    public:
        ~Collision() = delete;
        Collision() = delete;
        Collision(const Collision &other) = delete;
        Collision(Collision &&other) = delete;
        Collision &operator=(const Collision &other) = delete;
        Collision &operator=(Collision &&other) = delete;
    };
} // namespace eke

#endif // __COLLISION_H__