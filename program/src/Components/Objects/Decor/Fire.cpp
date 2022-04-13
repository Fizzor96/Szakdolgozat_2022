#include "Fire.h"

namespace eke
{
    Fire::Fire()
    {
        this->texture = new sf::Texture();
        this->sprite = new sf::Sprite();
        this->texture->loadFromFile("../assets/decor/Small_Fireball_10x26.png");
        this->sprite->setTexture(*this->texture);
        this->sprite->setPosition(100.f, 100.f);
        this->sprite->setScale(sf::Vector2f(5.f, 5.f));
        this->anim = new Anim(this->texture, sf::Vector2u(10, 6), 0.1f);
        this->sprite->setOrigin(sf::Vector2f(anim->GetAnimRect().width / 2, anim->GetAnimRect().height));
    }

    void Fire::SetPosition(const float &posx, const float &posy)
    {
        this->sprite->setPosition(sf::Vector2f(posx, posy));
    }

    void Fire::SetPosition(const sf::Vector2f &pos)
    {
        this->sprite->setPosition(pos);
    }

    void Fire::SetScale(const sf::Vector2f &scale)
    {
        this->sprite->setScale(scale);
    }

    void Fire::SetScale(const float &scalex, const float &scaley)
    {
        this->sprite->setScale(sf::Vector2f(scalex, scaley));
    }

    Fire::~Fire()
    {
        delete this->sprite;
        delete this->texture;
    }

    void Fire::PollEvents()
    {
    }

    void Fire::Update()
    {
        anim->Update(0, eke::Globals::DeltaTime);
        this->sprite->setTextureRect(this->anim->textureRect);
    }

    void Fire::Draw()
    {
        eke::Globals::RenderWindow->draw(*this->sprite);
    }

    sf::FloatRect Fire::GetGlobalBounds() const
    {
        return sf::FloatRect(0, 0, 0, 0);
    }

} // namespace eke
