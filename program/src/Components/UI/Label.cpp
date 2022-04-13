#include "Label.h"

namespace eke
{
    Label::Label(const char *str, const float &posx, const float &posy)
    {
        this->text.setFont(eke::Globals::GameFont);
        this->text.setStyle(1);
        this->text.setFillColor(sf::Color::White);
        this->text.setString(str);
        this->bbox = this->text.getLocalBounds();
        this->text.setOrigin(sf::Vector2f(bbox.width / 2, bbox.height * 1.5));
        this->text.setPosition(sf::Vector2f(posx, posy));
        this->InitInitialBox();
    }

    Label::Label(const char *str, const sf::Vector2f position)
    {
        this->text.setFont(eke::Globals::GameFont);
        this->text.setStyle(1);
        this->text.setFillColor(sf::Color::White);
        this->text.setString(str);
        this->bbox = this->text.getLocalBounds();
        this->text.setOrigin(sf::Vector2f(bbox.width / 2, bbox.height * 1.5));
        this->text.setPosition(position);
        this->InitInitialBox();
    }

    Label::Label(const char *str, const float &posx, const float &posy, const sf::Color &textcolor)
    {
        this->text.setFont(eke::Globals::GameFont);
        this->text.setStyle(1);
        this->text.setFillColor(textcolor);
        this->text.setString(str);
        this->bbox = this->text.getLocalBounds();
        this->text.setOrigin(sf::Vector2f(bbox.width / 2, bbox.height * 1.5));
        this->text.setPosition(sf::Vector2f(posx, posy));
        this->InitInitialBox();
    }

    Label::Label(const char *str, const sf::Vector2f &position, const sf::Color &textcolor)
    {
        this->text.setFont(eke::Globals::GameFont);
        this->text.setStyle(1);
        this->text.setFillColor(textcolor);
        this->text.setString(str);
        this->bbox = this->text.getLocalBounds();
        this->text.setOrigin(sf::Vector2f(bbox.width / 2, bbox.height * 1.5));
        this->text.setPosition(position);
        this->InitInitialBox();
    }

    Label::~Label()
    {
        if (this->sprite != nullptr)
        {
            delete this->sprite;
        }

        if (this->texture != nullptr)
        {
            delete this->texture;
        }

        if (this->initialbox != nullptr)
        {
            delete this->initialbox;
        }
    }

    void Label::Draw()
    {
        eke::Globals::RenderWindow->draw(this->text);
        if (eke::Globals::Debug)
        {
            eke::Globals::RenderWindow->draw(*this->initialbox);
        }
    }

    void Label::SetScale(const sf::Vector2f &scale)
    {
        this->text.setScale(scale);
        this->initialbox->setScale(scale);
    }

    void Label::SetScale(float xscale, float yscale)
    {
        this->text.setScale(xscale, yscale);
        this->initialbox->setScale(xscale, yscale);
    }

    void Label::SetPosition(const float &posx, const float &posy)
    {
        this->AdjustInitialBox();
        this->text.setPosition(sf::Vector2f(posx, posy));
        this->initialbox->setPosition(this->text.getPosition());
    }

    void Label::SetPosition(const sf::Vector2f &position)
    {
        this->AdjustInitialBox();
        this->text.setPosition(position);
        this->initialbox->setPosition(this->text.getPosition());
    }

    sf::Vector2f Label::GetPosition() const
    {
        return this->text.getPosition();
    }

    sf::Vector2f Label::GetSize() const
    {
        return this->initialbox->getSize();
    }

    void Label::SetColor(const sf::Color &color)
    {
        this->text.setFillColor(color);
    }

    void Label::SetText(const char *str)
    {
        this->text.setString(str);
    }

    void Label::PollEvents()
    {
    }

    void Label::Update()
    {
        this->AdjustInitialBox();
    }

    void Label::InitInitialBox()
    {
        this->initialbox = new sf::RectangleShape(sf::Vector2f(this->bbox.width, this->bbox.height));
        this->initialbox->setFillColor(sf::Color::Transparent);
        this->initialbox->setOutlineThickness(2.f);
        this->initialbox->setOutlineColor(sf::Color::Red);
        this->initialbox->setOrigin(this->initialbox->getSize().x / 2, this->initialbox->getSize().y * 1.5);
        this->initialbox->setPosition(this->GetPosition());
    }

    void Label::AdjustInitialBox()
    {
        this->bbox = this->text.getLocalBounds();
        this->text.setOrigin(sf::Vector2f(bbox.width / 2, bbox.height * 1.5));
        this->initialbox->setSize(sf::Vector2f(this->bbox.width, this->bbox.height));
        this->initialbox->setOrigin(this->initialbox->getSize().x / 2, this->initialbox->getSize().y * 1.5);
        this->initialbox->setPosition(this->GetPosition());
    }
}