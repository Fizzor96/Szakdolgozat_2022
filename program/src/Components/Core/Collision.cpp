#include "Collision.h"

namespace eke
{
    bool Collision::CheckColl(sf::RectangleShape *first, sf::RectangleShape *second, float thrust)
    {
        sf::Vector2f firstpos = first->getPosition();
        sf::Vector2f firstsize = first->getSize() / 2.f;
        sf::Vector2f secondpos = second->getPosition();
        sf::Vector2f secondsize = second->getSize() / 2.f;
        float dx = secondpos.x - firstpos.x;
        float dy = secondpos.y - firstpos.y;
        float interx = abs(dx) - (secondsize.x + firstsize.x);
        float intery = abs(dy) - (secondsize.y + firstsize.y);
        if (interx < 0.f && intery < 0.f)
        {
            thrust = std::min(std::max(thrust, 0.f), 1.f);
            if (interx > intery)
            {
                if (dx > 0.f)
                {
                    first->move(interx * (1.f - thrust), 0.f);
                    second->move(-interx * thrust, 0.f);
                }
                else
                {
                    first->move(-interx * (1.f - thrust), 0.f);
                    second->move(interx * thrust, 0.f);
                }
            }
            else
            {
                if (dy > 0.f)
                {
                    first->move(0.f, intery * (1.f - thrust));
                    second->move(0.f, -intery * thrust);
                }
                else
                {
                    first->move(0.f, -intery * (1.f - thrust));
                    second->move(0.f, intery * thrust);
                }
            }
            return true;
        }
        return false;
    }
} // namespace eke
