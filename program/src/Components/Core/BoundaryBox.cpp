#include "BoundaryBox.h"

namespace eke
{
    const sf::Color BoundaryBox::boxcolor = sf::Color::Transparent;

    BoundaryBox::BoundaryBox(const float &topleftx, const float &toplefty, const float &botrightx, const float &botrighty) noexcept
    {
        this->box = new sf::RectangleShape(sf::Vector2f(botrightx - topleftx, botrighty - toplefty));
        this->box->setOrigin(sf::Vector2f(this->box->getSize().x / 2.f, this->box->getSize().y / 2.f));
        this->box->setPosition(sf::Vector2f(topleftx + this->box->getSize().x / 2.f, toplefty + this->box->getSize().y / 2.f));
        this->box->setFillColor(BoundaryBox::boxcolor);
        this->box->setOutlineColor(sf::Color::Red);
        this->box->setOutlineThickness(2.f);
    }

    BoundaryBox::BoundaryBox(const sf::Vector2f &topleft, const sf::Vector2f &botright) noexcept
    {
        this->box = new sf::RectangleShape(sf::Vector2f(botright.x - topleft.x, botright.y - topleft.y));
        this->box->setOrigin(sf::Vector2f(this->box->getSize().x / 2.f, this->box->getSize().y / 2.f));
        this->box->setPosition(sf::Vector2f(topleft.x + this->box->getSize().x / 2.f, topleft.y + this->box->getSize().y / 2.f));
        this->box->setFillColor(BoundaryBox::boxcolor);
        this->box->setOutlineColor(sf::Color::Red);
        this->box->setOutlineThickness(2.f);
    }

    BoundaryBox::~BoundaryBox()
    {
        if (this->box != nullptr)
        {
            delete this->box;
        }

        if (this->boundingboxes.size() > 0)
        {
            for (size_t i = 0; i < this->boundingboxes.size(); i++)
            {
                if (this->boundingboxes[i] != nullptr)
                {
                    delete this->boundingboxes[i];
                }
            }
            this->boundingboxes.clear();
        }
    }

    void BoundaryBox::AddBoundingBox(sf::RectangleShape *boundingbox)
    {
        this->boundingboxes.push_back(boundingbox);
    }

    void BoundaryBox::AddBoundingBoxes(const std::vector<sf::RectangleShape *> &boundingboxes)
    {
        for (size_t i = 0; i < boundingboxes.size(); i++)
        {
            this->boundingboxes.push_back(boundingboxes[i]);
        }
    }

    void BoundaryBox::Update()
    {
        for (size_t i = 0; i < this->boundingboxes.size(); i++)
        {
            eke::Collision::CheckColl(this->boundingboxes[i], this->box, 0.f);
        }
    }

    void BoundaryBox::Draw()
    {
        if (eke::Globals::Debug)
        {
            eke::Globals::RenderWindow->draw(*this->box);
        }
    }
} // namespace eke
