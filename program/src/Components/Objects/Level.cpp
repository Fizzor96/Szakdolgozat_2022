#include "Level.h"

namespace eke
{
    Level::Level()
    {
        this->InitMap();
        this->InitTimers();
        this->InitPlayer();
        this->InitMapEdges();
    }

    void Level::Update()
    {
        this->UpdateMap();
        this->UpdateTimers();
        this->UpdatePlayer();
        this->UpdateEnemies();
    }

    void Level::Draw()
    {
        this->DrawMap();
        this->DrawEnemies();
        this->DrawPlayer();
        this->DrawMapEdges();
    }

    void Level::PollEvents()
    {
        this->player->PollEvents();
    }

    Level::~Level()
    {
        if (this->player != nullptr)
        {
            delete this->player;
        }
        for (size_t i = 0; i < this->boundaryboxes.size(); i++)
        {
            if (this->boundaryboxes[i] != nullptr)
            {
                delete this->boundaryboxes[i];
                this->boundaryboxes.erase(this->boundaryboxes.begin() + i);
            }
        }
        for (size_t i = 0; i < this->warriors.size(); i++)
        {
            if (this->warriors[i] != nullptr)
            {
                delete this->warriors[i];
                this->warriors.erase(this->warriors.begin() + i);
            }
        }

        if (this->enemyGenTimer != nullptr)
        {
            delete this->enemyGenTimer;
        }
    }

    void Level::AddWarrior()
    {
        int floorx = 625;
        int floory = 575;
        int topx = 2575;
        int topy = 2625;
        int xcoord = rand() % (topx - floorx) + floorx;
        int ycoord = rand() % (topy - floory) + floory;

        while (abs(this->player->GetPosition().x - xcoord) < 500 || abs(this->player->GetPosition().y - ycoord) < 500)
        {
            xcoord = rand() % (topx - floorx) + floorx;
            ycoord = rand() % (topy - floory) + floory;
        }

        if (this->warriors.size() < 10)
        {
            this->warriors.push_back(new eke::Warrior(sf::Vector2f(xcoord, ycoord), this->player));
        }
    }

    void Level::Restart()
    {
        for (size_t i = 0; i < this->warriors.size(); i++)
        {
            delete this->warriors[i];
        }
        this->warriors.clear();
        this->player->SetPosition(sf::Vector2f(1600.f, 1600.f));
        this->player->Reset();
    }

    eke::Player *Level::GetPlayerInst()
    {
        return this->player;
    }

    bool Level::IsPlayerAlive()
    {
        if (this->player->GetHealth() > 0)
        {
            return true;
        }
        return false;
    }

    sf::Vector2f Level::GetPosition() const
    {
        return sf::Vector2f(0, 0);
    }

    void Level::InitMap()
    {
        this->mapscale = 1.f;
        this->texture.loadFromFile("../assets/levels/level1.png");
        this->map.setTexture(this->texture);
        this->map.setScale(sf::Vector2f(mapscale, mapscale));
    }

    void Level::InitTimers()
    {
        this->enemyGenTimer = new eke::Timer(3.f, true);
        this->enemyGenTimer->SetExpiredCallback(new std::function<void()>([this]()
                                                                          { this->AddWarrior(); }));
        this->enemyGenTimer->Start();
    }

    void Level::InitPlayer()
    {
        this->player = new eke::Player(sf::Vector2f(1600.f, 1600.f));
    }

    void Level::InitMapEdges()
    {
        this->boundaryboxes.push_back(new eke::BoundaryBox(sf::Vector2f(0.f, 0.f), sf::Vector2f(3200.f, 575.f)));
        this->boundaryboxes.push_back(new eke::BoundaryBox(sf::Vector2f(0.f, 0.f), sf::Vector2f(625.f, 3200.f)));
        this->boundaryboxes.push_back(new eke::BoundaryBox(sf::Vector2f(2575.f, 0.f), sf::Vector2f(3200.f, 3200.f)));
        this->boundaryboxes.push_back(new eke::BoundaryBox(sf::Vector2f(0.f, 2625.f), sf::Vector2f(3200.f, 3200.f)));
        for (size_t i = 0; i < this->boundaryboxes.size(); i++)
        {
            this->boundaryboxes[i]->AddBoundingBox(this->player->GetBoundingBox());
        }
    }

    void Level::UpdateMap()
    {
        for (size_t i = 0; i < this->boundaryboxes.size(); i++)
        {
            this->boundaryboxes[i]->Update();
        }
    }

    void Level::UpdatePlayer()
    {
        this->player->Update();
    }

    void Level::UpdateTimers()
    {
        this->enemyGenTimer->Update(eke::Globals::DeltaTime);
    }

    void Level::UpdateEnemies()
    {
        if (this->warriors.size() > 0)
        {
            for (size_t i = 0; i < this->warriors.size(); i++)
            {
                if (this->warriors[i] != nullptr && this->warriors[i]->GetHealth() > 0)
                {
                    this->warriors[i]->Update();
                }
                else
                {
                    delete this->warriors[i];
                    this->warriors.erase(this->warriors.begin() + i);
                }
            }
        }
        this->CheckEnemyCollisions();
        this->CheckProjectileIntersections();
    }

    void Level::DrawMap()
    {
        eke::Globals::RenderWindow->draw(this->map);
    }

    void Level::DrawMapEdges()
    {
        for (size_t i = 0; i < this->boundaryboxes.size(); i++)
        {
            this->boundaryboxes[i]->Draw();
        }
    }

    void Level::DrawPlayer()
    {
        this->player->Draw();
    }

    void Level::DrawEnemies()
    {
        for (size_t i = 0; i < this->warriors.size(); i++)
        {
            if (this->warriors[i] != nullptr)
            {
                this->warriors[i]->Draw();
            }
        }
    }

    void Level::CheckEnemyCollisions()
    {
        if (this->warriors.size() > 1)
        {
            for (size_t i = 0; i < this->warriors.size(); i++)
            {
                for (size_t j = 0; j < this->warriors.size(); j++)
                {
                    auto first = this->warriors[i]->GetBoundingBox();
                    auto second = this->warriors[j]->GetBoundingBox();
                    if (i != j)
                    {
                        eke::Collision::CheckColl(first, second, 0.f);
                    }
                }
            }
        }
    }

    void Level::CheckProjectileIntersections()
    {
        // Check if player projectiles intersects with enemies
        for (size_t i = 0; i < this->player->GetProjectiles()->size(); i++)
        {
            for (size_t j = 0; j < this->warriors.size(); j++)
            {
                if ((*this->player->GetProjectiles())[i]->GetGlobalBounds().intersects(this->warriors[j]->GetBoundingBox()->getGlobalBounds()))
                {
                    this->warriors[j]->Damage((*this->player->GetProjectiles())[i]->GetDamage());
                    this->player->RemoveProjectileFromNthPlace(i);
                    break;
                }
            }
        }

        // Check if enemy projectiles intersects with player
        for (size_t i = 0; i < this->warriors.size(); i++)
        {
            for (size_t j = 0; j < this->warriors[i]->GetProjectiles()->size(); j++)
            {
                if ((*this->warriors[i]->GetProjectiles())[j]->GetGlobalBounds().intersects(this->player->GetBoundingBox()->getGlobalBounds()))
                {
                    this->player->Damage((*this->warriors[i]->GetProjectiles())[j]->GetDamage());
                    this->warriors[i]->RemoveProjectileFromNthPlace(j);
                    break;
                }
            }
        }
    }

} // namespace eke
