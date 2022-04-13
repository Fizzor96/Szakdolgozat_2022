#include "Anim.h"

namespace eke
{
    Anim::Anim(sf::Texture *texture, const unsigned int rows, unsigned int cols, const float switchTime)
    {
        this->imgCount = sf::Vector2u(cols, rows);
        this->switchTime = switchTime;
        this->totalTime = 0.f;
        this->currImg.x = 0;

        this->textureRect.width = texture->getSize().x / float(cols);
        this->textureRect.height = texture->getSize().y / float(rows);
    }

    Anim::Anim(sf::Texture *texture, const sf::Vector2u imgCount, float switchTime)
    {
        this->imgCount = imgCount;
        this->switchTime = switchTime;
        this->totalTime = 0.f;
        this->currImg.x = 0;

        this->textureRect.width = texture->getSize().x / float(imgCount.x);
        this->textureRect.height = texture->getSize().y / float(imgCount.y);
    }

    void Anim::SetSwitchTime(const float &time)
    {
        this->switchTime = time;
    }

    void Anim::SetAnimationRow(const unsigned int &row)
    {
        this->currImg.y = row;
    }

    sf::IntRect Anim::GetAnimRect() const
    {
        return this->textureRect;
    }

    Anim::~Anim()
    {
    }

    void Anim::Update(const int &row, const float &deltatime)
    {
        this->currImg.y = row;
        this->totalTime += deltatime;
        if (this->totalTime >= this->switchTime)
        {
            this->totalTime -= this->switchTime;
            currImg.x++;
            if (this->currImg.x >= this->imgCount.x)
            {
                this->currImg.x = 0;
            }
        }
        this->textureRect.left = this->currImg.x * this->textureRect.width;
        this->textureRect.top = this->currImg.y * this->textureRect.height;
    }
}