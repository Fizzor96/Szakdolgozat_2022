#include "Hitbox.h"

namespace eke
{
    Hitbox::Hitbox()
    {
        this->hitbox = new sf::RectangleShape(sf::Vector2f(0.f, 0.f));
        this->hitbox->setFillColor(sf::Color::Transparent);
        this->hitbox->setOutlineColor(sf::Color::Red);
        this->hitbox->setOutlineThickness(2.f);
        this->hitbox->setPosition(sf::Vector2f(0.f, 0.f));
    }

    Hitbox::Hitbox(const sf::Vector2f &size)
    {
        this->hitbox = new sf::RectangleShape(size);
        this->hitbox->setOrigin(this->hitbox->getSize() / 2.f);
        this->hitbox->setFillColor(sf::Color::Transparent);
        this->hitbox->setOutlineColor(sf::Color::Red);
        this->hitbox->setOutlineThickness(2.f);
        this->hitbox->setPosition(sf::Vector2f(0.f, 0.f));
    }

    Hitbox::Hitbox(const float &width, const float &height)
    {
        this->hitbox = new sf::RectangleShape(sf::Vector2f(width, height));
        this->hitbox->setOrigin(this->hitbox->getSize() / 2.f);
        this->hitbox->setFillColor(sf::Color::Transparent);
        this->hitbox->setOutlineColor(sf::Color::Red);
        this->hitbox->setOutlineThickness(2.f);
        this->hitbox->setPosition(sf::Vector2f(0.f, 0.f));
    }

    Hitbox::~Hitbox()
    {
        if (this->hitbox != nullptr)
        {
            delete this->hitbox;
        }
    }

    void Hitbox::SetSize(const sf::Vector2f &size)
    {
        this->hitbox->setSize(size);
        this->hitbox->setOrigin(sf::Vector2f(this->hitbox->getSize().x / 2.f, this->hitbox->getSize().y / 2.f));
    }

    void Hitbox::SetSize(const float &widht, const float &height)
    {
        this->hitbox->setSize(sf::Vector2f(widht, height));
        this->hitbox->setOrigin(sf::Vector2f(this->hitbox->getSize().x / 2.f, this->hitbox->getSize().y / 2.f));
    }

    sf::Vector2f Hitbox::GetSize() const
    {
        return this->hitbox->getSize();
    }

    void Hitbox::SetPosition(const sf::Vector2f &pos)
    {
        this->hitbox->setPosition(pos);
    }

    void Hitbox::SetPosition(const float &x, const float &y)
    {
        this->hitbox->setPosition(sf::Vector2f(x, y));
    }

    sf::Vector2f Hitbox::GetPosition() const
    {
        return this->hitbox->getPosition();
    }

    sf::RectangleShape *Hitbox::GetDrawable()
    {
        return this->hitbox;
    }

    void Hitbox::Update()
    {
    }

    void Hitbox::PollEvents()
    {
    }

    void Hitbox::Draw()
    {
        if (eke::Globals::Debug)
        {
            eke::Globals::RenderWindow->draw(*this->hitbox);
        }
    }
} // namespace eke
