#include "Healthbar.h"

namespace eke
{
    Healthbar::Healthbar(eke::Creature *creature, const sf::Vector2f &size) noexcept
    {
        this->creature = creature;

        this->bar.setSize(size);
        this->bar.setFillColor(sf::Color::Red);
        this->bar.setOutlineColor(sf::Color::Transparent);
        this->bar.setPosition(sf::Vector2f(0.f, 0.f));

        this->border.setSize(size);
        this->border.setFillColor(sf::Color::Transparent);
        this->border.setOutlineColor(sf::Color::Black);
        this->border.setOutlineThickness(2.f);
        this->border.setOrigin(this->border.getSize() / 2.f);
        this->border.setPosition(sf::Vector2f(0.f, 0.f));

        this->maxsize = size.x;

        this->InitFont();
    }

    Healthbar::Healthbar(eke::Creature *creature, const float &width, const float &height) noexcept
    {
        this->creature = creature;

        this->bar.setSize(sf::Vector2f(width, height));
        this->bar.setFillColor(sf::Color::Red);
        this->bar.setOutlineColor(sf::Color::Transparent);
        this->bar.setPosition(sf::Vector2f(0.f, 0.f));

        this->border.setSize(sf::Vector2f(width, height));
        this->border.setFillColor(sf::Color::Transparent);
        this->border.setOutlineColor(sf::Color::Black);
        this->border.setOutlineThickness(2.f);
        this->border.setOrigin(this->border.getSize() / 2.f);
        this->border.setPosition(sf::Vector2f(0.f, 0.f));

        this->maxsize = width;

        this->InitFont();
    }

    void Healthbar::SetColor(const sf::Color &color)
    {
        this->bar.setFillColor(color);
    }

    void Healthbar::SetPosition(const sf::Vector2f &pos)
    {
        this->border.setPosition(pos);
    }

    void Healthbar::SetPosition(const float &x, const float &y)
    {
        this->border.setPosition(x, y);
    }

    sf::Vector2f Healthbar::GetPosition() const
    {
        return this->border.getPosition();
    }

    void Healthbar::Update()
    {
        this->lbl.setString(std::to_string((int)this->creature->GetHealth()));

        this->bar.setSize(sf::Vector2f(this->maxsize * (this->creature->GetHealth() / this->creature->GetMaxHealth()), this->bar.getSize().y));

        this->border.setPosition(this->creature->GetBoundingBox()->getPosition().x, this->creature->GetBoundingBox()->getPosition().y - this->creature->GetBoundingBox()->getSize().y - this->creature->GetBoundingBox()->getSize().y / 10.f);

        this->bar.setPosition(sf::Vector2f(this->border.getPosition().x - this->border.getSize().x / 2.f, this->border.getPosition().y - this->border.getSize().y / 2.f));

        this->lbl.setPosition(sf::Vector2f(this->border.getPosition().x - this->lblbox.width / 2.f, this->border.getPosition().y));
    }

    void Healthbar::Draw()
    {
        eke::Globals::RenderWindow->draw(this->bar);
        eke::Globals::RenderWindow->draw(this->border);
        eke::Globals::RenderWindow->draw(this->lbl);
    }

    void Healthbar::PollEvents()
    {
    }

    Healthbar::~Healthbar()
    {
    }

    void Healthbar::InitFont()
    {
        this->lbl.setFont(eke::Globals::GameFont);
        this->lbl.setFillColor(sf::Color::White);
        this->lbl.setStyle(sf::Text::Regular);
        this->lbl.setString("0");
        this->lbl.setScale(sf::Vector2f(0.5f, 0.5f));
        this->lblbox = this->lbl.getGlobalBounds();
        this->lbl.setOrigin(sf::Vector2f(this->lblbox.width / 1, this->lblbox.height * 3.4f));
        // this->ValidateTextLength();
    }

    void Healthbar::ValidateTextLength()
    {
        if (this->lblbox.width > this->border.getSize().x)
        {
            float tempx = (this->lblbox.width / this->border.getSize().x) * 1.2;
            this->border.setScale(sf::Vector2f(tempx, this->border.getSize().y));
            this->lbl.setPosition(this->border.getPosition());
        }
        if (this->lblbox.height > this->border.getSize().y)
        {
            float tempy = this->lblbox.height * 3;
            this->border.setScale(sf::Vector2f(this->border.getScale().x, tempy));
            this->lbl.setPosition(this->border.getPosition());
        }
    }
} // namespace eke
