#ifndef __BOUNDARYBOX_H__
#define __BOUNDARYBOX_H__

#include "Collision.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace eke
{
    // Helper class to create invisible walls
    class BoundaryBox
    {

    public:
        explicit BoundaryBox(const float &topleftx, const float &toplefty, const float &botrightx, const float &botrighty) noexcept;
        explicit BoundaryBox(const sf::Vector2f &topleft, const sf::Vector2f &botrigt) noexcept;
        ~BoundaryBox();
        // Add a rectangleptr of any object to test collision
        void AddBoundingBox(sf::RectangleShape *boundingbox);
        // Add a vector of rectangleptr of any objs to test collision
        void AddBoundingBoxes(const std::vector<sf::RectangleShape *> &boundingboxes);

    private:
        sf::RectangleShape *box;
        static const sf::Color boxcolor;
        std::vector<sf::RectangleShape *> boundingboxes;

    public:
        void Update();
        void Draw();

    public:
        BoundaryBox(const eke::BoundaryBox &other) = delete;
        BoundaryBox(eke::BoundaryBox &&other) = delete;
        BoundaryBox &operator=(const eke::BoundaryBox &other) = delete;
        BoundaryBox &operator=(eke::BoundaryBox &&other) = delete;
    };
} // namespace eke
#endif // __BOUNDARYBOX_H__