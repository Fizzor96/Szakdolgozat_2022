#include "Candle.h"

namespace eke
{
    Candle::Candle()
    {
        this->texture = new sf::Texture();
        this->sprite = new sf::Sprite();
        this->texture->loadFromFile("../assets/decor/CandleA.png");
        this->sprite->setTexture(*this->texture);
        this->sprite->setPosition(100.f, 100.f);
        this->sprite->setScale(sf::Vector2f(5.f, 5.f));
        this->anim = new Anim(this->texture, sf::Vector2u(4, 1), 0.25f);
        this->sprite->setOrigin(sf::Vector2f(anim->GetAnimRect().width / 2, anim->GetAnimRect().height / 2));
    }

    void Candle::SetPosition(const float &posx, const float &posy)
    {
        this->sprite->setPosition(sf::Vector2f(posx, posy));
    }

    void Candle::SetPosition(const sf::Vector2f &pos)
    {
        this->sprite->setPosition(pos);
    }

    sf::Vector2f Candle::GetPosition() const
    {
        return this->sprite->getPosition();
    }

    void Candle::SetScale(const sf::Vector2f &scale)
    {
        this->sprite->setScale(scale);
    }

    void Candle::SetScale(const float &scalex, const float &scaley)
    {
        this->sprite->setScale(sf::Vector2f(scalex, scaley));
    }

    Candle::~Candle()
    {
        delete this->sprite;
        delete this->texture;
    }

    void Candle::PollEvents()
    {
    }

    void Candle::Update()
    {
        this->anim->Update(0, eke::Globals::DeltaTime);
        this->sprite->setTextureRect(this->anim->textureRect);
    }

    void Candle::Draw()
    {
        eke::Globals::RenderWindow->draw(*this->sprite);
    }

    sf::FloatRect Candle::GetGlobalBounds() const
    {
        return sf::FloatRect(0, 0, 0, 0);
    }

} // namespace eke
