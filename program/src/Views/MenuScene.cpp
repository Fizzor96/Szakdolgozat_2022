#include "MenuScene.h"

namespace eke
{

    MenuScene *MenuScene::Instance = nullptr;

    eke::MenuScene *MenuScene::GetInstance() const
    {
        return eke::MenuScene::Instance;
    }

    void MenuScene::InitComponents()
    {
        eke::Button *btnStart = new eke::Button("Start");
        btnStart->SetPosition(sf::Vector2f(eke::Globals::RenderWindow->getView().getCenter().x, btnStart->GetPosition().y + btnStart->GetSize().y));
        btnStart->SetOnClickEvent(new std::function<void()>([]()
                                                            { eke::Controller::LoadScene(eke::SceneId::Main); }));
        this->buttons.push_back(btnStart);

        const float separator = btnStart->GetSize().y * 1.5;

        this->helpisvisible = true;

        eke::Button *btnHelp = new eke::Button("Help");
        btnHelp->SetPosition(sf::Vector2f(eke::Globals::RenderWindow->getView().getCenter().x, btnStart->GetPosition().y + separator));
        btnHelp->SetOnClickEvent(new std::function<void()>([this]()
                                                           { this->helpisvisible = !this->helpisvisible; }));
        this->buttons.push_back(btnHelp);

        eke::Button *btnDebug = new eke::Button("Debug: OFF");
        btnDebug->SetPosition(sf::Vector2f(eke::Globals::RenderWindow->getView().getCenter().x, btnHelp->GetPosition().y + separator));
        btnDebug->SetOnClickEvent(new std::function<void()>([this]()
                                                            { eke::Globals::Debug = !eke::Globals::Debug; 
                                                            if (eke::Globals::Debug)
                                                            {
                                                                this->buttons[2]->SetText("Debug: ON");
                                                            }
                                                            else
                                                            {
                                                                this->buttons[2]->SetText("Debug: OFF");
                                                            } }));
        this->buttons.push_back(btnDebug);

        eke::Button *btnExit = new eke::Button("Exit");
        btnExit->SetPosition(sf::Vector2f(eke::Globals::RenderWindow->getView().getCenter().x, eke::Globals::RenderWindow->getView().getSize().y - btnExit->GetSize().y));
        btnExit->SetOnClickEvent(new std::function<void()>([]()
                                                           { eke::Globals::RenderWindow->close(); }));
        this->buttons.push_back(btnExit);

        eke::Fire *fire1 = new eke::Fire();
        fire1->SetScale(sf::Vector2f(10, 20));
        fire1->SetPosition(eke::Globals::RenderWindow->getView().getSize().x / 6, (eke::Globals::RenderWindow->getView().getSize().y / 3) * 2.5);
        this->fires.push_back(fire1);

        eke::Fire *fire2 = new eke::Fire();
        fire2->SetScale(sf::Vector2f(10, 20));
        fire2->SetPosition((eke::Globals::RenderWindow->getView().getSize().x / 6) * 5, (eke::Globals::RenderWindow->getView().getSize().y / 3) * 2.5);
        this->fires.push_back(fire2);

        this->info_lbl = new eke::Label("Stay alive as long as you can!\n", eke::Globals::RenderWindow->getView().getSize().x / 2, eke::Globals::RenderWindow->getView().getSize().y / 2);
    }

    void MenuScene::PollEvents()
    {
        sf::Event *ev = eke::Globals::Event;
        if (ev->type == sf::Event::KeyPressed)
        {
            if (ev->key.code == sf::Keyboard::Escape)
            {
                eke::Globals::RenderWindow->close();
            }
        }

        for (size_t i = 0; i < this->buttons.size(); i++)
        {
            this->buttons[i]->PollEvents();
        }
    }

    void MenuScene::Update()
    {
        for (size_t i = 0; i < this->buttons.size(); i++)
        {
            this->buttons[i]->Update();
        }
        for (size_t i = 0; i < this->fires.size(); i++)
        {
            this->fires[i]->Update();
        }
    }

    void MenuScene::Draw()
    {
        if (this->helpisvisible)
        {
            this->info_lbl->Draw();
        }
        for (size_t i = 0; i < this->buttons.size(); i++)
        {
            this->buttons[i]->Draw();
        }
        for (size_t i = 0; i < this->fires.size(); i++)
        {
            this->fires[i]->Draw();
        }
    }

    MenuScene::MenuScene()
    {
        if (MenuScene::Instance == nullptr)
        {
            MenuScene::Instance = this;
        }

        this->sceneid = eke::SceneId::Menu;
        this->InitComponents();
    }

    eke::SceneId MenuScene::GetSceneId() const
    {
        return this->sceneid;
    }

    MenuScene::~MenuScene()
    {
        for (size_t i = 0; i < this->fires.size(); i++)
        {
            delete this->fires[i];
        }

        for (size_t i = 0; i < this->buttons.size(); i++)
        {
            delete this->buttons[i];
        }

        this->fires.clear();
        this->buttons.clear();

        delete this->info_lbl;

        delete eke::MenuScene::Instance;
    }
}