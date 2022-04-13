#include "Warrior.h"

namespace eke
{
    void Warrior::InitDefaultValues()
    {
        this->defprojpath = "../assets/projectiles/Energy/EnergyBall.png";
        this->maxhealth = 50;
        this->health = 50;
        this->velocity = 100.f;
        this->projectilevelocity = 270.f;
        this->shootinterval = 2.5f;
        this->regen = 0.f;
        this->shootIsRdy = true;
        this->spritescale = 1.5f;
        this->mindamage = 3.f;
        this->maxdamage = 10.f;
    }

    Warrior::Warrior(eke::Player *target)
    {
        this->target = target;
        this->InitDefaultValues();
        this->InitWarriorBody(sf::Vector2f(745.f, 675.f));
        this->InitShoot();
        this->InitRegen();
    }

    Warrior::Warrior(sf::Vector2f spawnposition, eke::Player *target)
    {
        this->target = target;
        this->InitDefaultValues();
        this->InitWarriorBody(spawnposition);
        this->InitShoot();
        this->InitRegen();
    }

    Warrior::Warrior(float spawnx, float spawny, eke::Player *target)
    {
        this->target = target;
        this->InitDefaultValues();
        this->InitWarriorBody(sf::Vector2f(spawnx, spawny));
        this->InitShoot();
        this->InitRegen();
    }

    Warrior::~Warrior()
    {
        if (this->shootTimer != nullptr)
        {
            delete this->shootTimer;
        }
        if (this->animation != nullptr)
        {
            delete this->animation;
        }
        if (this->hitbox != nullptr)
        {
            delete this->hitbox;
        }
        if (this->regenTimer != nullptr)
        {
            delete this->regenTimer;
        }
        if (this->healthbar != nullptr)
        {
            delete this->healthbar;
        }
    }

    void Warrior::Update()
    {
        this->Movement();
        this->Shoot();
        this->UpdateProjectiles();
        this->UpdateTimers();
        this->UpdateWarriorBody();
    }

    void Warrior::Draw()
    {
        this->DrawProjectiles();
        this->DrawWarriorBody();
    }

    void Warrior::InitWarriorBody(sf::Vector2f spawnposition)
    {
        this->texture.loadFromFile("../assets/characters/warrior/warrior.png");
        this->sprite.setTexture(this->texture);
        this->animation = new eke::Anim(&this->texture, 4, 8, 0.125f);
        this->animation->Update(0, eke::Globals::DeltaTime);
        this->sprite.setTextureRect(this->animation->GetAnimRect());
        this->sprite.setOrigin(sf::Vector2f(this->animation->GetAnimRect().width / 3.f, this->animation->GetAnimRect().height / 2.f));
        this->sprite.setScale(sf::Vector2f(this->spritescale, this->spritescale));
        this->hitbox = new eke::Hitbox(sf::Vector2f((this->animation->GetAnimRect().width / 2.f) * this->spritescale, (this->animation->GetAnimRect().height / 2.f) * this->spritescale));
        this->hitbox->SetPosition(spawnposition);
        this->healthbar = new eke::Healthbar(this, sf::Vector2f(50.f, 10.f));
    }
    void Warrior::InitWarriorBody(float spawnx, float spawny)
    {
        this->texture.loadFromFile("../assets/characters/warrior/warrior.png");
        this->sprite.setTexture(this->texture);
        this->animation = new eke::Anim(&this->texture, 4, 8, 0.125f);
        this->animation->Update(0, eke::Globals::DeltaTime);
        this->sprite.setTextureRect(this->animation->GetAnimRect());
        this->sprite.setOrigin(sf::Vector2f(this->animation->GetAnimRect().width / 3.f, this->animation->GetAnimRect().height / 2.f));
        this->sprite.setScale(sf::Vector2f(this->spritescale, this->spritescale));
        this->hitbox = new eke::Hitbox(sf::Vector2f((this->animation->GetAnimRect().width / 2.f) * this->spritescale, (this->animation->GetAnimRect().height / 2.f) * this->spritescale));
        this->hitbox->SetPosition(sf::Vector2f(spawnx, spawny));
        this->healthbar = new eke::Healthbar(this, sf::Vector2f(50.f, 10.f));
    }

    void Warrior::InitShoot()
    {
        this->shootTimer = new eke::Timer(this->shootinterval);
        this->shootTimer->SetExpiredCallback(new std::function<void()>([this]()
                                                                       { this->shootIsRdy = true; }));
    }

    void Warrior::InitRegen()
    {
        this->regenTimer = new eke::Timer(5.f, true);
        this->regenTimer->Start();
        this->regenTimer->SetExpiredCallback(new std::function<void()>([this]()
                                                                       {
            if (this->GetHealth() > this->GetMaxHealth() - this->GetRegen() && this->GetHealth() < this->GetMaxHealth())
            {
                this->SetHealth(this->GetMaxHealth());
            }
            if (this->GetHealth() <= this->GetMaxHealth() - this->regen)
            {
                this->SetHealth(this->GetHealth() + this->GetRegen());
            } }));
    }

    void Warrior::UpdateWarriorBody()
    {
        this->sprite.setTextureRect(this->animation->GetAnimRect());
        this->sprite.setPosition(this->hitbox->GetPosition().x - this->sprite.getTextureRect().width / 4.f, this->hitbox->GetPosition().y - this->sprite.getTextureRect().height / 8.f);
        this->healthbar->Update();
    }

    void Warrior::UpdateTimers()
    {
        this->shootTimer->Update(eke::Globals::DeltaTime);
        this->regenTimer->Update(eke::Globals::DeltaTime);
    }

    void Warrior::UpdateProjectiles()
    {
        for (size_t i = 0; i < this->projectiles.size(); i++)
        {
            if (this->projectiles[i] != nullptr)
            {
                this->projectiles[i]->Update();
            }
            if (this->projectiles[i] == nullptr || this->projectiles[i]->GetDuration() < 0)
            {
                this->projectiles.erase(this->projectiles.begin() + i);
            }
        }
    }

    void Warrior::DrawProjectiles()
    {
        for (size_t i = 0; i < this->projectiles.size(); i++)
        {
            this->projectiles[i]->Draw();
        }
    }

    void Warrior::DrawWarriorBody()
    {
        this->healthbar->Draw();
        eke::Globals::RenderWindow->draw(this->sprite);
        this->hitbox->Draw();
    }

    float Warrior::GetRegen() const
    {
        return this->regen;
    }

    void Warrior::SetRegen(const float &val)
    {
        this->regen = val;
    }

    void Warrior::SetTarget(eke::Player *target)
    {
        this->target = target;
    }

    void Warrior::DelTarget()
    {
        if (this->target != nullptr)
        {
            this->target = nullptr;
        }
    }

    sf::Vector2f Warrior::GetPosition() const
    {
        return this->hitbox->GetPosition();
    }

    void Warrior::SetPosition(const sf::Vector2f &pos)
    {
        this->hitbox->SetPosition(pos);
    }

    void Warrior::SetPosition(const float &posx, const float &posy)
    {
        this->hitbox->SetPosition(posx, posy);
    }

    sf::RectangleShape *Warrior::GetBoundingBox()
    {
        return this->hitbox->GetDrawable();
    }

    void Warrior::Shoot()
    {
        if (this->target != nullptr)
        {
            if (this->shootIsRdy)
            {
                this->shootIsRdy = false;
                this->shootTimer->Start();

                float rotation = (atan2f(this->target->GetPosition().x - this->hitbox->GetPosition().x, this->hitbox->GetPosition().y - this->target->GetPosition().y)) * 180 / M_PI;

                eke::Projectile *tempprojectile = new eke::Projectile(this->defprojpath, 1, 9, 0.12f, this->hitbox->GetPosition(), rotation, this->CalculateDamage(), this->projectilevelocity);
                tempprojectile->SetColor(sf::Color(255, 255, 0, 255));

                this->projectiles.push_back(tempprojectile);
            }
        }
    }

    void Warrior::Movement()
    {
        if (this->target != nullptr)
        {
            float dx = this->target->GetPosition().x - this->hitbox->GetPosition().x;
            float dy = this->target->GetPosition().y - this->hitbox->GetPosition().y;

            float dirx = 0;
            float diry = 0;

            float divider = (abs(sqrt(dx * dx + dy * dy)));

            if (divider != 0)
            {
                dirx = dx / (abs(sqrt(dx * dx + dy * dy)));
                diry = dy / (abs(sqrt(dx * dx + dy * dy)));
            }

            float absdx = dx;
            float absdy = dy;

            if (dx < 0)
            {
                absdx = -1 * dx;
            }
            if (dy < 0)
            {
                absdy = -1 * dy;
            }

            this->hitbox->SetPosition(sf::Vector2f(this->hitbox->GetPosition().x + dirx * this->velocity * eke::Globals::DeltaTime, this->hitbox->GetPosition().y + diry * this->velocity * eke::Globals::DeltaTime));

            if (absdx >= absdy)
            {
                if (dirx >= 0)
                {
                    this->animation->Update(2, eke::Globals::DeltaTime);
                }
                else
                {
                    this->animation->Update(1, eke::Globals::DeltaTime);
                }
            }
            if (absdy > absdx)
            {
                if (diry >= 0)
                {
                    this->animation->Update(0, eke::Globals::DeltaTime);
                }
                else
                {
                    this->animation->Update(3, eke::Globals::DeltaTime);
                }
            }
        }
    }

    float Warrior::CalculateDamage()
    {
        int calculated = rand() % (static_cast<int>(this->maxdamage) - static_cast<int>(this->mindamage)) + static_cast<int>(this->mindamage);
        return calculated;
    }

    float Warrior::GetHealth() const
    {
        return this->health;
    }

    float Warrior::GetMaxHealth() const
    {
        return this->maxhealth;
    }

    void Warrior::SetHealth(const float &val)
    {
        this->health = val;
    }

    void Warrior::Damage(const float &val)
    {
        if ((this->health - val) < 0)
        {
            this->health = 0;
        }
        else
        {
            this->health -= val;
        }
    }

    std::vector<eke::Projectile *> *Warrior::GetProjectiles()
    {
        return &(this->projectiles);
    }

    void Warrior::RemoveProjectileFromNthPlace(int i)
    {
        delete this->projectiles[i];
        this->projectiles.erase(this->projectiles.begin() + i);
    }

    void Warrior::PollEvents()
    {
    }

} // namespace eke
