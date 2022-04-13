#include "Player.h"

namespace eke
{

    void Player::InitDefaultValues()
    {
        this->spritescale = 1.f;
        this->defprojpath = "../assets/projectiles/Energy/EnergyBall.png";
        this->maxhealth = 100;
        this->health = 100;
        this->velocity = 175.f;
        this->projectilevelocity = 300.f;
        this->shootinterval = 0.3f;
        this->shootIsRdy = true;
        this->regen = 5.f;
        this->mindamage = 5.f;
        this->maxdamage = 20.f;
    }

    Player::Player()
    {
        this->InitDefaultValues();
        this->InitPlayerBody(sf::Vector2f(1600.f, 1600.f));
        this->InitShoot();
        this->InitRegen();
        this->healthbar = new eke::Healthbar(this, sf::Vector2f(50.f, 10.f));
        this->cam = new eke::Camera();
    }

    Player::Player(const sf::Vector2f &spawnposition)
    {
        this->InitDefaultValues();
        this->InitPlayerBody(spawnposition);
        this->InitShoot();
        this->InitRegen();
        this->healthbar = new eke::Healthbar(this, sf::Vector2f(50.f, 10.f));
        this->cam = new eke::Camera();
    }

    Player::Player(const float &spawnx, const float &spawny)
    {
        this->InitDefaultValues();
        this->InitPlayerBody(sf::Vector2f(spawnx, spawny));
        this->InitShoot();
        this->InitRegen();
        this->healthbar = new eke::Healthbar(this, sf::Vector2f(50.f, 10.f));
        this->cam = new eke::Camera();
    }

    void Player::Update()
    {
        this->Movement();
        this->Shoot();
        this->UpdateProjectiles();
        this->UpdateTimers();
        this->UpdateCamera();
        this->UpdatePlayerBody();
    }

    void Player::Draw()
    {
        this->DrawProjectiles();
        this->DrawPlayerBody();
    }

    Player::~Player()
    {
        if (this->shootTimer != nullptr)
        {
            delete this->shootTimer;
        }
        if (this->regenTimer != nullptr)
        {
            delete this->regenTimer;
        }
        if (this->animation != nullptr)
        {
            delete this->animation;
        }
        if (this->cam != nullptr)
        {
            delete this->cam;
        }
        if (this->hitbox != nullptr)
        {
            delete this->hitbox;
        }
        if (this->healthbar != nullptr)
        {
            delete this->healthbar;
        }
        for (size_t i = 0; i < this->projectiles.size(); i++)
        {
            if (this->projectiles[i] != nullptr)
            {
                delete this->projectiles[i];
                this->projectiles.erase(this->projectiles.begin() + i);
            }
        }
    }

    void Player::Shoot()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shootIsRdy)
        {
            this->shootIsRdy = false;
            this->shootTimer->Start();

            // Rot calculation
            float rotation = (atan2f(sf::Mouse::getPosition(*eke::Globals::RenderWindow).x - (eke::Globals::RenderWindow->getSize().x / 2.f), (eke::Globals::RenderWindow->getSize().y / 2.f) - sf::Mouse::getPosition(*eke::Globals::RenderWindow).y)) * 180 / M_PI;

            this->projectiles.push_back(new eke::Projectile(this->defprojpath, 1, 9, 0.12f, this->hitbox->GetPosition(), rotation, this->CalculateDamage(), this->projectilevelocity));
        }
    }

    void Player::Movement()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->hitbox->SetPosition(this->hitbox->GetPosition().x - this->velocity * eke::Globals::DeltaTime, this->hitbox->GetPosition().y);
            this->animation->Update(1, eke::Globals::DeltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->hitbox->SetPosition(this->hitbox->GetPosition().x + this->velocity * eke::Globals::DeltaTime, this->hitbox->GetPosition().y);
            this->animation->Update(3, eke::Globals::DeltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->hitbox->SetPosition(this->hitbox->GetPosition().x, this->hitbox->GetPosition().y - this->velocity * eke::Globals::DeltaTime);
            this->animation->Update(0, eke::Globals::DeltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->hitbox->SetPosition(this->hitbox->GetPosition().x, this->hitbox->GetPosition().y + this->velocity * eke::Globals::DeltaTime);
            this->animation->Update(2, eke::Globals::DeltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if (this->health < this->maxhealth)
            {
                this->health += 1;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            if (this->health > 0)
            {
                this->health -= 1;
            }
        }
    }

    float Player::CalculateDamage()
    {
        int calculated = rand() % (static_cast<int>(this->maxdamage) - static_cast<int>(this->mindamage)) + static_cast<int>(this->mindamage);
        return calculated;
    }

    sf::RectangleShape *Player::GetBoundingBox()
    {
        return this->hitbox->GetDrawable();
    }

    sf::Vector2f Player::GetPosition() const
    {
        return this->hitbox->GetPosition();
    }

    void Player::SetPosition(const sf::Vector2f &position)
    {
        this->hitbox->SetPosition(position);
    }

    void Player::SetPosition(const float &posx, const float &posy)
    {
        this->hitbox->SetPosition(sf::Vector2f(posx, posy));
    }

    float Player::GetHealth() const
    {
        return this->health;
    }

    float Player::GetMaxHealth() const
    {
        return this->maxhealth;
    }

    void Player::SetHealth(const float &val)
    {
        if (val > 0 && val < (this->maxhealth + 1))
        {
            this->health = val;
        }
    }

    void Player::Damage(float val)
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

    float Player::GetRegen() const
    {
        return this->regen;
    }

    void Player::SetRegen(const float &val)
    {
        this->regen = val;
    }

    float Player::GetVelocity() const
    {
        return this->velocity;
    }

    void Player::SetVelocity(const float &val)
    {
        this->velocity = val;
    }

    void Player::RemoveProjectileFromNthPlace(int i)
    {
        delete this->projectiles[i];
        this->projectiles.erase(this->projectiles.begin() + i);
    }

    void Player::Reset()
    {
        for (size_t i = 0; i < this->projectiles.size(); i++)
        {
            delete this->projectiles[i];
        }
        this->projectiles.clear();
        this->SetHealth(this->maxhealth);
        this->animation->Update(2, eke::Globals::DeltaTime);
    }

    std::vector<eke::Projectile *> *Player::GetProjectiles()
    {
        return &(this->projectiles);
    }

    void Player::InitPlayerBody(const sf::Vector2f &spawnpos)
    {

        // Load texture
        this->texture.loadFromFile("../assets/characters/orc.png");
        this->sprite.setTexture(this->texture);
        this->animation = new eke::Anim(&this->texture, 4, 9, 0.12f);
        this->animation->Update(2, eke::Globals::DeltaTime);
        this->sprite.setTextureRect(this->animation->GetAnimRect());
        this->sprite.setOrigin(sf::Vector2f(animation->GetAnimRect().width / 4.f, animation->GetAnimRect().height / 2.f));
        this->sprite.setScale(sf::Vector2f(spritescale, spritescale));
        // Creating hitbox
        this->hitbox = new eke::Hitbox(sf::Vector2f(this->animation->GetAnimRect().width / 2.f, this->animation->GetAnimRect().height / 1.3f));
        // this->hitbox->SetPosition(sf::Vector2f(745.f, 675.f));
        this->hitbox->SetPosition(spawnpos);
    }

    void Player::InitShoot()
    {
        this->shootTimer = new eke::Timer(shootinterval);
        this->shootTimer->SetExpiredCallback(new std::function<void()>([this]()
                                                                       { this->shootIsRdy = true; }));
    }

    void Player::InitRegen()
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

    void Player::UpdateTimers()
    {
        this->shootTimer->Update(eke::Globals::DeltaTime);
        this->regenTimer->Update(eke::Globals::DeltaTime);
    }

    void Player::UpdateProjectiles()
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

    void Player::DrawProjectiles()
    {
        for (size_t i = 0; i < this->projectiles.size(); i++)
        {
            this->projectiles[i]->Draw();
        }
    }

    void Player::UpdatePlayerBody()
    {
        this->sprite.setTextureRect(this->animation->GetAnimRect());
        this->sprite.setPosition(this->hitbox->GetPosition().x - this->sprite.getTextureRect().width / 4.f, this->hitbox->GetPosition().y - this->sprite.getTextureRect().height / 8.f);
        this->healthbar->Update();
    }

    void Player::UpdateCamera()
    {
        this->cam->Update(this->GetPosition());
    }

    void Player::DrawPlayerBody()
    {
        this->healthbar->Draw();
        eke::Globals::RenderWindow->draw(this->sprite);
        this->hitbox->Draw();
    }

    void Player::PollEvents()
    {
    }
}