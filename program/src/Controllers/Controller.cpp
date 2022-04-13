#include "Controller.h"

namespace eke
{
    std::vector<eke::Scene *> Controller::Scenes;
    eke::Scene *Controller::Current;

    void Controller::Init()
    {
        Scenes.push_back(new eke::MenuScene());
        Scenes.push_back(new eke::MainScene());
        Controller::Current = Controller::Scenes[0];
    }

    void Controller::LoadScene(const eke::SceneId &sceneid)
    {
        for (size_t i = 0; i < Controller::Scenes.size(); i++)
        {
            if (Controller::Scenes[i]->GetSceneId() == sceneid)
            {

                if (sceneid == eke::SceneId::Menu)
                {
                    eke::Globals::RenderWindow->setView(sf::View(sf::Vector2f(960.f, 540.f), sf::Vector2f(1920.f, 1080.f)));
                }

                if (sceneid == eke::SceneId::Main)
                {
                    Controller::Scenes[i]->Restart();
                }

                Controller::Current = Controller::Scenes[i];
                std::cout << "Scene number " << i << ". loaded succesfully!\n";
            }
        }
    }

    void Controller::CleanUp()
    {
        for (size_t i = 0; i < eke::Controller::Scenes.size(); i++)
        {
            delete eke::Controller::Scenes[i];
        }
        eke::Controller::Scenes.clear();
        delete eke::Controller::Current;
    }

    void Controller::PollEvents()
    {
        Controller::Current->PollEvents();
    }

    void Controller::Update()
    {
        Controller::Current->Update();
    }

    void Controller::Draw()
    {
        Controller::Current->Draw();
    }

}