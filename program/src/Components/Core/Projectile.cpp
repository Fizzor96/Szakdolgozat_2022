#include "Projectile.h"

namespace eke
{
    Projectile::Projectile(const char *texturepath, const float &rows, const float &cols, const float &switchtime, const sf::Vector2f &org, const float &rot, const float &damage, const float &velo)
    {
        // Init Sprite
        float spritescale = 0.35f;

        this->texture = new sf::Texture();
        this->texture->loadFromFile(texturepath);

        this->sprite = new sf::Sprite(*this->texture);
        this->anim = new eke::Anim(this->texture, rows, cols, switchtime);
        this->sprite->setTextureRect(this->anim->GetAnimRect());
        this->sprite->setOrigin(sf::Vector2f(this->anim->GetAnimRect().width / 2.f, this->anim->GetAnimRect().height / 2.f));
        this->sprite->setScale(sf::Vector2f(spritescale, spritescale));
        this->sprite->setRotation(rot - 90.f);

        // Init Hitbox
        this->hitbox = new eke::Hitbox(sf::Vector2f((this->anim->GetAnimRect().width / 2.f) * spritescale, (this->anim->GetAnimRect().height / 2.f) * spritescale));
        this->hitbox->SetPosition(org);

        // Init dirs
        this->dirx = cosf((rot - 90.f) * (M_PI / 180.f));
        this->diry = sinf((rot - 90.f) * (M_PI / 180.f));

        this->velocity = velo;

        // Init default lifetime in seconds (we don't want to run out of memory)!
        this->lifetime = 10.f;

        this->damage = damage;
    }

    Projectile::~Projectile()
    {
        if (this->texture != nullptr)
        {
            delete this->texture;
        }
        if (this->sprite != nullptr)
        {
            delete this->sprite;
        }
        if (this->hitbox != nullptr)
        {
            delete this->hitbox;
        }
        if (this->anim != nullptr)
        {
            delete this->anim;
        }
    }

    sf::FloatRect Projectile::GetGlobalBounds() const
    {
        return this->hitbox->GetDrawable()->getGlobalBounds();
    }

    sf::RectangleShape *Projectile::GetBoundingBox()
    {
        return this->hitbox->GetDrawable();
    }

    sf::Vector2f Projectile::GetPosition() const
    {
        return this->hitbox->GetPosition();
    }

    void Projectile::PollEvents()
    {
    }

    void Projectile::Update()
    {
        if (this->lifetime > 0)
        {
            this->lifetime -= eke::Globals::DeltaTime;
        }
        else
        {
            delete this;
        }

        this->anim->Update(0, eke::Globals::DeltaTime);
        this->sprite->setTextureRect(this->anim->GetAnimRect());
        this->hitbox->SetPosition(this->hitbox->GetPosition().x + this->dirx * this->velocity * eke::Globals::DeltaTime, this->hitbox->GetPosition().y + this->diry * this->velocity * eke::Globals::DeltaTime);
        this->sprite->setPosition(this->hitbox->GetPosition());
    }

    void Projectile::Draw()
    {
        eke::Globals::RenderWindow->draw(*this->sprite);
        this->hitbox->Draw();
    }

    float Projectile::GetDuration() const
    {
        return this->lifetime;
    }

    void Projectile::SetColor(const sf::Color &color)
    {
        this->sprite->setColor(color);
    }

    float Projectile::GetDamage() const
    {
        return this->damage;
    }
} // namespace eke
