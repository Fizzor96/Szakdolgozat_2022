#ifndef __HEALTHBAR_H__
#define __HEALTHBAR_H__

#include "Core/Creature.h"
#include "Core/GameObject.h"
#include "Core/Globals.h"
#include <SFML/Graphics.hpp>

namespace eke
{
    class Healthbar : public GameObject
    {
    public:
        explicit Healthbar(eke::Creature *creature, const sf::Vector2f &size) noexcept;
        explicit Healthbar(eke::Creature *creature, const float &width, const float &height) noexcept;
        void SetColor(const sf::Color &color);
        void SetPosition(const sf::Vector2f &pos);
        void SetPosition(const float &x, const float &y);
        sf::Vector2f GetPosition() const;
        void Update() override;
        void Draw() override;
        void PollEvents() override;
        ~Healthbar();

    private:
        // Do not delete creature when destructor called!!!
        eke::Creature *creature;
        sf::RectangleShape bar;
        sf::RectangleShape border;
        sf::Text lbl;
        sf::FloatRect lblbox;
        float maxsize;

    private:
        void InitFont();
        void ValidateTextLength();

    public:
        Healthbar(const Healthbar &other) = delete;
        Healthbar(Healthbar &&other) = delete;
        Healthbar &operator=(const Healthbar &other) = delete;
        Healthbar &operator=(Healthbar &&other) = delete;
    };
} // namespace eke

#endif // __HEALTHBAR_H__