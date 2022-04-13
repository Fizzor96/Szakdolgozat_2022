#ifndef LABEL_HPP
#define LABEL_HPP 1

#include "Core/GameObject.h"
#include "Core/Globals.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace eke
{
    class Label : public GameObject
    {
    public:
        Label(const char *str, const float &posx, const float &posy);
        Label(const char *str, const sf::Vector2f position);
        Label(const char *str, const float &posx, const float &posy, const sf::Color &textcolor);
        Label(const char *str, const sf::Vector2f &position, const sf::Color &textcolor);

        void SetScale(const sf::Vector2f &scale);
        void SetScale(float xscale, float yscale);
        void SetPosition(const float &posx, const float &posy);
        void SetPosition(const sf::Vector2f &position);
        sf::Vector2f GetPosition() const;
        sf::Vector2f GetSize() const;

        void SetColor(const sf::Color &color);

        void SetText(const char *str);

        void Draw() override;
        void Update() override;

        ~Label();

    private:
        sf::Sprite *sprite;
        sf::Texture *texture;
        sf::Text text;
        sf::Color textcolor;
        sf::FloatRect bbox;
        sf::RectangleShape *initialbox;

    private:
        void PollEvents() override;
        void InitInitialBox();
        void AdjustInitialBox();

    public:
        Label() = delete;
        Label(const Label &other) = delete;
        Label(Label &&other) = delete;
        Label &operator=(const Label &other) = delete;
        Label &operator=(Label &&other) = delete;
    };
}

#endif