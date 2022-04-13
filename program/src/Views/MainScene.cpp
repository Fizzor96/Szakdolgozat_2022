#include "MainScene.h"

namespace eke
{
    MainScene *MainScene::Instance = nullptr;

    void MainScene::InitComponents()
    {
        this->level = new eke::Level();
        this->label = new eke::Label("", sf::Vector2f(1220.f, 1570.f));
        this->label->SetScale(0.6f, 0.6f);
        this->survivaltime = 0.f;
        this->ispaused = false;
        this->InitPauseMenu();
    }

    void MainScene::PollEvents()
    {
        sf::Event *ev = eke::Globals::Event;
        if (ev->type == sf::Event::KeyPressed)
        {
            if (ev->key.code == sf::Keyboard::Escape)
            {
                this->ispaused = !this->ispaused;
            }
        }

        this->PollEventsPauseMenu();
    }

    void MainScene::Update()
    {
        if (!this->ispaused)
        {
            this->level->Update();

            auto ppos = this->level->GetPlayerInst()->GetPosition();
            auto vp = eke::Globals::RenderWindow->getView().getSize();
            this->label->SetPosition(sf::Vector2f((ppos.x - vp.x / 2) + this->label->GetSize().x / 2, (ppos.y - vp.y / 2) + this->label->GetSize().y / 2));

            this->survivaltime += eke::Globals::DeltaTime;
            this->label->SetText(std::string("time: " + std::to_string((int)this->survivaltime) + "s").c_str());

            if (!this->level->IsPlayerAlive())
            {
                this->ispaused = true;
                this->pmLabel->SetText(std::string("You Died! Your time: " + std::to_string((int)this->survivaltime) + "s\nWell Played!").c_str());
            }
        }
        else
        {
            this->UpdatePauseMenu();
        }
    }

    void MainScene::Draw()
    {
        this->level->Draw();
        this->label->Draw();

        if (this->ispaused)
        {
            this->DrawPauseMenu();
        }
    }

    void MainScene::InitPauseMenu()
    {
        // Background
        this->pmBackground = new sf::RectangleShape(eke::Globals::RenderWindow->getView().getSize());
        this->pmBackground->setOrigin(this->pmBackground->getSize().x / 2, this->pmBackground->getSize().y / 2);
        this->pmBackground->setPosition(this->level->GetPlayerInst()->GetPosition());
        this->pmBackground->setFillColor(sf::Color(0, 0, 0, 160));

        // Label
        this->pmLabel = new eke::Label("Game Paused!", 0, 0);
        this->pmLabel->SetScale(2.f, 2.f);

        // Buttons
        eke::Button *pmBtnResume = new eke::Button("Resume");
        pmBtnResume->SetPosition(sf::Vector2f(0, 0));
        pmBtnResume->SetOnClickEvent(new std::function<void()>([this]()
                                                               { this->Resume(); }));
        this->pmButtons.push_back(pmBtnResume);

        eke::Button *pmBtnRestart = new eke::Button("Restart");
        pmBtnRestart->SetPosition(sf::Vector2f(0, 0));
        pmBtnRestart->SetOnClickEvent(new std::function<void()>([this]()
                                                                { this->Restart(); }));
        this->pmButtons.push_back(pmBtnRestart);

        eke::Button *pmBtnMenu = new eke::Button("Menu");
        pmBtnMenu->SetPosition(sf::Vector2f(0, 0));
        pmBtnMenu->SetOnClickEvent(new std::function<void()>([this]()
                                                             { eke::Controller::LoadScene(eke::SceneId::Menu); }));
        this->pmButtons.push_back(pmBtnMenu);

        eke::Button *pmBtnExit = new eke::Button("Exit");
        pmBtnExit->SetPosition(sf::Vector2f(0, 0));
        pmBtnExit->SetOnClickEvent(new std::function<void()>([this]()
                                                             { eke::Globals::RenderWindow->close(); }));
        this->pmButtons.push_back(pmBtnExit);
    }

    void MainScene::UpdatePauseMenu()
    {
        auto ppos = this->level->GetPlayerInst()->GetPosition();
        auto vsize = eke::Globals::RenderWindow->getView().getSize();

        // Background
        this->pmBackground->setPosition(this->level->GetPlayerInst()->GetPosition());

        // Label
        this->pmLabel->SetPosition(ppos.x, ppos.y - vsize.y / 2 + this->pmLabel->GetSize().y + vsize.y / 10);

        this->pmButtons[0]->SetPosition(sf::Vector2f(ppos.x, (ppos.y - vsize.y / 2 + this->pmButtons[0]->GetSize().y / 2) + ((vsize.y / 10) * 2)));
        this->pmButtons[1]->SetPosition(sf::Vector2f(ppos.x, (ppos.y - vsize.y / 2 + this->pmButtons[1]->GetSize().y / 2) + ((vsize.y / 10) * 4)));
        this->pmButtons[2]->SetPosition(sf::Vector2f(ppos.x, (ppos.y - vsize.y / 2 + this->pmButtons[2]->GetSize().y / 2) + ((vsize.y / 10) * 6)));
        this->pmButtons[3]->SetPosition(sf::Vector2f(ppos.x, (ppos.y - vsize.y / 2 + this->pmButtons[3]->GetSize().y / 2) + ((vsize.y / 10) * 8)));

        // Buttons
        if (this->level->IsPlayerAlive())
        {
            this->pmButtons[0]->Update();
        }

        for (size_t i = 1; i < this->pmButtons.size(); i++)
        {
            this->pmButtons[i]->Update();
        }
    }

    void MainScene::DrawPauseMenu()
    {
        // Background
        eke::Globals::RenderWindow->draw(*this->pmBackground);

        // Label
        this->pmLabel->Draw();

        // Buttons
        if (this->level->IsPlayerAlive())
        {
            this->pmButtons[0]->Draw();
        }

        for (size_t i = 1; i < this->pmButtons.size(); i++)
        {
            this->pmButtons[i]->Draw();
        }
    }

    void MainScene::PollEventsPauseMenu()
    {
        if (this->ispaused)
        {
            if (this->level->IsPlayerAlive())
            {
                this->pmButtons[0]->PollEvents();
            }

            for (size_t i = 1; i < this->pmButtons.size(); i++)
            {
                this->pmButtons[i]->PollEvents();
            }
        }
    }

    void MainScene::Restart()
    {
        this->level->Restart();
        this->survivaltime = 0;
        this->ispaused = false;
        this->pmLabel->SetText("Game Paused!");
    }

    void MainScene::Resume()
    {
        this->ispaused = false;
    }

    eke::SceneId MainScene::GetSceneId() const
    {
        return SceneId::Main;
    }

    MainScene::MainScene()
    {
        if (MainScene::Instance == nullptr)
        {
            MainScene::Instance = this;
        }
        this->sceneid = eke::SceneId::Main;
        this->InitComponents();
    }

    MainScene::~MainScene()
    {
    }
}