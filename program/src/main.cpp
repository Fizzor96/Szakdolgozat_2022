#include "Engine.h"
#include "functional"
#include <SFML/Graphics.hpp>

int main()
{
    eke::Globals::Init();
    eke::Controller::Init();

    // eke::Level level1;

    while (eke::Globals::RenderWindow->isOpen())
    {
        eke::Globals::DeltaTime = eke::Globals::Clock->restart().asSeconds();

        while (eke::Globals::RenderWindow->pollEvent(*eke::Globals::Event))
        {
            eke::Globals::PollEvents();
            eke::Controller::PollEvents();
        }

        eke::Globals::Update();
        eke::Controller::Update();
        // level1.Update();

        eke::Globals::RenderWindow->clear(sf::Color(54, 49, 60, 255));

        eke::Controller::Draw();
        // level1.Draw();

        eke::Globals::RenderWindow->display();
    }

    eke::Globals::CleanUp();

    return 0;
}